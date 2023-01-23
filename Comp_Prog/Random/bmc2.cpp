#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <cstdlib>

int processArray(std::vector<int> &array) {
  int ctr = 0 ;
  for(int i = 0 ; i< array.size();i++)
  {
    if(array[i]>=100)
    {
        ctr++ ; 
    }
    else
    {
        if(ctr == 0)
        {
            continue ; 
        }
        else
        {
           array[i-1] = ctr ; 
           array.erase(array.begin() + i - ctr, array.begin() + i - 1);
           ctr= 0 ; 
        }
    }
  }
  return array.size();
}

int main(void) {
  std::vector<int> array;
  int val;
  while (std::cin >> val) {
    if (val < 0) break;
    array.push_back(val);
  }
  int new_len = processArray(array);
  for(std::vector<int>::iterator a = array.begin(); a != array.end(); a++) {
    std::cout << *a << std::endl;
  }
  return 0;
}

