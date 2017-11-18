
void find_two_sum(std::vector<int>& vec_sort_array, int n_start, int n_target, std::vector<std::vector<int>>& vec_res) {
	int n_head = n_start, n_tail = vec_sort_array.size() - 1;
	while(n_head < n_tail) {
		int n_temp = vec_sort_array[n_head] + vec_sort_array[n_tail];
		if(n_temp < n_target)         ++n_head;
		else if(n_temp > n_target)    --n_tail;
		else {
			vec_res.push_back(std::vector<int>{
				vec_sort_array[n_start - 1], 
				vec_sort_array[n_head],
				vec_sort_array[n_tail]
			});

			// After finding a result triblet, filtering the same element new the bound
			int k = n_head + 1;
			while(k < n_tail && vec_sort_array[k] == vec_sort_array[n_head])  ++k;
			n_head = k;

			k = n_tail - 1;
			while(k > n_head && vec_sort_array[k] == vec_sort_array[n_tail])  --k;
			n_tail = k;
		}
	}
}

std::vector<std::vector<int>> find_three_sum(int n_target, std::vector<int>& vec_num) {
	int n_size = vec_num.size();
	std::sort(vec_num.begin(), vec_num.end());
	std::vector<std::vector<int>> vec_res;
	for(int i = 0; i < n_size - 2; ++i) {
		if(i > 0 && vec_num[i] == vec_num[i - 1])  continue;
		int n_target_2 = n_target - vec_num[i];
		find_two_sum(vec_num, i + 1, n_target_2, vec_res);
	}

	return vec_res;
}

/******************************************************************************************************************/
/*                      Finding 3 numbers' sum that is closed to target value                                     */
/******************************************************************************************************************/

int find_two_sum(std::vector<int>& vec_sort_array, int n_start, int n_target) {
	int n_head = n_start, n_tail = vec_sort_array.size() - 1;
	int n_distance = INT_MAX, n_res = 0;

	while(n_head < n_tail) {
		int n_temp = vec_sort_array[n_head] + vec_sort_array[n_tail];
		if(n_temp < n_target) {
			if(n_target - n_temp < n_distance) {
				n_distance = n_target - n_temp;
				n_res = n_temp;
			}
			n_head++;
		} else if(n_temp > n_target) {
			if(n_temp - n_target < n_distance) {
				n_distance = n_temp - n_target;
				n_res = n_temp;
			}
			n_tail--;
		}
		else {
			return n_target;
		}
	}

	return n_res;
}

int find_three_sum(std::vector<int>& vec_num, int n_target) {
	int n_size = vec_num.size();
	std::sort(vec_num.begin(), vec_num.end());
	int n_distance = INT_MAX, n_res = 0;

	for(int i = 0; i < n_size - 2; ++i) {
		int n_target_2 = n_target - vec_num[i];
		int n_result_2 = find_two_sum(vec_num, i + 1, n_target_2);
		int n_temp_dist = abs(n_result_2 - n_target_2);

		if(n_temp_dist < n_distance) {
			n_distance = n_temp_dist;
			n_res = vec_num[i] + n_result_2;
			if(n_res == n_target)    return n_res;
		}
	}

	return n_res;
}