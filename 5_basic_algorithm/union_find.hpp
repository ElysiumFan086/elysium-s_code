#ifndef _UNION_FIND_H_
#define _UNION_FIND_H_

/**
 * This class encapsulate basic operations for a union-find set, which including 'union' and 'find'.
 * Here I make 'find()' a private function and expose a method called 'is_connected()' to user for 
 * connectivity test between to given nodes.
 * And the same time, this class keeps the number of connectivity components of the current graph.
 */
class UnionFind {
public:
	// Constructor
	UnionFind(unsigned int n_size) : n_vertex_nb(n_size) {
		if(n_vertex_nb == 0){
			p_parents = nullptr;
			p_height  = nullptr;
			n_component_nb = 0;
		}
		else{
			p_parents = new unsigned int[n_vertex_nb];
			p_height  = new unsigned int[n_vertex_nb];

			for(unsigned int i = 0; i < n_vertex_nb; ++i){
				p_parents[i] = i;
				p_height[i]  = 1;
			}
			n_component_nb = n_vertex_nb;
		}
	}

	/** 
	 * Union node A and node B into the same connected component
	 * NOTE: This implementation applies weighted quick-union method to make the component
	 *       after union as banlance as possible.
	 */
	void do_union(unsigned int n_node_a, unsigned int n_node_b){
		unsigned int n_parent_a = find(n_node_a);
		unsigned int n_parent_b = find(n_node_b);

		if(n_parent_b == n_parent_a)
			return;

		if(p_height[n_parent_a] > p_height[n_parent_b]){
			p_parents[n_parent_b] = n_parent_a;
			p_height[n_parent_b] += p_height[n_parent_a];
		}
		else{
			p_parents[n_parent_a] = n_parent_b;
			p_height[n_parent_a] += p_height[n_parent_b];
		}
		n_component_nb--;
	}

	/**
	 * Testing if node A and node B are in the same connected component. 
	 * In other word, if they are connected.
	 */
	bool is_connected(unsigned int n_node_a, unsigned int n_node_b){
		return find(n_node_a) == find(n_node_b);
	}

	/**
	 * Return the currently connected components number. 
	 */
	unsigned int get_component_nb(){
		return n_component_nb;
	}

	UnionFind& operator=(const UnionFind&) = delete;
	UnionFind(const UnionFind&) = delete;

private:
	/**
	 * Finding the parent node of given node, which is based on the fact that a node's 
	 * parent node is regarded as itself.
	 * NOTE: the finding process contains path compressing.
	 */
	unsigned int find(unsigned int n_node_id){
		unsigned int n_id = n_node_id;
		while(p_parents[n_id] != n_id){
			p_parents[n_id] = p_parents[p_parents[n_id]];
			n_id = p_parents[n_id];
		}
	}

	unsigned int* p_parents;	    // Arrays for every node's parent node
	unsigned int* p_height;         // Arrays for every node's height(also regarding as the size of current connected compenent)

	unsigned int n_vertex_nb;       // The total vertexes number of the set(or graph)
	unsigned int n_component_nb;    // Current connected components number
};

#endif