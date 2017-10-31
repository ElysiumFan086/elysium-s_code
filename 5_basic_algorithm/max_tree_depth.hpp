/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

int maxDepth(TreeNode* root) {
        if(root == NULL)    return 0;
        int n_count = 0;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            ++n_count;
            int n = q.size();
            for(int i = 0; i < n; ++i){
                TreeNode* p_node = q.front();
                q.pop();
                if(p_node->left)     q.push(p_node->left);
                if(p_node->right)    q.push(p_node->right);
            }
        }
        
        return n_count;
}
