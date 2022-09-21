#include <iostream>
#include <cmath>
#include<vector>
using namespace std;
class Solution
{
public:
    /// @brief 
    /// @param nums1 
    /// @param nums2 
    /// @return 
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int m = nums1.size();
        int n = nums2.size();
        std::cout<<"m,n "<<m<<n<<std::endl ; 
        // int* k = (m+n)%2 != 0? {ceil((m+n)/2),ceil((m+n)/2)} : {(m+n)/2,((m+n)/2)+1} ;
        int stop = ceil((m + n) / 2)+1;
        std::cout<<"stop is "<<stop <<std::endl ; 

        bool singleVal = (m + n) % 2 != 0 ? true : false;

        if (singleVal)
        {
            int ctr = 0;
            int l1 = 0;
            int l2 = 0;
            int curr = 0;
            while (stop > l1 + l2)
            {

                if (nums1[l1] > nums2[l2])
                {
                    curr = nums2[l2];
                    l2++;
                    if(l2 == n)
                    {
                        nums2[l2] = 99999; 
                    }
                }
                else
                {
                    curr = nums1[l1];
                    l1++;
                    if(l1 == m)
                    {
                        nums1[l1] = 99999;
                    }
                }
            }
            std::cout << curr<<std::endl ;
            return curr;
        }
        else
        {
            int ctr = 0;
            int l1 = 0;
            int l2 = 0;
            int curr = 0;
            int prev = 0;
            while (stop > l1 + l2)
            {

                if (nums1[l1] > nums2[l2])
                {
                    prev = curr;
                    curr = nums2[l2];
                    l2++;
                    if(l2 == n)
                    {
                        nums2[l2] = 99999; 
                    }
                }
                else
                {
                    prev = curr;
                    curr = nums1[l1];
                    
                    l1++;
                    if(l1 == m)
                    {
                        nums1[l1] = 99999;
                    }
                }
            }
            std::cout << curr<<std::endl ;
            std::cout << prev<<std::endl ;
            std::cout <<  double(curr+prev)/2<<std::endl ;
            
            return double(curr+prev)/2;
        }
    }
};

int main()
{
    Solution s;
    vector<int> nums1 = {1,3};                                                                                   
    vector<int> nums2 = {2};
    s.findMedianSortedArrays(nums1, nums2);
    return 0;
}