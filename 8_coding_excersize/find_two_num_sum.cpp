/** WARNING: This code is unfinished!!!
 *  Finding two numbers in an array, which satisties that their sum equals to a ginven number.
 *  Return the postion of these two number in array.
 *  NOTE: it is position, not indexing!
 */

#include <unordered_map>
#include <vector>

std::vector<int> twoSum(std::vector<int>& nums, int target){
	std::unordered_map<int, std::size_t> hash_table;
	for(std::size_t i = 0; i < nums.size(); ++i){
		hash_table[nums[i]] = i;
    }

    std::vector<int> vec_res;
    for(auto itr = nums.begin(); itr != nums.end(); ++itr){
    	if(hash_table.find(target - *itr) != hash_table.end()){
    		int n_a = hash_table[*itr];
    		int n_b = hash_table[target - *itr];
    		if(n_a < n_b){
    			vec_res.push_back(n_a);
    			vec_res.push_back(n_b);
    		}
    		else{
    			vec_res.push_back(n_b);
    			vec_res.push_back(n_a);
    		}
    		break;
    	}
    }

    return vec_res;
}
