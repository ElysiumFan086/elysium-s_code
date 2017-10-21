#ifdef WIN32
#include "stdafx.h"
#endif
#include <iostream>  
#include <boost/filesystem.hpp>  
#include <file_helper.hpp>  

namespace fs = boost::filesystem;

bool FileHelper::traverse_path(
	std::vector<std::string> &vec_file_name, 
	const std::string& str_path, 
	const std::string& str_file_type) const
{
	if (!fs::exists(str_path))
	{
		std::cout << "Path: " << str_path << " is not exist." << std::endl;
		return false;
	}

	if (!fs::is_directory(str_path))
	{
		std::cout << "Path: " << str_path << " is not a directory." << std::endl;
		return false;
	}

	fs::directory_iterator itr_begin(str_path);
	fs::directory_iterator itr_end;
	for (; itr_begin != itr_end; itr_begin++)
	{
		fs::path path_tmp(*itr_begin);
		if (fs::is_regular_file(path_tmp))
		{
			path_tmp = path_tmp.filename();
			std::string str = path_tmp.string();
			if (is_file_type(str, str_file_type))
				vec_file_name.push_back(str);
		}
	}

	return true;
}

bool FileHelper::is_file_exist(
	const std::string& str_path, 
	const std::string& str_file_name) const
{
	std::string t_path = str_path;
	if (*(t_path.end() - 1) != '/')
	{
		t_path += '/';
	}

	return is_file_exist(t_path + str_file_name);;
}

bool FileHelper::is_file_exist(const std::string& str_file_name) const
{
	fs::path path_file(str_file_name);
	if (!fs::exists(path_file))
	{
		return false;
	}

	return fs::is_regular_file(path_file);
}

bool  FileHelper::get_dir_files(
	const        std::string& str_dir_path, 
	std::vector<std::string>& vec_file_names)
{
	fs::path fullpath(str_dir_path);

	if (!fs::exists(fullpath))
	{
		return false;
	}
	fs::recursive_directory_iterator itr_end;
	for (fs::recursive_directory_iterator itr(fullpath); itr != itr_end; itr++)
	{
		try{
			if (fs::is_directory(*itr))
			{
				std::cout << "[Directory]: " << *itr << std::endl;
			}
			else
			{
				std::string str_file_name = itr->path().filename().string();
				if (str_file_name.find(".csv") != std::string::npos)
					continue;
				vec_file_names.push_back(str_file_name);
			}
		}
		catch (const std::exception& ex)
		{
			std::cout << __FILE__ << ":" << __LINE__ 
				<< "]Read file error: " << ex.what() << std::endl;
			continue;
		}
	}
	return true;
}

bool FileHelper::delete_file(
	const std::string& str_path, 
	const std::string& str_file_name) const
{
	std::string t_path = str_path;
	if (*(t_path.end() - 1) != '/')
	{
		t_path += '/';
	}

	return delete_file(t_path + str_file_name);;
}

bool FileHelper::delete_file(const std::string& str_file_name) const
{
	fs::path path_file(str_file_name);
	if (!fs::exists(path_file) || !fs::is_regular_file(path_file))
	{
		return false;
	}

	return fs::remove(path_file);

	return true;
}

bool FileHelper::delete_directory(const std::string& str_path_name) const
{
	std::vector<std::string> vec_file_name;
	if (!traverse_path(vec_file_name, str_path_name))
		return false;

	for (auto tr = vec_file_name.begin(); itr != vec_file_name.end(); itr++)
	{
		delete_file(str_path_name +"/"+ (*itr));
	}
	delete_file(str_path_name);
	return true;
}

bool FileHelper::create_directory(const std::string& str_path_name) const
{
	if (!boost::filesystem::exists(str_path_name))
	{
		boost::filesystem::create_directories(str_path_name);
	}
	return true;
}

void FileHelper::copy_file(
	const std::string& str_file_src, 
	const std::string& str_file_dst) const
{
	fs::path s_path(str_file_src);
	fs::path d_path(str_file_dst);

	if (is_file_exist(str_file_dst))
	{
		delete_file(str_file_dst);
	}
	fs::copy_file(s_path, d_path, fs::copy_option::fail_if_exists);
}

void FileHelper::copy_directory(
	const std::string& str_path_src, 
	const std::string& str_path_dst) const
{
	std::vector<std::string> vec_file_name;
	if (traverse_path(vec_file_name, str_path_src))
	{
		for (auto itr = vec_file_name.begin(); itr != vec_file_name.end(); ++itr)
		{
			copy_file(str_path_src + (*itr), str_path_dst + (*itr));
		}
	}
}

bool FileHelper::change_file_type(
		const std::string& str_file_name, 
		const std::string& str_type_src, 
		const std::string& str_type_dst, 
		std::string&       str_changed_name) const
{
	if (!is_file_type(str_file_name, str_type_src))
	{
		std::cout << "File " << str_file_name << " dose not match file type " 
			<< str_type_src << std::endl;
		return false;
	}

	str_changed_name = str_file_name;
	int n_size = str_type_src.length();

	str_changed_name.replace(str_changed_name.length() - n_size, n_size, str_type_dst);

	return true;
}

bool FileHelper::is_file_type(
	const std::string& str_file_name, 
	const std::string& str_file_type) const
{
	std::string str_file_cp = str_file_name;
	int n_size = str_file_type.length();

	if (0 == str_file_cp.substr(str_file_cp.length() - n_size, n_size).compare(str_file_type))
		return true;

	return false;
}

bool FileHelper::read_file(
	const std::string&        str_file_name, 
	std::vector<std::string>& vec_data)
{
	vec_data.clear();
	std::ifstream ifs(str_file_name, std::ios::in);

	const int n_buff_size = 512;
	char p_buff[n_buff_size];
	while (!ifs.eof())
	{
		ifs.getline(p_buff, n_buff_size);
		std::string str_line = p_buff;
		if (str_line.empty())
		{
			continue;
		}
		vec_data.push_back(str_line);
	}
	ifs.close();
	if (vec_data.size() <= 1)
	{
		return false;
	}
	vec_data.erase(vec_data.begin());
	return true;
}

bool FileHelper::create_file(const std::string &str_file_name) const
{
	FILE *p_file_out;
	p_file_out = fopen(str_file_name.c_str(), "wb+");
	if (p_file_out == NULL)
	{
		printf("open Save %s failed.", str_file_name.c_str());
		return false;
	}
	fwrite("Server Start Up succeed ...", sizeof("Server Start Up succeed ..."), 1, p_file_out);
	fclose(p_file_out);

	return true;
}