/**
 * There are N children standing in a line. Each child is assigned a rating value. 
 * You are giving candies to these children subjected to the following requirements: 
 * Each child must have at least one candy.
 * Children with a higher rating get more candies than their neighbors.
 * What is the minimum candies you must give? 
 */
 
int candy(std::vector<int>& ratings) {
	if (ratings.empty())      return 0;
	if (ratings.size() == 1)  return 1;
	std::size_t n_size = ratings.size();

	std::vector<int> vec_res = std::vector<int>(n_size, 1);
	for (std::size_t i = 1; i < n_size; ++i) {
		if (ratings[i] > ratings[i - 1])
			vec_res[i] = std::max(vec_res[i], vec_res[i - 1] + 1);
	}
    
    // NOTE: do NOT use std::size_t for 'i' in reverse tranversing
	for (int i = n_size - 2; i >= 0; --i) {
		if (ratings[i] > ratings[i + 1]) {
			vec_res[i] = std::max(vec_res[i], vec_res[i + 1] + 1);
		}
	}

	int n_sum = 0;
	for (auto itr = vec_res.begin(); itr != vec_res.end(); ++itr)
		n_sum += *itr;

	return n_sum;
}
