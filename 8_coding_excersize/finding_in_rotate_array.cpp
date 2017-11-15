/**
    Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
    (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
    Find the minimum element.
*/

int findMin(vector<int>& nums) {
        if(nums.size() == 1)    return nums[0];
        
        int n_left = 0, n_right = nums.size() - 1;
        if(nums[n_left] > nums[n_right]) {
            // Not sure which side may be the MIN, so keep both and compare(that is why use 'n_left != n_right - 1')
            while(n_left != n_right - 1) {
                int n_mid = (n_left + n_right) / 2;
                // Unlike binary search, here we do not compare with 'nums[n_mid]', so 'n_mid' is directly 
                // assigned to 'n_left' or 'n_right', without plus or minus 1.
                if(nums[n_mid] > nums[n_right])         // The rotate pivot is in right side
                    n_left = n_mid;
                else if(nums[n_mid] < nums[n_right])    // The rotate pivot is in left side
                    n_right = n_mid;
                else                                    // If there is duplicate, skip the right bound element
                    --n_right;
            }
            
            return std::min(nums[n_left], nums[n_right]);
        }
        else {
            return nums[0];
        }
}

/**
    Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
    (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
    Write a function to determine if a given target is in the array.
    The array may contain duplicates.
*/

bool search(vector<int>& nums, int target) {
        if(nums.empty())  return false;
        
        if(nums.size() == 1)  return nums[0] == target;
        
        int n_left = 0, n_right = nums.size() - 1;
        while(n_left <= n_right) {
            int n_mid = (n_left + n_right) / 2;
            if(nums[n_mid] == target)    return true;
            else if(nums[n_mid] < nums[n_right]) {
            // Rotate pivot is in the left side
                if(nums[n_mid] < target && target <= nums[n_right])  n_left = n_mid + 1;
                else n_right = n_mid - 1;
            } else if(nums[n_mid] > nums[n_right]){
            // Rotate pivot is in the right side
                if(nums[n_left] <= target && target < nums[n_mid])    n_right = n_mid - 1;
                else n_left = n_mid + 1;
            } else {
                --n_right;
            }
        }
        
        return false;
}

/**
 Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
 (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 You are given a target value to search. If found in the array return its index, otherwise return -1.
 You may assume no duplicate exists in the array.
*/
 
 int search(vector<int>& nums, int target) {
        if(nums.empty())  return -1;
        
        if(nums.size() == 1)  return nums[0] == target ? 0 : -1;
        
        int n_left = 0, n_right = nums.size() - 1;
        while(n_left <= n_right) {
            int n_mid = (n_left + n_right) / 2;
            if(nums[n_mid] == target)    return n_mid;
            else if(nums[n_mid] < nums[n_right]) {
                if(nums[n_mid] < target && target <= nums[n_right])  n_left = n_mid + 1;
                else n_right = n_mid - 1;
            } else {
                if(nums[n_left] <= target && target < nums[n_mid])    n_right = n_mid - 1;
                else n_left = n_mid + 1;
            }
        }
        
        return -1;
}
