#include "stdafx.h"

#include "video_info_parser.hpp"
#include <opencv2/opencv.hpp>
#include <vlc/vlc.h>

#pragma region Information Parser Base Class
video::VideoInfoParser::VideoInfoParser(void)
{
	this->str_file_name = "";
}

video::VideoInfoParser::VideoInfoParser(const std::string& str_file_path)
{
	this->str_file_name = str_file_path;
}

video::VideoInfo*  video::VideoInfoParser::get_vedio_info(){
	return NULL;
}

int video::VideoInfoParser::correct_frame_count(){
	cv::Mat mat_frame;
	cv::VideoCapture capture;
	capture.open(this->str_file_name);
	int n_frame_nb = 0;
	while(capture.read(mat_frame)){
		n_frame_nb++;
	}
	capture.release();
	return n_frame_nb;
}
#pragma endregion

//////////////////////////////////////////////////////////////////////////////////

#pragma region Dahua Video Parser
video::DhInfoParser::DhInfoParser(void)
{
	this->str_file_name = "";
}

video::DhInfoParser::DhInfoParser(const std::string& str_file_path)
{
	this->str_file_name = str_file_path;
}

video::VideoInfo* video::DhInfoParser::get_vedio_info(){
	VideoInfo* info_obj = new VideoInfo(this->str_file_name);

	long * n_dh_port = new long[1];
	if (!PLAY_GetFreePort(n_dh_port))
	{
		delete info_obj;
		info_obj = NULL;
		delete[] n_dh_port;
	    n_dh_port = NULL;
		return info_obj;
	}
	char* p_file_name = const_cast<char *>(this->str_file_name.c_str());
	if (!PLAY_OpenFile(*n_dh_port, p_file_name))
	{
		PLAY_ReleasePort(*n_dh_port);
		delete info_obj;
		info_obj = NULL;
		delete[] n_dh_port;
	    n_dh_port = NULL;
		return info_obj;		
	}
	
	int n_duration = PLAY_GetFileTime(*n_dh_port);	
	int n_total_frame = PLAY_GetFileTotalFrames(*n_dh_port);

	cv::VideoCapture cap;
	cap.open(p_file_name);
	float f_fps = cap.get(CV_CAP_PROP_FPS);;

	PLAY_CloseFile(*n_dh_port);
	PLAY_ReleasePort(*n_dh_port);

	// Try to open with OpenCV
	cv::VideoCapture capture;
	capture.open(p_file_name);
	if(capture.isOpened()){
		info_obj->is_cv_decode   = true;
		info_obj->n_frame_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
		info_obj->n_frame_width  = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	}
	else{
		info_obj->is_cv_decode   = false;
		info_obj->n_frame_height = 0;
		info_obj->n_frame_width  = 0;
	}
	capture.release();

	delete[] n_dh_port;
	n_dh_port = NULL;

	// Correct wrong information
	if(n_duration < 0 && f_fps > 0 && n_total_frame > 0)
		n_duration = (int)(n_total_frame / f_fps);
	else if(n_duration > 0 && f_fps < 0 && n_total_frame > 0)
		f_fps = (float)n_total_frame / n_duration;
	else if(n_duration > 0 && f_fps < 0 && n_total_frame < 0)
		n_total_frame = (int)(f_fps * n_duration);

	info_obj->n_duration = n_duration;
	info_obj->frame_nb   = n_total_frame;
	info_obj->f_fps      = f_fps;

	return info_obj;
}
#pragma endregion

//////////////////////////////////////////////////////////////////////////////////

#pragma region Hanbang Gaoke Video Parser
video::GkInfoParser::GkInfoParser(void)
{
	this->str_file_name = "";
}

video::GkInfoParser::GkInfoParser(const std::string& str_file_path)
{
	this->str_file_name = str_file_path;
}

video::VideoInfo* video::GkInfoParser::get_vedio_info()
{
	VideoInfo* info_obj =  new VideoInfo(this->str_file_name);

	char* p_file_name = const_cast<char *>(this->str_file_name.c_str());

	long * p_gk_port = new long[1];
	*p_gk_port = HB_PLAY_OpenFileEx(p_file_name);
	if (*p_gk_port == 0)	
	{
		return nullptr;
	}
	
	SLEEP(1000);
	int n_duration    = HB_PLAY_GetFileTime(*p_gk_port);
	int n_total_frame = HB_PLAY_GetFileTotalFrames(*p_gk_port);
	float f_fps       = (float)HB_PLAY_GetCurrFrameRate(*p_gk_port);

	HB_PLAY_CloseFile(*p_gk_port);

	// Try to open with OpenCV
	cv::VideoCapture capture;
	capture.open(p_file_name);
	if(capture.isOpened()){
		info_obj->is_cv_decode   = true;
		info_obj->n_frame_height = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
		info_obj->n_frame_width  = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	}
	else{
		info_obj->is_cv_decode   = false;
		info_obj->n_frame_height = 0;
		info_obj->n_frame_width  = 0;
	}
	capture.release();

	delete[] p_gk_port;
	p_gk_port = NULL;

	// Correct wrong information
	if(n_duration < 0 && f_fps > 0 && n_total_frame > 0)
		n_duration = (int)(n_total_frame / f_fps);
	else if(n_duration > 0 && f_fps < 0 && n_total_frame > 0)
		f_fps = (float)n_total_frame / n_duration;
	else if(n_duration > 0 && f_fps < 0 && n_total_frame < 0)
		n_total_frame = (int)(f_fps * n_duration);

	info_obj->n_duration = n_duration;
	info_obj->f_fps      = f_fps;
	info_obj->n_frame_nb = n_total_frame;

	return info_obj;
}
#pragma endregion

