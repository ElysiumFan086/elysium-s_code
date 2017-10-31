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
	 
std::vector<int> preorderTraversal(TreeNode* p_root) {
        std::vector<int> vec_res;
        if(p_root == NULL)    return vec_res;
        std::stack<TreeNode*> s;
        s.push(p_root);
        while(!s.empty()) {
            TreeNode* p_top = s.top();
            vec_res.push_back(p_top->val);
            s.pop();
            if(p_top->right)    s.push(p_top->right);
            if(p_top->left)     s.push(p_top->left);
        }
        return vec_res;
}

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
  
  std::vector<int> postorderTraversal(TreeNode* p_root) {
        std::vector<int> vec_res;
        if(p_root == NULL)    return vec_res;
        std::stack<TreeNode*> s;
        s.push(p_root);
        TreeNode* p_head = p_root;
        while(!s.empty()) {
            TreeNode* p_top = s.top();
            if((!p_top->left && !p_top->right) || p_top->left == p_head || p_top->right == p_head) {
                vec_res.push_back(p_top->val);
                s.pop();
                p_head = p_top;
            }
            else {
                if(p_top->right)    s.push(p_top->right);
                if(p_top->left)     s.push(p_top->left);
            }
        }
        
        return vec_res;
    }  

  void inorderTraversal(TreeNode* root, std::vector<int> &vec_data) {
        if(root != NULL){
              inorderTraversal(root->left, vec_data);
              vec_data.push_back(root->val);
              inorderTraversal(root->right, vec_data);
        }
  }
