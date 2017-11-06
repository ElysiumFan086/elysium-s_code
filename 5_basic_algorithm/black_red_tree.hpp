#ifndef _BR_TREE_H_
#define _BR_TREE_H_

/********************************************************/
/*              Basic tree rotate operations            */
/********************************************************/

struct Node* parent(struct Node* n) {
	return n->parent;
}

struct Node* grand_parent(struct Node* n) {
	struct Node* p = parent(n);
	if(p == NULL)    return NULL;
	return parent(p);
}

struct Node* sibling(struct Node* n) {
	struct Node* p = parent(n);
	if(p == NULL)        return NULL;
	if(n == p->left)     return p->right;
	if(n == p->right)    return p->left;
}

struct Node* uncle(struct Node* n) {
	struct Node* p = parent(n);
	struct Node* g = grand_parent(n);
	if(g == NULL)    return NULL;
	return sibling(p);
}

void rotate_left(struct Node* n) {
	struct Node* nnew = n->right;
	assert(nnew != LEAF);
	n->right = nnew->left;
	nnew->left = n;
	nnew->parent = n->parent;
	n->parent = nnew;
}

void rotate_right(struct Node* n) {
	struct Node* nnew = n->left;
	assert(nnew != LEAF);
	n->left = nnew->right;
	nnew->right = n;
	nnew->parent = n->parent;
	n->parent = nnew;
}

/********************************************************/
/*          Black-Red Tree inserting operations         */
/********************************************************/

struct Node* insert(struct Node* root, struct Node* n) {
	// Insert new node into the current tree
	insert_recurse(root, n);

	// Repair the tree in case any of the red-black properties have been voilated
	insert_repair_tree(n);

	// Find the new root to return
	root = n;
	while(parent(root) != NULL)
		root = parent(root);
	return root;
}

void insert_recurse(struct Node* root, struct Node* n) {
	// Recursively descend the tree until a leaf is found
	if(root != NULL && n->key < root->key) {
		if(root->left != LEAF) {
			insert_recurse(root->left, n);
			return ;
		}
		else {
			root->left = n;
		}
	} else if(root != NULL) {
		if(root->right != LEAF) {
			insert_recurse(root->right, n);
			return ;
		}
		else {
			root->right = n;
		}
	}

	// Insert new node 'n'
	n->parent = root;
	n->left = LEAF;
	n->right = LEAF;
	n->color = RED;
}

void insert_repair_tree(struct Node* n) {
	if(parent(n) == NULL) {
		insert_case1(n);
	} else if(parent(n)->color == BLACK) {
		insert_case2(n);
	} else if(uncle(n)->color == RED) {
		insert_case3(n);
	} else {
		insert_case4(n);
	}
}

/* The current node 'n' is at the root of the tree. */
void insert_case1(struct Node* n) {
	if(parent(n) == NULL)
		n->color = BLACK;
}

/* The current node's parent is black, properties are not threatened. */
void insert_case2(struct Node* n) {
	return;
}

/* Both parent and uncle node are red */
void insert_case3(struct Node* n) {
	struct Node* p = parent(n);
	if(p)  p->color = BLACK;
	struct Node* u = uncle(n);
	if(u)  u->color = BLACK;
	struct Node* g = grand_parent(n);
	if(g)  g->color = RED;

	/* Since set grandfather to RED may broke RB-tree property */
	insert_repair_tree(g);
}

/* Current node's parent is red, and its uncle is black. */
void insert_case4(struct Node* n) {
	struct Node* p = parent(n);
	struct Node* g = grand_parent(n);

	// Step 1: make the new node N to the outside of its sub-tree
	if(n == g->left->right) {
		rotate_left(p);
		n = n->left;
	} else if (n == g->right->left) {
		rotate_right(p);
		n = n->right;
	}

	// Step 2: rotate grand father and retain node's color
	insert_case4_step2(n);
}

void insert_case4_step2(struct Node* n) {
	struct Node* p = parent(n);
	struct Node* g = grand_parent(n);

	if(n == p->left)
		rotate_right(g);
	else
		rotate_left(g);

	p->color = BLACK;
	g->color = RED;
}

#endif