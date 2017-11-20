void swap_nodes(TreeNode* p_node) {
        if(p_node == NULL)    return;
        TreeNode* p_temp = p_node->left;
        p_node->left = p_node->right;
        p_node->right = p_temp;
    }
    
    TreeNode* invertTree(TreeNode* root) {
        if(root == NULL)    return NULL;
        
        TreeNode* p_root = root;
        std::stack<TreeNode*> nodes;
        nodes.push(root);
        
        while(nodes.empty() == false) {
            TreeNode* p_node = nodes.top();
            nodes.pop();
            
            swap_nodes(p_node);
            
            if(p_node->left != NULL)    nodes.push(p_node->left);
            if(p_node->right != NULL)   nodes.push(p_node->right);
        }
        
        return p_root;
}
