/** LeetCode Problem 84:
 * Given n non-negative integers representing the histogram's bar height where the width of each 
 * bar is 1, find the area of largest rectangle in the histogram. 
 *
 *		 +--+--+--+--+--+--+--+
 *		 [0]|##|##|  |  |  |  |   2
 *		 +--+--+--+--+--+--+--+
 *		 [1]|##|  |  |  |  |  |   1
 *		 +--+--+--+--+--+--+--+
 *		 [2]|##|##|##|##|##|  |   5
 *		 +--+--+--+--+--+--+--+
 *		 [3]|##|##|##|##|##|##|   6
 *		 +--+--+--+--+--+--+--+
 *		 [4]|##|##|  |  |  |  |   2
 *		 +--+--+--+--+--+--+--+
 *		 [5]|##|##|##|  |  |  |   3
 *		 +--+--+--+--+--+--+--+
 *
 * Above is a histogram where width of each bar is 1, given height = [2,1,5,6,2,3].
 */
int largestRectangleArea(std::vector<int> &vec_height) {
		vec_height.push_back(0);
		std::stack<int>  stk_height_idx;
		int n_max_area = 0;
		int i = 0;
		while(i < vec_height.size()) {
				if(stk_height_idx.empty() || vec_height[stk_height_idx.top()] <= vec_height[i]) {
						stk_height_idx.push(i++);
				}
				else {
						int n_top = stk_height_idx.top();
						stk_height_idx.pop();
						n_max_area = max(n_max_area, vec_height[n_top] * (stk_height_idx.empty() ? i : i - stk_height_idx.top() - 1));
				}
		}
		
		return n_max_area;
}

int maximalRectangle(std::vector<std::vector<char>>& vec_matrix){
		if (vec_matrix.empty() || vec_matrix[0].empty()) return 0;
    int n_res = 0, n_rows = vec_matrix.size(), n_cols = vec_matrix[0].size();
    
    std::vector<int> vec_height(n_cols + 1, 0);
		for (int i = 0; i < n_rows; ++i) {
				std::stack<int> s;
				for (int j = 0; j < n_cols + 1; ++j) {
						if(j < n_cols) {
							vec_height[j] = vec_matrix[i][j] == '1' ? height[j] + 1 : 0;
						}
						
						while(!s.empty() && height[s.top()] >= height[j]) {
								int n_top = s.top();
								s.pop();
								n_res = max(n_res, vec_height[n_top] * (s.empty() ? j : (j - s.top() - 1)));
						}
						
						s.push(j);
				}
		}
		
		return n_res;
}


