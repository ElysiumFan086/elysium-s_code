/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
#include <iostream>
#include <vector>
#include <stack>

std::vector<int> inorderTraversal(TreeNode* root) {
      std::vector<int> res;
	    std::stack<TreeNode*> s;
	    TreeNode* p = root;
	    while( p || !s.empty() ) {
		    while(p) {
			    s.push(p);
			    p = p->left;
		    }

            p = s.top();
		    s.pop();
		    res.push_back(p->val);
		    p = p->right;
	    }

	    return res;
  }
  
  void inorderTraversal(TreeNode* root, std::vector<int> &vec_data) {
        if(root != NULL){
              inorderTraversal(root->left, vec_data);
              vec_data.push_back(root->val);
              inorderTraversal(root->right, vec_data);
        }
  }
