/**
 * Possible implement of STL algorithm : std::remove_if
 */
 
template<class ForwardIterator, class UnaryPredict>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, UnaryPredict pred) {
	ForwardIterator result = first;
	while(first != last) {
		if(pred(*first) == false) {
			*result = std::move(*first);
			++result;
		}
		++first;
	}

	return result;
}

//Example: Remove elements less than 100 in a vector
void remove_element(std::vector<int>& vec_data) {
	vec_data.erase(
		std::remove_if(
			vec_data.begin(), 
			vec_data.end(), 
			std::bind2nd(std::less<int>, 100)), 
		vec_data.end());
}
