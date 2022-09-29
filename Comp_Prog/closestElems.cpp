class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> closest; 
        int prev_diff = 99999 ; 
        for(int i = 0 ; i <arr.size() ; i++)
        {
            if(abs(arr[i]-x) < prev_diff or closest.size()!=k )
            {
                prev_diff = abs(arr[i]-x);
                if(closest.size() == k)
                    closest.erase(closest.begin()) ; 
                 closest.push_back(arr[i]) ;
                 
            }
            else if(abs(arr[i]-x) < abs(closest.front() -x))
            {
                 closest.erase(closest.begin()) ; 
                 closest.push_back(arr[i]) ;
            }
            
            
        }
        return closest; 
    }
};
