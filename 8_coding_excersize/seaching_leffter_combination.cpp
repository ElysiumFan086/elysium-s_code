
void letter_combination_search(std::string str_digits, std::string str_dict[], int n_search_level, std::string str_out, std::vector<std::string>& vec_res) {
	if(n_search_level == str_digits.size())    vec_res.push_back(str_out);
	else {
		std::string str = str_dict[str_digits[n_search_level] - '2'];
		for(int i = 0; i < str.size(); ++i) {
			str_out.push_back(str[i]);
			letter_combination_search(str_digits, str_dict, n_search_level + 1, str_out, vec_res);
			str_out.pop_back();
		}
	}
}

std::vector<std::string> letter_combination(std::string str_digits) {
	std::vector<std::string> vec_res;
	if(str_digits.empty())    return vec_res;

	std::string str_dict[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
	letter_combination_search(str_digits, str_dict, 0, "", vec_res);

	return vec_res;
}