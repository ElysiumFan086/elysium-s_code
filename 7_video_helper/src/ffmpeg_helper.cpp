#include "Stdafx.h"
#include "ffmpeg_helper.hpp"

video::FfmpegHelper::FfmpegHelper():
	pImgConvertCtx(NULL), 
	videoBaseTime(0.0),
	videoFramePerSecond(0.0), 
	isOpen(false), 
	videoStreamIndex(-1),
	pVideoCodec(NULL), 
	pVideoCodecCtx(NULL), 
	pFormatCtx(NULL) 
{
	pFrame = NULL;
	out_buffer = NULL;
};

video::FfmpegHelper::~FfmpegHelper(){
	CloseFile();
}

int video::FfmpegHelper::GetHeight(){
	return this->height;
}

int video::FfmpegHelper::GetWidth(){
	return this->width;
}

/** 
 * Get the video frame rate. The value may be wrong for some
 * unknown format or video pure stream.
 * There exists a typical kind video whose r_frame_rate is wrong.
 * @return    video frame rate.
 */
double   video::FfmpegHelper::GetVideoFramePerSecond(){
	return this->videoFramePerSecond;
}

/** 
 * Get the video base time. The value is parsed from AVStream instead
 * of AVCodecContext.
 * @return    video base time.
 */
double   video::FfmpegHelper::GetVideoBaseTime(){
	return this->videoBaseTime;
}

/** 
 * Get the video frame numbers
 * @return    frame numbers of the video, if error occurs a value less 
 *            or equal to zero will be get.
 */
int64_t  video::FfmpegHelper::GetVideoNbFrames(){
	return this->video_nb_frames;
}

/** 
 * Register related muxer and demuxer in ffmpeg, allocate AVFormatContext
 * and open given file. After that, video stream in the file will be got
 * and some basic information like fps, duration and frame numbers will be
 * parsed.
 * @param[in] inputFile: file's URL to be opened
 * @return    return true if file is open successfully, and false otherwise.
 */
bool video::FfmpegHelper::OpenFile(const std::string& inputFile)
{
	CloseFile();

	// Register all components
	av_register_all();

	pFormatCtx = avformat_alloc_context();

	// Open media file.
	this->errorCode = avformat_open_input(&pFormatCtx, inputFile.c_str(), NULL, NULL);
	if (this->errorCode != 0)
	{
		CloseFile();
		return false;
	}

	// Get format info.
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		CloseFile();
		return false;
	}

	// open video and audio stream.
	bool hasVideo = OpenVideo();

	if (!hasVideo)
	{
		CloseFile();
		return false;
	}

	isOpen = true;

	// Get file information.
	if (videoStreamIndex != -1)
	{
		AVStream* stream = pFormatCtx->streams[videoStreamIndex];
		videoFramePerSecond = av_q2d(stream->r_frame_rate);
		/** 
			For some videos whose fps is 27, its correct fps is often
			not 27 exactly. So check the time_base and ticks_per_frame
			of codec member in AVStream, and by experience we can get
			the fps in following way, though it is also not quiet right.
		*/
		if(videoFramePerSecond - 27 <= EPSILON){
			// For H.264/MPEG-2, 'ticks_per_frame' of codec is 2
			videoFramePerSecond = stream->codec->time_base.den 
				/ stream->codec->time_base.num 
				/ stream->codec->ticks_per_frame;
		}

		//Need for convert time to ffmpeg time.
		videoBaseTime   = av_q2d(pFormatCtx->streams[videoStreamIndex]->time_base); 
		video_nb_frames = pFormatCtx->streams[videoStreamIndex]->nb_frames; 
		video_duration  = GetVideoDuration(); 
	}
	return true;
}

/** 
 * Get video stream after initialize contexts, and the mainly work is to iterating
 * AVStream[] and get video stream. After that, related Codec and Context will
 * also be find. SwsContext, AVFrame and decode buffer will also be get here.
 * @return    return true if file is open successfully, and false otherwise.
 */
bool     video::FfmpegHelper::OpenVideo()
{
	bool res = false;

	if (pFormatCtx)
	{
		videoStreamIndex = -1;

		for (unsigned int i = 0; i < pFormatCtx->nb_streams; i++)
		{
			if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
			{
				videoStreamIndex = i;
				pVideoCodecCtx   = pFormatCtx->streams[i]->codec;
				pVideoCodec      = avcodec_find_decoder(pVideoCodecCtx->codec_id);

				if (pVideoCodec)
				{
					res     = !(avcodec_open2(pVideoCodecCtx, pVideoCodec, NULL) < 0);
					width   = pVideoCodecCtx->coded_width;
					height  = pVideoCodecCtx->coded_height;
				}

				break;
			}
		}

		if (!res)
		{
			CloseVideo();
		}
		else
		{
			pImgConvertCtx = sws_getContext(pVideoCodecCtx->width, pVideoCodecCtx->height,
				pVideoCodecCtx->pix_fmt,
				pVideoCodecCtx->width, pVideoCodecCtx->height,
				PIX_FMT_BGR24,
				SWS_BICUBIC, NULL, NULL, NULL);
		}

		// Format convert buffer
		out_buffer = (uint8_t *)av_malloc(
			avpicture_get_size(PIX_FMT_BGR24, 
			pVideoCodecCtx->width, 
			pVideoCodecCtx->height));
		pFrame = av_frame_alloc();
		avpicture_fill((AVPicture*)pFrame, out_buffer, 
			PIX_FMT_BGR24, width, height);
	}

	return res;
}

