/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

bool isSameTree(TreeNode* p, TreeNode* q) {
        std::stack<TreeNode*> s1, s2;
        if(p)  s1.push(p);
        if(q)  s2.push(q);
        while( !s1.empty() && !s2.empty() ) {
            TreeNode *t1 = s1.top();    s1.pop();
            TreeNode *t2 = s2.top();    s2.pop();
            
            if(t1->val != t2->val)    return false;
            if(t1->left)     s1.push(t1->left);
            if(t2->left)     s2.push(t2->left);
            if(s1.size() != s2.size())    return false;
            if(t1->right)    s1.push(t1->right);
            if(t2->right)    s2.push(t2->right);
            if(s1.size() != s2.size())    return false;
        }
        
        return s1.size() == s2.size();
}
