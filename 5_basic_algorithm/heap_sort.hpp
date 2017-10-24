#ifndef _HEAP_SORT_H_
#define _HEAP_SORT_H_

/************************************************************************
   The following code is based on the book of data structure.
 ************************************************************************/

void adjust_heap(int* p_data, std::size_t n_pivot, std::size_t n_size){
	int n_temp = p_data[n_pivot];
	for(std::size_t k = n_pivot * 2 + 1; k < n_size; k = k * 2 + 1){
		if(k + 1 < n_size && p_data[k] < p_data[k + 1])
			++k;

		if(p_data[k] > n_temp){
			p_data[n_pivot] = p_data[k];
			n_pivot = k;
		}
		else{
			break;
		}
	}

	p_data[n_pivot] = n_temp;
}

void swap(int* p_data, std::size_t n_from, std::size_t n_to){
	int n_temp = p_data[n_from];
	p_data[n_from] = p_data[n_to];
	p_data[n_to] = n_temp;
}

void heap_sort(int* p_data, std::size_t n_size){
	if(p_data == NULL || n_size == 0)	return;

	for(std::size_t i = n_size / 2 - 1; i >= 0; --i){
		adjust_heap(p_data, i, n_size);
	}

	for(std::size_t i = n_size - 1; i > 0; --i){
		swap(p_data, 0, i);

		adjust_heap(p_data, 0, i);
	}
}

/************************************************************************
   The following code is based on the book of 'Introduction of Algorithm'
 ************************************************************************/

int get_parent(int n){
	return (n - 1) / 2;
}

int get_left_child(int n){
	return 2 * n + 1;
}

int get_right_child(int n){
	return 2 * n + 2;
}

/**
 * Make the sub-tree rooted as node 'n_root' a max-heap. If the sub-tree contains N
 * nodes, this procedure's time costing is O[log(n)], which can be also regarded as
 * O[h], here 'h' meanes the hight of sub-tree.
 */
void max_heapify(int* p_data, int n_heap_size, int n_root){
	int n_lchild = get_left_child(n_root);
	int n_rchild = get_right_child(n_root);

	int n_large_node = n_root;
	if(n_lchild < n_heap_size && p_data[n_lchild] > p_data[n_root]){
		n_large_node = n_lchild;
	}

	if(n_rchild < n_heap_size && p_data[n_rchild] > p_data[n_large_node]){
		n_large_node = n_rchild;
	}

	if(n_large_node != n_root){
		int n_temp = p_data[n_large_node];
		p_data[n_large_node] = p_data[n_root];
		p_data[n_root] = n_temp;

		max_heapify(p_data, n_heap_size, n_large_node);
	}
}

void build_max_heap(int* p_data, int n_size){
	for(int i = n_size / 2 - 1; i >= 0; --i){
		max_heapify(p_data, n_size, i);
	}
}

void heap_sort_v2(int* p_data, int n_size){
	build_max_heap(p_data, n_size);
	for(int i = n_size - 1; i >= 1; --i){
		swap(p_data, 0, i);
		max_heapify(p_data, i, 0);
	}
}

#endif