#ifndef _STR_TOOLS_H_
#define _STR_TOOLS_H_

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>
#include <functional>

int is_space(int const c)
{
	return (c >= -127 && c <= 127 && isspace(c) != 0);
}

void trim(std::string &str_input)
{
	str_input.erase(
		str_input.begin(), 
		std::find_if(str_input.begin(), str_input.end(), 
		std::not1(std::ptr_fun<int, int>(is_space))));
}

void replace(
	std::string &str_input,
	const char  *p_old_str, std::size_t n_len_old,
	const char  *p_new_str, std::size_t n_len_new)
{
	std::string::size_type pos = 0;
	while ((pos = str_input.find(p_old_str, pos)) != std::string::npos) {
		str_input.replace(pos, n_len_old, p_new_str);
		pos = pos + n_len_new;
	}
}

void split(const std::string &str_input, char delim, std::vector<std::string>& vec_split_str)
{
	std::stringstream ss;
	ss.str(str_input);
	std::string str_item;
	while (std::getline(ss, str_item, delim))
	{
		vec_split_str.push_back(str_item);
	}
}

#endif