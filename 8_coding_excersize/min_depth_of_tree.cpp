/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 
 int minDepth(TreeNode* root) {
        if(root == NULL)    return 0;
        if(root->left == NULL && root->right == NULL)    return 1;
        
        if(root->left == NULL && root->right != NULL)    return minDepth(root->right) + 1;
        if(root->left != NULL && root->right == NULL)    return minDepth(root->left) + 1;
        
        return min(minDepth(root->right), minDepth(root->left)) + 1;
}
