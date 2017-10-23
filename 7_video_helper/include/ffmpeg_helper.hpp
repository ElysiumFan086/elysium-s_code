#ifndef FFMPEG_H
#define FFMPEG_H

#include "ffmpegHeader.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>

#define EPSILON 1e-8

namespace video{
	class FfmpegHelper{
	public:
		FfmpegHelper();

		virtual ~FfmpegHelper();
		/** 
		* Register related muxer and demuxer in ffmpeg, allocate AVFormatContext
		* and open given file. After that, video stream in the file will be got
		* and some basic information like fps, duration and frame numbers will be
		* parsed.
		* @param[in] inputFile: file's URL to be opened
		* @return    return true if file is open successfully, and false otherwise.
		*/
		virtual bool OpenFile(const std::string& inputFile);
		
		// Return next FFmpeg frame.
		virtual cv::Mat GetNextFrame(int& hasFrame);

		// Return video width
		int GetWidth();
		// Return video hight
		int GetHeight();
		/** 
		* Get the video frame rate. The value may be wrong for some
		* unknown format or video pure stream.
		* There exists a typical kind video whose r_frame_rate is wrong.
		* @return    video frame rate.
		*/
		double  GetVideoFramePerSecond();
		/** 
		* Get the video base time. The value is parsed from AVStream instead
		* of AVCodecContext.
		* @return    video base time.
		*/
		double  GetVideoBaseTime();
		/** 
		* Get the video frame numbers
		* @return    frame numbers of the video, if error occurs a value less 
		*            or equal to zero will be get.
		*/
		int64_t GetVideoNbFrames();
		/**
		* Get video duration with seconds, and the code is referencing
		* ffmpeg 'av_dump_format' function, which is defined in the file
		* of 'libavformat/dump.c' Line 528
		*
		* @return    Return the video's duration in second.
		*/
		int     GetVideoDuration();
		/**
		* Count video, typically for streams, frame numbers by reading data
		* packet one by one, yet not decoding them.
		* @return      Return frame number, if open failed return 0.
		*/
		int64_t CountStreamNbFrames();

	private:
		/** 
		* Get video stream after initialize contexts, and the mainly work is to iterating
		* AVStream[] and get video stream. After that, related Codec and Context will
		* also be find. SwsContext, AVFrame and decode buffer will also be get here.
		* @return    return true if file is open successfully, and false otherwise.
		*/
		bool OpenVideo(); 
		/** 
		* Free related structure, such as AVFrame and decode buffer, after
		* which close the open file and release AVFormatContext struct.
		* @return     Return true is clean-up work is finished.
		*/
		virtual bool CloseFile();
		/**
		* Close AVCodecContext struct
		*/
		void CloseVideo();

	public:
		// Convert YVU12 to RGB
		static bool YV12_to_RGB24(
			unsigned char* p_yuv12, 
			unsigned char* p_rgb24, 
			int            n_width, 
			int            n_height)
		{
			if (n_width < 1 || n_height < 1 || p_yuv12 == NULL || p_rgb24 == NULL)
				return false;
			AVPicture av_frame_yuv, av_frame_rgb;

			avpicture_fill(&av_frame_yuv, p_yuv12, PIX_FMT_YUV420P, n_width, n_height);

			uint8_t * p_tmp_data = av_frame_yuv.data[1];
			av_frame_yuv.data[1] = av_frame_yuv.data[2];
			av_frame_yuv.data[2] = p_tmp_data;

			avpicture_fill(&av_frame_rgb, p_rgb24, PIX_FMT_BGR24, n_width, n_height);

			struct SwsContext* sws_img_ctx = NULL;
			sws_img_ctx = sws_getContext(n_width, n_height, PIX_FMT_YUV420P, 
				n_width, n_height, PIX_FMT_BGR24, SWS_BILINEAR, NULL, NULL, NULL);

			if (sws_img_ctx != NULL){
				sws_scale(sws_img_ctx, av_frame_yuv.data, av_frame_yuv.linesize, 
					0, n_height, av_frame_rgb.data, av_frame_rgb.linesize);
				if(sws_img_ctx){
					sws_freeContext(sws_img_ctx);
					sws_img_ctx = NULL;
				}
				return true;
			}
			else{
				sws_freeContext(sws_img_ctx);
				sws_img_ctx = NULL;
				return false;
			}
		}


	private: 
		AVFormatContext* pFormatCtx;      // FFmpeg file format.
		AVCodecContext*  pVideoCodecCtx;  // FFmpeg codec context.
		AVCodec*         pVideoCodec;     // FFmpeg codec for video.
		SwsContext*      pImgConvertCtx;  // FFmpeg context convert image.

		AVFrame*         pFrame;          // Ffmpeg decode buffer frame
		uint8_t*         out_buffer;      // Output buffer for 'pFrame'

		int     videoStreamIndex;         // Video stream number in file.
		int64_t video_nb_frames;          // decode video stream frame numbers
		double  video_duration;
		bool    isOpen;                   // File is open or not.
		double  videoFramePerSecond;      // Video frame per seconds.
		double  videoBaseTime;            // FFmpeg timebase for video.
		int     width;                    // Width of image
		int     height;                   // Height of image

		int     errorCode;                // Error code

	};
}

#endif