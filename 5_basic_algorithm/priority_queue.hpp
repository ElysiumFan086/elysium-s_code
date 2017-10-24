#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_

#include <limit.h>
#include <unordered_map>
#include <vector>

template<typename T, typename V>
class MaxHeap{
public:
	bool heap_maximum(V& n_element){
		if(vec_heap_data.empty())
			return false;

		T max_index = vec_heap_data[0];
		n_element = map_hash_table[max_index];
		return true;
	}

	bool heap_pop_max(V& n_max_element){
		if(vec_heap_data.empty())
			return false;

		T max_index = vec_heap_data[0];
		n_max_element = map_hash_table[max_index];

		map_hash_table.erase(max_index);
		if(vec_heap_data.size() > 1){
			auto itr_last = vec_heap_data.end() - 1;
			vec_heap_data[0] = *itr_last;
			vec_heap_data.erase(itr_last);

			max_heapify(0);
		}
		else{
			vec_heap_data.clear();
		}

		return true;
	}

	bool heap_increase_key(int n_idx, T key){
		if(vec_heap_data.empty() || n_idx >= vec_heap_data.size())
			return false;
		if(vec_heap_data[n_idx] > key){
			return false;
		}

		vec_heap_data[n_idx] = key;
		while(n_idx > 0 && vec_heap_data[get_parent(n_idx)] < vec_heap_data[n_idx]){
			swap(n_idx, get_parent(n_idx));
			n_idx = get_parent(n_idx);
		}

		return true;
	}

	void heap_insert(T key, V value){
		// Insert a new value with the smallest value of type T
		vec_heap_data.emplace_back(MIN_VALUE_FOR_T);
		heap_increase_key(vec_heap_data/size() - 1, key);
		map_hash_table[key] = value;
	}

	std::size_t get_heap_size() const {
		return vec_heap_data.size();
	}


	MaxHeap(const MaxHeap&) = delete;
	MaxHeap& operator=(const MaxHeap&) = delete;

private:
	std::size_t get_parent(std::size_t n){
		return (n - 1) / 2;
	}

	std::size_t get_left_child(std::size_t n){
		return 2 * n + 1;
	}

	std::size_t get_right_child(std::size_t n){
		return 2 * n + 2;
	}

	void swap(std::size_t n_from, std::size_t n_to){
		if(n_from < vec_heap_data.size() && n_to < vec_heap_data.size()){
			T temp = vec_heap_data[n_from];
			vec_heap_data[n_from] = vec_heap_data[n_to];
			vec_heap_data[n_to] = temp;
		}
	}

	void max_heapify(std::size_t n_root){
		std::size_t n_lchild = get_left_child(n_root);
		std::size_t n_rchild = get_right_child(n_root);
		std::size_t n_heap_size = vec_heap_data.size();

		std::size_t n_large_node = n_root;
		if(n_lchild < n_heap_size && vec_heap_data[n_lchild] > vec_heap_data[n_root]){
			n_large_node = n_lchild;
		}

		if(n_rchild < n_heap_size && vec_heap_data[n_rchild] > vec_heap_data[n_large_node]){
			n_large_node = n_rchild;
		}

		if(n_large_node != n_root){
			T n_temp = vec_heap_data[n_large_node];
			vec_heap_data[n_large_node] = vec_heap_data[n_root];
			vec_heap_data[n_root] = n_temp;

			max_heapify(n_large_node);
		}
	}

	std::vector<T> vec_heap_data;
	std::unordered_map<T, V> map_hash_table;
}

#endif