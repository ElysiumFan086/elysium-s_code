std::vector<std::vector<int>> find_four_sum(std::vector<int>& vec_num, int n_target) {
	int n_size = vec_num.size();
	std::vector<std::vector<int>> vec_res;

	std::unordered_map<int, std::vector<std::pair<int, int>>> hash_pairs;
	hash_pairs.reserve(n_size * n_size);
	std::sort(vec_num.begin(), vec_num.end());

	for(int i = 0; i < n_size; ++i)
		for(int j = i + 1; j < n_size; ++j)
			hash_pairs[vec_num[i] + vec_num[j]].push_back(std::make_pair(i, j));

	for(int i = 0; i < n_size - 3; ++i) {
		if(i != 0 && vec_num[i] == vec_num[i - 1])    continue;
		for(int j = i + 1; j < n_size - 2; ++j) {
			if(j != i + 1 && vec_num[j] == vec_num[j - 1])    continue;

			if(hash_pairs.find(n_target - vec_num[i] - vec_num[j]) != hash_pairs.end()) {
				std::vector<std::pair<int, int>>& vec_sum2 = 
				    hash_pairs[n_target - vec_num[i] - vec_num[j]];
				bool is_first_push = true;
				for(int k = 0; k < vec_sum2.size(); ++k) {
					if(vec_sum2[k].first <= j)    continue;
					if(is_first_push || (vec_res.back())[2] != vec_num[vec_sum2[k].first]) {
						vec_res.push_back(std::vector<int> {
							vec_num[i], vec_num[j], 
							vec_num[vec_sum2[k].first], 
							vec_num[vec_sum2[k].second]
						});
						is_first_push = false;
					}
				}
			}
		}
	}

	return vec_res;
}