/** 
 * Free related structure, such as AVFrame and decode buffer, after
 * which close the open file and release AVFormatContext struct.
 * @return     Return true is clean-up work is finished.
 */
bool video::FfmpegHelper::CloseFile()
{
	isOpen = false;

	if(pFrame != NULL){
		av_frame_free(&pFrame);
	}

	if(out_buffer != NULL){
		av_free(out_buffer);
	}

	// Close video and audio.
	CloseVideo();

	if (pFormatCtx)
	{
		avformat_close_input(&(pFormatCtx));
		avformat_free_context(pFormatCtx);
		pFormatCtx = NULL;
	}

	return true;
}

/**
 * Close AVCodecContext struct
 */
void video::FfmpegHelper::CloseVideo()
{
	if (pVideoCodecCtx)
	{
		avcodec_close(pVideoCodecCtx); 
		pVideoCodecCtx = NULL;
		pVideoCodec = NULL;
		videoStreamIndex = 0;
	}
}

/**
 * Get video duration with seconds, and the code is referencing
 * ffmpeg 'av_dump_format' function, which is defined in the file
 * of 'libavformat/dump.c' Line 528
 *
 * @return      Return the video's duration in second.
*/
int video::FfmpegHelper::GetVideoDuration()
{
	if (pFormatCtx)
	{
		int hours, mins, secs, us;
		int totalDuration = 0;;
		int64_t duration = pFormatCtx->duration 
			+ (pFormatCtx->duration <= INT64_MAX - 5000 ? 5000 : 0);
		secs  = duration / AV_TIME_BASE;
		totalDuration = secs;
		us    = duration % AV_TIME_BASE;
		mins  = secs / 60;
		secs %= 60;
		hours = mins / 60;
		mins %= 60;

		if(secs > 0)
			return totalDuration;
	}

	return 0;
}

/** 
 * Decode next frame and return it with converting into
 * OpenCV cv::Mat format.
 * It is strongly recommended to get a deep copy of the 
 * frame Mat after invoking this function.
 *
 * @param[out] hasFrame: If successfully decode a frame, this param
 *             is set to be frame number and to be -1 otherwise.
 * @return     Return the frame Mat with RGB format.
 */
cv::Mat video::FfmpegHelper::GetNextFrame(int& hasFrame)
{
	cv::Mat imgFrame;

	hasFrame = -1;
	if (videoStreamIndex != -1)
	{
		AVFrame *pVideoYuv = av_frame_alloc();
		AVPacket *packet = (AVPacket *)av_malloc(sizeof(AVPacket));

		bool exitLoop = false;
		if (isOpen)
		{
			// Read frame packet.
			while (av_read_frame(pFormatCtx, packet) >= 0)
			{
				int64_t pts = 0;
				pts = (packet->dts != AV_NOPTS_VALUE) ? packet->dts : 0;

				if(packet->stream_index == videoStreamIndex)
				{
					// Convert ffmpeg frame timestamp to real frame number.
					int64_t numberFrame = (double)((int64_t)pts - 
						pFormatCtx->streams[videoStreamIndex]->start_time) * 
						videoBaseTime * videoFramePerSecond; 

					// Decode packet into frame
					bool isDecodeComplite = false;
					if (pVideoCodecCtx)
					{
						if (packet && pVideoYuv)
						{
							int got_picture_ptr = 0;
							int videoFrameBytes = avcodec_decode_video2(
								pVideoCodecCtx,
								pVideoYuv,
								&got_picture_ptr, 
								packet);
							isDecodeComplite = (videoFrameBytes > 0);
						}
					}

					// Convert frame from YUV to RGB
					if (isDecodeComplite)
					{
						sws_scale(pImgConvertCtx, 
							(const uint8_t* const*)pVideoYuv->data, 
							pVideoYuv->linesize, 
							0, pVideoCodecCtx->height, 
							pFrame->data, pFrame->linesize);

						imgFrame = cv::Mat(pVideoCodecCtx->height, pVideoCodecCtx->width, CV_8UC3, 
							pFrame->data[0], pFrame->linesize[0]);
						hasFrame = 1;
					}
					exitLoop = true;
				} // End of if

				av_free_packet(packet);
				if(exitLoop == true){
					break;
				}

				packet = (AVPacket *)av_malloc(sizeof(AVPacket));
			}// end of While
			av_free(pVideoYuv);
		}    
	}
	return imgFrame;
}

/**
 * Count video, typically for streams, frame numbers by reading data
 * packet one by one, yet not decoding them.
 * @return      Return frame number, if open failed return 0.
 */
int64_t video::FfmpegHelper::CountStreamNbFrames(){
	if(pFormatCtx == NULL)
		return 0;
	int64_t frameCount = 0;
	clock_t begTime = clock();

	AVPacket packet = AVPacket();
	while (av_read_frame(pFormatCtx, &packet) >= 0)
	{
		if(packet.stream_index == videoStreamIndex){
			frameCount++;
		}
		av_free_packet(&packet);
		packet = AVPacket();
	}
	av_free_packet(&packet);
	clock_t endTime = clock();

	/* Executing time : */
	double timeCost = static_cast<double>(endTime - begTime) 
		/ CLOCKS_PER_SEC * 1000;
	
	return frameCount;
}