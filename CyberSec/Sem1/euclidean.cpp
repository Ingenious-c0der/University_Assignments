#include<iostream>
class ExtendedEuclid
{
    int a,b,x,y ;
    public:
    ExtendedEuclid(int a, int b)
    {
        this->a = a ;
        this->b = b ;
        this->x = 0 ;
        this->y = 0 ;
    }
    int gcdExtended(int a, int b, int* x, int* y)
    {
        
        if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
 
    return gcd;
    }
    void getModInverse()
    {
        int g = gcdExtended(a,b,&x,&y);
        if(g != 1)
        {
            std::cout<<"Inverse does not exist"<<std::endl;
        }
        else
        {
            int res = (x%b + b)%b ;
            std::cout<<"Modular inverse is : "<<res<<std::endl;
        }
    }
}; 
int main()
{
    ExtendedEuclid(17, 30).getModInverse();
    return 0;
}