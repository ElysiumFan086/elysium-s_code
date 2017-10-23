#ifndef _VEDIO_INFO_H_
#define _VEDIO_INFO_H_

#include <string>

#ifdef EXPORT_VIDEO_API_ALL
#define VIDEO_INFO_API __declspec(dllexport) 
#else 
#define VIDEO_INFO_API __declspec(dllimport) 
#endif

namespace video {
	typedef long long int64_t;

	class VIDEO_INFO_API VideoInfo
	{
	public:
		VideoInfo(void);
		VideoInfo(const std::string& str_file_path);
		/* Setting file header data, learn more in 'video::VideoInfo::str_file_head' */
		void set_file_head(const char* p_file_header);
		/* If the file exits or can be opened succesfully */
		bool is_invalid_file() const;

	public:
		/* File's full path string */
		std::string str_full_path;
		/* File's name without path information */
		std::string str_file_name;
		/* File's extension string with dot in it*/
		std::string str_extension;
		/* The first several bytes data for a video file, which may be different for some video type. */
		std::string str_file_head;

		/* Video frame numbers */
		int64_t   n_frame_nb;
		/* Video duration, counted as second */
		int       n_duration;
		/* Frame per second, it is counted as a float number */
		float     f_fps;

		/* Video frame's width */
		int       n_frame_width;
		/* Video frame's height */
		int       n_frame_height;
		/* File length */
		int64_t   n_file_size;

		/* If video can be decoded with cv::VideoCapture in OpenCV */
		bool  is_cv_decode;

	private:
		/* If this is a valid video file */ 
		bool  is_valide;

		bool get_file_name();
		bool get_extension();
	};
}

#endif