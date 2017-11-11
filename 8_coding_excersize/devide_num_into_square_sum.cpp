/**
 * Given a number 'n', representing it with the form of several square numbers' num.
 * Calculate the minimum number, such as:
 *         12 = 2^2 + 2^2 + 2^2; 
 * So the anwser is 3.
 */

#include <vector>
#include <limits.h>
#include <algorithm>

int find_min_sum(int n) {
	if(n < 0)    return -1;
	if(n <= 1)	 return 1;
	
	// dp[i] means the number of  needed square number
	std::vector<int> vec_dp(n + 1, INT_MAX);
	vec_dp[0] = 0;
	for(int i = 1; i < n + 1; ++i) {
		int j = 1;
		while(j * j <= i) {
			vec_dp[i] = std::min(vec_dp[i], vec_dp[i - j * j] + 1);
			++j;
		}
	}
	
	return vec_dp[n];
}