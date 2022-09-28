#include <iostream>
#include <vector>
int main()
{
  std::vector<int> v ; 
  int n ;
  while (1)
  {
    std::cin>>n ; 
    if(n<0)
    {
        break ;
    }
    else if(n%6 == 0 )
    {
        v.push_back(n) ; 
    }
  }
  std::cout<<v.size()<<std::endl;
}