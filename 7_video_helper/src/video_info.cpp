#include "stdafx.h"

#include "video_info.hpp"
#include <fstream>
#include <cstring>
#include <sys/stat.h>

#ifdef WIN32
#define FILE_STAT _stat
#else
#define FILE_STAT stat
#endif

video::VideoInfo::VideoInfo(){
	n_frame_nb   = -1;
	n_duration   = -1;  
	f_fps        = -1.0f;       
	n_file_size  = -1;    
	is_cv_decode = false;
	is_valide    = false;
}

video::VideoInfo::VideoInfo(const std::string& str_file_path){
	n_frame_nb   = -1;
	n_duration   = -1;
	f_fps        = -1.0f;
	n_file_size  = -1;
	is_cv_decode = false;

	std::fstream fs;
	fs.open(str_file_path, std::ios::in);
	if(fs.is_open())
	{
		is_valide = true;
		this->str_full_path = str_file_path;
		get_file_name();
		get_extension();

		long long n_file_length = -1;

		struct FILE_STAT stat_buff;
		if(FILE_STAT(str_file_path.c_str(), &stat_buff) >= 0)
		{
			this->n_file_size = stat_buff.st_size;
			this->is_valide = true;
		}
		else{
			this->n_file_size = -1;
			this->is_valide = false;
		}		

		fs.close();
	}
	else
	{
		this->is_valide = false;
		this->str_full_path = "";
		this->str_file_name = "";
		this->str_extension = "";
		this->n_file_size   = -1;
	}
}

/** 
 * To get if this file is valid.(Set by constructor)
 * @return true if given file is valid.
 */
bool video::VideoInfo::is_invalid_file() const{
	return this->is_valide;
}

/** 
 * Set file header string.For many video files, they may have 
 * file header string to specify their encode or type information.
 * @param[in] headStr: file header pointer.
 */
void video::VideoInfo::set_file_head(const char* p_file_header){
	if(p_file_header == NULL || strlen(p_file_header) <= 0){
		this->str_file_head = std::string("");
	}
	else{
		this->str_file_head = std::string(p_file_header);
	}
}

/** 
 * Get file name(with extension) from path.
 * @return true if file path has value, and false otherwise.
 */
bool video::VideoInfo::get_file_name(){
	if(this->str_full_path.size() > 0)
	{
		std::size_t n_slash_pos = full_path.find_last_of("/\\");
		this->str_file_name = str_full_path.substr(n_slash_pos + 1);
		return true;
	}
	else
	{
		this->str_file_name = std::string("");
		return false;
	}
}

/** 
 * Get file extension from path.
 * @return true if file path has value, and false otherwise.
 */
bool video::VideoInfo::get_extension(){
	if(this->str_full_path.size() > 0)
	{
		std::size_t n_dot_pos = full_path.find_last_of(".");
		this->str_extension = full_path.substr(n_dot_pos);
		return true;
	}
	else
	{
		this->str_extension = std::string("");
		return false;
	}
}