#pragma region ALK Video Parser
video::AlkInfoParser::AlkInfoParser(void)
{
	this->str_file_name = "";
}

video::AlkInfoParser::AlkInfoParser(const std::string& str_file_path)
{
	this->str_file_name = str_file_path;
}

video::VideoInfo* video::AlkInfoParser::get_vedio_info(){
	VideoInfo* info_obj =  new VideoInfo(this->str_file_name);
	char* p_file_name = const_cast<char *>(this->str_file_name.c_str());

	FfmpegHelper* p_ffmpeg_obj = new FfmpegHelper();
	bool is_ffmpeg_open = p_ffmpeg_obj->OpenFile(p_file_name);
	if(!is_ffmpeg_open){
		info_obj = nullptr;
		goto PARSE_FAIL;
	}

	int     n_duration     = p_ffmpeg_obj->GetVideoDuration();
	float   f_fps          = p_ffmpeg_obj->GetVideoFramePerSecond();
	int64_t n_total_frame  = p_ffmpeg_obj->GetVideoNbFrames();
	int     n_frame_widt   = p_ffmpeg_obj->GetWidth();
	int     n_frame_height = p_ffmpeg_obj->GetHeight();

	if(fabs(f_fps - 0.0f) >= EPSILON){
		if(n_duration > 0 && n_total_frame <= 0){
			n_total_frame = static_cast<int64_t>(n_duration * f_fps);
		}
		if(n_total_frame > 0 && n_duration <= 0){
			n_duration = static_cast<int>(n_total_frame / f_fps);
		}
	}
	info_obj->is_cv_decode   = true;
	info_obj->n_frame_height = n_frame_height;
	info_obj->n_frame_width  = n_frame_width;
	info_obj->n_duration     = n_duration;
	info_obj->f_fps          = f_fps;
	info_obj->n_frame_nb     = n_total_frame;

	PARSE_FAIL:
	delete p_ffmpeg_obj;
	p_ffmpeg_obj = NULL;

	delete[] p_file_name;
	p_file_name = NULL;

	return info_obj;
}

#pragma endregion

#pragma region Standard Common Parser
video::CommonInfoParser::CommonInfoParser(void)
{
	this->str_file_name = "";
}

video::CommonInfoParser::CommonInfoParser(const std::string& str_file_path)
{
	this->str_file_name = str_file_path;
}

video::VideoInfo* video::CommonInfoParser::get_vedio_info(){
	char* p_file_name = const_cast<char *>(this->str_file_name.c_str());
	VideoInfo* info_obj =  new VideoInfo(this->str_file_name);

	int     n_duration    = -1;
	float   f_fps         = -1;
	int64_t n_total_frame = -1;

	FfmpegHelper* p_ffmpeg_obj = new FfmpegHelper();
	bool is_ffmpeg_open = p_ffmpeg_obj->OpenFile(p_file_name);
	if(!is_ffmpeg_open){
		goto TRY_OPRN_CV;
	}

	// First try parse with ffmpeg
	n_duration   = p_ffmpeg_obj->GetVideoDuration();
	f_fps        = p_ffmpeg_obj->GetVideoFramePerSecond();
	n_total_frame = p_ffmpeg_obj->GetVideoNbFrames();
	int n_frame_width  = p_ffmpeg_obj->GetWidth();
	int n_frame_height = p_ffmpeg_obj->GetHeight();
	// For stream data, count its frame numbers
	if(n_total_frame <= 0){
		n_total_frame = p_ffmpeg_obj->CountStreamNbFrames();
		n_duration = static_cast<int>(n_total_frame / f_fps);
	}

	TRY_OPRN_CV:
	// If ffmpeg cannot read some information, try with OpenCV
	delete p_ffmpeg_obj;
	p_ffmpeg_obj = NULL;

	cv::VideoCapture capture;
	capture.open(p_file_name);
	if(capture.isOpened())
	{
		info_obj->is_cv_decode = true;
		// Try get video properties with OpenCV when ffmpeg fails
		if( n_duration <= 0 || n_total_frame <= 0 ){
			f_fps = (float)capture.get(CV_CAP_PROP_FPS);
			n_total_frame = capture.get(CV_CAP_PROP_FRAME_COUNT);
			n_duration = n_total_frame / f_fps;
		}
		int n_frame_count = 0;
		// Try get video frame size when ffmpeg fails
		if(info_obj->n_frame_width <= 0 || info_obj->n_frame_height <= 0){
			cv::Mat mat_frame;
			capture.read(mat_frame);
			n_frame_count++;
			n_frame_width  = mat_frame.cols;
			n_frame_height = mat_frame.rows;
		}
		// For stream file, try to count its frame to get frame number
		if( (n_duration <= 0 || n_total_frame <= 0) 
			&& fabs(f_fps - 0.0f) >= EPSILON ){

				while(capture.grab()){
					n_frame_count++;
				}
				n_total_frame = n_frame_count;
				n_duration = n_total_frame / f_fps;
		}
		capture.release();
	}
	else
	{
		capture.release();
		if(is_ffmpeg_open == false){
			info_obj = NULL;
			goto PARSE_FAIL;
		}
		info_obj->is_cv_decode = false;		
	}

	info_obj->n_duration     = n_duration;
	info_obj->f_fps          = f_fps;
	info_obj->n_frame_nb     = n_total_frame;
	info_obj->n_frame_width  = n_frame_width;
	info_obj->n_frame_height = n_frame_height;

	PARSE_FAIL:
	return info_obj;
}

#pragma endregion