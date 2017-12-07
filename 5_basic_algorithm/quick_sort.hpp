#ifndef _QUICK_SORT_H_
#define _QUICK_SORT_H_

std::size_t partition(int* p_data, std::size_t n_low, std::size_t n_high){
	int n_pivot = p_data[n_low];
	while(n_low < n_high){
		while(n_low < n_high && p_data[n_high] > n_pivot)  --n_high;
		p_data[n_low] = p_data[n_high];
		while(n_low < n_high && p_data[n_low] < n_pivot)   ++n_low;
		p_data[n_high] = p_data[n_low];
	}

	p_data[n_low] = n_pivot;

	return n_low;
}

void do_quick_sort(int* p_data, std::size_t n_low, std::size_t n_high){
	std::size_t n_pivot = 0;
	if(n_low < n_high){
		n_pivot = partition(p_data, n_low, n_high);
		do_quick_sort(p_data, n_low, n_pivot - 1);
		do_quick_sort(p_data, n_pivot + 1, n_high);
	}
}

void quick_sort(int* p_data, std::size_t n_size){
	if(p_data == NULL || n_size == 0)  return;

	do_quick_sort(p_data, 0, n_size - 1);
}

template<class ForwardIt, class UnaryPredict>
ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredict pred) {
	first = std::find_if_not(first, last, pred);
	if(first == last)    return first;

	for(auto i = std::next(first); i != last; ++i) {
		if(pred(*i)) {
			std::iter_swap(i, first);
			++first;
		}
	}

	return first;
}

template<class ForwardIt>
void quick_sort(ForwardIt first, ForwardIt last) {
	if(first == last)    return;
	auto pivot = std::next(first, std::distance(first, last) / 2);
	ForwardIt middle1 = partition(first, last, [pivot] (const auto& e) { return e < pivot; });
	ForwardIt middle2 = partition(middle1, last, [pivot] (const auto& e) { return !(e > pivot); });

	quick_sort(first, middle1);
	quick_sort(middle2, last);
}

#endif
