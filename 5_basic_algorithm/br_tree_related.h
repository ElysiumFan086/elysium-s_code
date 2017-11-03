/**
   LEFT-ROTATE(T, x)  
1   y ← right[x]            // Set y.  
2   right[x] ← left[y]      // Turn y's left subtree into x's right subtree.  
3   p[left[y]] ← x  
4   p[y] ← p[x]             // Link x's parent to y.  
5   if p[x] = nil[T]  
6       then root[T] ← y  
7   else 
8         if x = left[p[x]]  
9            then left[p[x]] ← y  
10        else right[p[x]] ← y  
11  left[y] ← x             // Put x on y's left.  
12  p[x] ← y 
*/

typedef bool __rb_tree_color_type;
const __rb_tree_color_type  __rb_tree_red   = false;
const __rb_tree_color_type  __rb_tree_black = true;

struct _rb_tree_node_base {
	typedef __rb_tree_color_type color_type;
	typedef __rb_tree_node_base* base_ptr;

	color_type color;
	base_ptr   parent;
	base_ptr   left;
	base_ptr   right;

	static base_ptr minimum(base_ptr x) {
		while (x->left != 0)  x = x->left;
		return x;
	}

	static base_ptr maximum(base_ptr x) {
		while (x->right != 0)  x = x->right;
	}
};

template <class Value>
struct __rb_tree_node : public __rb_tree_node_base {
	typedef __rb_tree_node<Value>* link_type;

	Value value_field;
};

struct __rb_tree_base_iterator
{
	typedef __rb_tree_node_base::base_ptr base_ptr;
	typedef bidirectional_iterator_tag    iterator_category;
	typedef ptrdiff_t                     difference_type;

	base_ptr node;

	void increment() {
		if (node->right != 0) {                // CASE 1: if node has right child,
			node = node->right;                // first find in the right sub-tree 
			while (node->left != 0)            // and then go alone to buttom
				node = node->left;             // of left, you can get the result.
		}                                      // (That is finding the minimum node in right sub-tree)
		else {
			base_ptr y = node->parent;         // CASE 2: if node has no right child
			while (node == y->right) {         // Finding its parent node.
				node = y;                      // Searching up backward until a node who is
				y = y->parent;                 // not the right child of its perent.
			}
			if (node->right != y)              // CASE 3: if right child is not current parent node, return parent;
				node = y;
		}                                      // CASE 4: otherwise, node is we want to find
	}

	void decrement() {
		if (node->color == __rb_tree_red &&    // CASE 1: if node is RED and its parent is itself
			 node->parent->parent == node)     // Right child is the solution.
		    node = node->right;                // This occasion means node is the 'header'.
		// We define header as the end iterator, whose right child is the mostright, that is the max node in tree.
		else if (node->left != 0) {            // CASE 2: If has left child
			base_ptr y = node->left;           // Make 'y' points to left child
			while (y->right != 0)              // If 'y' has right sub-tree
				y = y->right;                  // go to the most right.
			node = y;                          // This is to say the max node in left sub-tree is the answer.
		}
		else {                                 // CASE 3: Neither root nor with left child
			base_ptr y = node->parent;         // Find parent node 
			while (node == y->left) {          // If current node is left child of its parent
				node = y;                      // Find upward, and until current node is
				y = y->parent;                 //  not the left child of its parent. 
			}
			node = y;                          // Finally get the answer.
		}

	}
};

template <class Value, class Ref, class Ptr>
struct __rb_tree_iterator : public __rb_tree_base_iterator 
{
	typedef Value value_type;
	typedef Ref   reference;
	typedef Ptr   pointer;

	typedef __rb_tree_iterator<Value, Value&, Value*>             iterator;
	typedef __rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
	typedef __rb_tree_iterator<Value, Ref, Ptr>                   self;
	typedef __rb_tree_node<Value>*                                link_type;

	__rb_tree_iterator() {}
	__rb_tree_iterator(link_type x) { node = x; }
	__rb_tree_iterator(const iterator& it) { node = it.node; }

	reference operator*() const {
		return link_type(node)->value_field;
	}
	#ifndef __SGI_STL_NO_ARRAY_OPERATOR
		pointer operator->() const {
			return &(operator*());
		}
	#endif

	self& operator++() { increment(); return *this; }
	self  operator++(int) {
		self temp = *this;
		increment();
		return temp;
	}

	self& operator--() { decrement();  return *this; }
	self  operator--(int) {
		self temp = *this;
		decrement();
		return temp;
	}
};