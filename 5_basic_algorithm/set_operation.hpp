// Set operation

/**
 * Usage:
 *   std::vector<int> v1{1,2,3,4,5,6,7,8};
 *   std::vector<int> v2{        5,  7,  9,10};
 *   std::sort(v1.begin(), v1.end());
 *   std::sort(v2.begin(), v2.end());
 *
 *   std::vector<int> v_intersection;
 *
 *   set_intersection(v1.begin(), v1.end(),
 *                    v2.begin(), v2.end(),
 *                    std::back_inserter(v_intersection));
 */
template <class InputIt1, class InputIt2, class OutputIt, class Comparable>
void set_intersection(
	InputIt1 first1,    InputIt1 last1, 
	InputIt2 first2,    InputIt2 last2,
	OutputIt out_first, Comparable compare) {
	while(first1 != last1 && first2 != last2) {
		if(compare(*first1, *first2)) {
			++first1;
		} else {
			if(!compare(*first2, *first1)) {
				*out_first++ = *first1++;
			}
			++first2;
		}
	}

	return out_first;
}

template <class InputIt1, class InputIt2, class OutputIt, class Comparable>
OutputIt set_union(
	InputIt1 first1,    InputIt1 last1, 
	InputIt2 first2,    InputIt2 last2,
	OutputIt out_first, Comparable compare) {
	for(; first1 != last1; ++out_first) {
		if(first2 == last2) {
			return std::copy(first1, last1, out_first);
		}
		if(compare(*first2, *first1)) {
			*out_first = *first2++;
		} else {
			*out_first = *first1;
			if(!compare(*first1, *first2))
				++first2;
			++first1;
		}
	}

	return std::copy(first2, last2, out_first);
}
