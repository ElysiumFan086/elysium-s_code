/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
bool isSymmetric(TreeNode* root) {
        if(root == NULL)    return true;
        if(root->left == NULL && root->right == NULL)    return true;
        
        queue<TreeNode*> q1, q2;
        q1.push(root->left);
        q2.push(root->right);
        while(!q1.empty() && !q2.empty()) {
            TreeNode* p_node1 = q1.front();
            TreeNode* p_node2 = q2.front();
            q1.pop();    q2.pop();
            
            if((p_node1 && !p_node2) || (!p_node1 && p_node2))
                return false;
            
            if(p_node1) {
                if(p_node1->val != p_node2->val)    return false;
                q1.push(p_node1->left);
                q1.push(p_node1->right);
                q2.push(p_node2->right);
                q2.push(p_node2->left);                
            }
        }
        
        return true;
}
