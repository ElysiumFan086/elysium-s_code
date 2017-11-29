

/**
Possible implementation in STL

template<class BidirIt>
bool next_permutation(BidirIt first, BidirIt last)
{
    if (first == last) return false;
    BidirIt i = last;
    if (first == --i) return false;
 
    while (true) {
        BidirIt i1, i2;
 
        i1 = i;
        if (*--i < *i1) {
            i2 = last;
            while (!(*i < *--i2));
            std::iter_swap(i, i2);
            std::reverse(i1, last);
            return true;
        }
        if (i == first) {
            std::reverse(first, last);
            return false;
        }
    }
}

*/

bool get_next_permutation(char* p_perm, int n_size) {
	int i = 0;
	// [1] Finding the last(right most) ascend order position 'i', which makes a[i] <= a[i+1]
	for(i = n_size - 2; i >= 0 && p_perm[i] > p_perm[i + 1]; --i);

	// Have listed all the permutaion number
	if(i < 0)    return false;

	int k = 0;
	// [2] Find the right most element 'k', which makes a[k] > a[i]
	for(k = n_size - 1; K >= 0 && p_perm[k] <= p_perm[i]; --k);

	// [3] Swapping the element at postion 'i' and 'k'
	std::swap(p_perm[i], p_perm[k]);
	// [4] Reverse the substring from position 'i' to the end of the string
	std::reverse(p_perm + i + 1, p_perm + n_size);
}

template<class BidirItr>
bool next_permutation(BidirItr first, BidirItr last) {
        const auto rfirst = reverse_iterator<BidirItr>(last);
        const auto rlast  = reverse_iterator<BidirItr>(first);
        
        auto pivot = std::next(rfirst);
        while(pivot != rlast && *pivot >= *std::prev(pivot))    ++pivot;
        
        if(pivot == rlast) {
            std::reverse(rfirst, rlast);
            return false;
        }
        
        auto change = std::find_if(rfirst, pivot, std::bind1st(std::less<int>(), *pivot));
        
        std::swap(*change, *pivot);
        std::reverse(rfirst, pivot);
        
        return true;
}
