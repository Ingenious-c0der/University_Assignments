class Solution {
    vector<vector<int>> finals ; 
     vector<int> travels ; 

public:
    
    void travelPaths(const TreeNode* root, const int targetSum)
    {
        if(!root)
            return; 
        
        travels.push_back(root->val);
        if(!root->left && !root->right && root->val == targetSum)
            finals.push_back(travels) ; 
       
        travelPaths(root->left,targetSum-root->val) ; 
        travelPaths(root->right,targetSum-root->val) ;     
        travels.pop_back();
    }
    
    
    vector<vector<int>> pathSum(const TreeNode* root, const int targetSum  ) {
     
        if(!root)
            return {};
        travelPaths(root,targetSum);
        return finals; 
        
      
    }
    
    
};
