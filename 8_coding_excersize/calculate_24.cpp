#include <vector>

bool search_24_dfs(std::vector<double>& vec_data, int n_current_len) {
	if(n_current_len == 1) {
		if(fabs(vec_data[0] - 24.0) < 1e-7)    return true;
		else return false;
	}

	for(int i = 0; i < n_current_len; ++i) {
		for(int j = i + 1; j < n_current_len; ++j) {
			double f_opt_a = vec_data[i];
			double f_opt_b = vec_data[j];
			vec_data[j] = vec_data[n - 1];
			vec_data[i] = f_opt_a + f_opt_b;
			if(search_24_dfs(vec_data, n_current_len - 1))    return true;

			vec_data[i] = f_opt_a - f_opt_b;
			if(search_24_dfs(vec_data, n_current_len - 1))    return true;

			vec_data[i] = f_opt_a * f_opt_b;
			if(search_24_dfs(vec_data, n_current_len - 1))    return true;

			vec_data[i] = f_opt_b - f_opt_a;
			if(search_24_dfs(vec_data, n_current_len - 1))    return true;

			if(fabs(f_opt_a - 0.0) > 1e-7) {
				vec_data[i] = f_opt_b / f_opt_a;
				if(search_24_dfs(vec_data, n_current_len - 1))    return true;
			}

			if(fabs(f_opt_b - 0.0) > 1e-7) {
				vec_data[i] = f_opt_a / f_opt_b;
				if(search_24_dfs(vec_data, n_current_len - 1))    return true;
			}

			vec_data[i] = f_opt_a;
			vec_data[j] = f_opt_b;
		}

		return false;
	}
}
