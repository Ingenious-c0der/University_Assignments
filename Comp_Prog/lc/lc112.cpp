class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(!root) return (0);
        if(!root->left && !root->right && targetSum-root->val == 0) return (1) ;
        return hasPathSum(root->left,targetSum-root->val)||hasPathSum(root->right, targetSum-root->val); ;
    }
};