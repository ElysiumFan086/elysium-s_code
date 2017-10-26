/** 
 *  Finding two numbers in an array, which satisties that their sum equals to a ginven number.
 *  Return the postion of these two number in array.
 *  NOTE: it is position, not indexing!
 */

#include <unordered_map>
#include <vector>

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> hash_table;
    int i = 0;
    for(auto itr = nums.begin(); itr != nums.end(); ++itr) {
        if(hash_table.count(target - nums[i])) {
            return {i, hash_table[target - nums[i]]};
        }
        hash_table[nums[i]] = i;
        ++i;
    }
    return {};
}
