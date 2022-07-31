#include<iostream>
using namespace std;
void fur(int x)
    {
        x=15;
    }
int main()
{
    
   
    int *x;
    *x=10;
    fur(x);
    
    

    return 0;
}