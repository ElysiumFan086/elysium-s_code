/**
 * Giving an array with size 'n', all the elements in array are from 1 to n, but some numbers
 * repeate many times, while some are missing. Finding every numbers' frequency with time cost 
 * O(n) and memory cost O(1).
 */
 
void count_number_frequency(int* p_data, std::size_t n_size, std::vector<int>& vec_res) {
    if(p_data == NULL || n_size == 0)    return;
    
    for(std::size_t i = 0; i < n_size; ++i){
        vec_res.push_back(p_data * n_size);
    }
    
    for(std::size_t i = 0; i < n_size; ++i){
        vec_res[vec_res[i] / n_size] += 1;
    }
    
    for(std::size_t i = 0; i < n_size; ++i){
        vec_res[i] %= n_size;
    }
}
