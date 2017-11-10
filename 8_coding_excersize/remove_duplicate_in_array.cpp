/** 
 * Given a sorted array, remove the duplicates in-place such that each element appear only once and return the new length.
 * Do not allocate extra space for another array, you must do this by modifying the input array in-place with O(1) extra memory.
 */

std::vector<int>::iterator unique(std::vector<int>::iterator first,std::vector<int>::iterator last) {
    if(first == last)  return last;
        
    std::vector<int>::iterator result = first;
    while(++first != last) {
        if( (*result == *first) == false) {
            *(++result) = *first;
        }
    }
        
    return ++result;
}
    
int removeDuplicates(vector<int>& nums) {
    return std::distance(nums.begin(), unique(nums.begin(), nums.end()));
}
