int maxSubArray(vector<int>& nums) {
    if(nums.size() == 1)
        return nums[0];
    int n_max = INT_MIN, n_current_max = 0;
    for(int i = 0; i < nums.size(); ++i){
        if(n_current_max >= 0)
            n_current_max += nums[i];
        else{
            n_current_max = nums[i];
            // Keep begin index here
        }
        
        if(n_current_max > n_max){
            n_max = n_current_max;
            // Keep end index here
        }
    }
    
    return n_max;
}