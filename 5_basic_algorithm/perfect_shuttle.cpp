
void location_replace(int* p_idx, std::size_t n_pair_size) {
	if(p_idx == NULL || n_pair_size == 0)
		return;
	std::size_t n_length = n_pair_size << 2;
	int* p_after = new int[n_length + 1];
	memset(p_after, 0, n_length * sizeof(int));

	for(int i = 1; i < n_length; ++i) {
		p_after[(i * 2) % (n_length + 1)] = p_idx[i];
	}

	for(int i = 1; i < n_length; ++i) {
		p_idx[i] = p_after[i];
	}

	delete[] p_after;
	p_after = NULL;
}

void reverse_str(int* p_array, std::size_t n_from, std::size_t n_to) {
	if(p_array == NULL || n_from < n_to)
		return;

	int n_temp = 0;
	while(n_from < n_to) {
		n_temp = p_array[n_from];
		p_array[n_from] = p_array[n_to];
		p_array[n_to] = n_temp;

		++n_from;
		--n_to;
	}
}

void right_rotate(int* p_data, std::size_t n_length, std::size_t n_pivot) {
	if(p_data == NULL || n_length == 0 || n_pivot > n_length)
		return;

	reverse_str(p_data, 1, n_length - n_pivot);
	reverse_str(p_data, n_length - n_pivot + 1, n_length);
	reverse_str(p_data, 1, n_length);
}

/**
 * For given pair number 'n', the total length is 2*n.
 * If there exits 'k', make 2*n=(3^k)-1, then, there are k
 * cycles in the array.
 *
 * Example:
 *     1  2  3  4  5  6  7  8
 *   There are two cycles in this array, because 2*4 = 3^2 - 1 = 8.
 *   The first one is:
 *      1 -> 2 -> 4 -> 8 -> 7 -> 5 -> 1
 *   The second one is:
 *      3 -> 6 -> 3
 *
 * The cycle's head is: 1, 3, ... , 3^(k-1)
 */
void cycle_leader(int* p_idx, std::size_t n_from, int n_mod) {
	int n_last_idx = p_idx[n_from];
	int n_temp = 0;
	for(int i = n_from * 2 % n_mod; i != n_from;) {
		n_temp = p_idx[i];
		p_idx[i] = n_last_idx;
		n_last_idx = n_temp;

		i = (2 * i) % n_mod;
	}

	p_idx[n_from] = n_last_idx;
}