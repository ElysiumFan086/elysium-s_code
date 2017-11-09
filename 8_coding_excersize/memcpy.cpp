/**
 * An implementation of 'memcpy()' by myself. As is considered, the source address and 
 * destination adress may be overlapped. According to the standard of ANSI, the copying 
 * result must be undefined in such cases. And more importantly, pointer with the type 
 * of 'void*' cannot be operated with plus-like operator.
 */

void* memcpy(void* p_src, void* p_dst, std::size_t n_size) {
	if(p_src == NULL || p_dst == NULL || n_size == 0)
		return NULL;

	unsigned char* p_cpy_dst = static_cast<unsigned char*>(p_dst);
	const unsigned char* p_cpy_src = static_cast<const unsigned char*>(p_src);

	bool is_over_1 = (p_cpy_dst > p_cpy_src) && (p_cpy_src + n_size > p_cpy_dst);
	bool is_over_2 = (p_cpy_src > p_cpy_dst) && (p_cpy_dst + n_size > p_cpy_src);
	if(is_over_1 || is_over_2) {
		return NULL;
	}

	while(n_size--) {
		*p_cpy_dst = *p_cpy_src;
		++p_cpy_dst;
		++p_cpy_src;
	}

	return p_dst;
}

void* memmove(void* p_src, void* p_dst, std::size_t n_size) {
	if(p_src == NULL || p_dst == NULL || n_size == 0)
		return NULL;

	unsigned char* p_cpy_dst = static_cast<unsigned char*>(p_dst);
	const unsigned char* p_cpy_src = static_cast<const unsigned char*>(p_src);

	bool is_over_1 = (p_cpy_dst > p_cpy_src) && (p_cpy_src + n_size > p_cpy_dst);
	bool is_over_2 = (p_cpy_src > p_cpy_dst) && (p_cpy_dst + n_size > p_cpy_src);
	if(is_over_1 || is_over_2) {
		while(n_size) {
			*(p_cpy_dst + n_size - 1) = *(p_cpy_src + n_size -1);
			--n_size;
		}
	} else {
		while(n_size--) {
			*p_cpy_dst = *p_cpy_src;
			++p_cpy_dst;
			++p_cpy_src;
		}
	}
	return p_dst;
}