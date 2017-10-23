#ifndef _BASE_INFO_H_
#define _BASE_INFO_H_

#ifdef EXPORT_VIDEO_API_ALL
#define VIDEO_INFO_PARSER_API __declspec(dllexport) 
#else 
#define VIDEO_INFO_PARSER_API __declspec(dllimport) 
#endif

#include "video_info.hpp"
#include "ffmpeg_helper.hpp"
#include "windows_play_hk.hpp"
#include "windows_play_dh.hpp"
#include "windows_play_hb.hpp"

namespace video {

	class VIDEO_INFO_PARSER_API VideoInfoParser
	{
	public:
		VideoInfoParser(void);
		VideoInfoParser(const std::string& str_file_path);

	public:
		std::string str_file_name;

		/* Get basic inforamtion of a video file. */
		virtual VideoInfo* get_vedio_info();
		/* For some video files encoding with stream, its frame count is not write in 
		   file header, so it has to be counted one frame by one frame. */
		virtual int correct_frame_count();
	};

	/**
	 * DhInfoParser can be used for parse Dahua video's information.
	 * This class is derived from VideoInfoParser.
	 */
	class VIDEO_INFO_PARSER_API DhInfoParser 
		: public VideoInfoParser{
	public:
		DhInfoParser(void);
		DhInfoParser(const std::string& str_file_path);
		virtual VideoInfo* get_vedio_info();
	};

	/**
	 * GkInfoParser can be used for parse HanbangGaoke video's information.
	 * This class is derived from VideoInfoParser.
	 */
	class VIDEO_INFO_PARSER_API GkInfoParser 
		: public VideoInfoParser{
	public:
		GkInfoParser(void);
		GkInfoParser(const std::string& fileName);
		virtual VideoInfo* get_vedio_info();
	};

	/**
	 * AlkInfoParser can be used for parse video whose extension
	 * is '.alk' information.
	 * This class is derived from VideoInfoParser.
	 */
	class VIDEO_INFO_PARSER_API AlkInfoParser 
		: public VideoInfoParser{
	public:
		AlkInfoParser(void);
		AlkInfoParser(const std::string& get_vedio_info);
		virtual VideoInfo* GetVideoInfo();
	};

	/**
	 * CommonInfoParser can be used for parse standard video's information.
	 * This class is derived from VideoInfoParser.
	 */
	class VIDEO_INFO_PARSER_API CommonInfoParser 
		: public VideoInfoParser{
	public:
		CommonInfoParser(void);
		CommonInfoParser(const std::string& get_vedio_info);
		virtual VideoInfo* GetVideoInfo();
	};
}

#endif