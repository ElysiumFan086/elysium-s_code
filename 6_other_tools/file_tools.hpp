#ifndef _FILE_HELPER_H_
#define _FILE_HELPER_H_

#include <fstream>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

#include <singleton.hpp>

class FileHelper : public Singleton<FileHelper>
{
public:
	FileHelper() { };
	~FileHelper() { };

public:

	bool traverse_path(
		std::vector<std::string> &vec_file_name, 
		const std::string& str_path, 
		const std::string& str_file_type = "") const;

	bool is_file_exist(
		const std::string& str_path, 
		const std::string& str_file_name) const;

	bool is_file_exist(
		const std::string& str_file_name) const;

	bool get_dir_files(
		const        std::string& str_dir_path, 
		std::vector<std::string>& vec_file_names);

	bool delete_file(
		const std::string& str_path, 
		const std::string& str_file_name) const;

	bool delete_file(
		const std::string& str_file_name) const;

	bool delete_directory(
		const std::string& str_path_name) const;

	bool create_directory(
		const std::string& str_path_name) const;

	void copy_file(
		const std::string& str_file_src, 
		const std::string& str_file_dst) const;

	void copy_directory(
		const std::string& str_path_src, 
		const std::string& str_path_dst) const;

	bool change_file_type(
		const std::string& str_file_name, 
		const std::string& str_type_src, 
		const std::string& str_type_dst, 
		std::string&       str_changed_name) const;

	bool read_file(
		const std::string& str_file_name, 
		std::vector<std::string>& vec_data);

	bool create_file(
		const std::string& str_file_name) const;

private:
	bool is_file_type(
		const std::string& str_file_name, 
		const std::string& str_file_type) const; 
};

#endif