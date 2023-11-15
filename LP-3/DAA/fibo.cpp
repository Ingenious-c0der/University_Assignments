#include <iostream>

class Fibo
{
public:
    int recursive(int n)
    {
        return n <= 1 ? n : recursive(n - 1) + recursive(n - 2);
    }

    void iterative(int n)
    {
        int t1 = 0;
        int t2 = 1;
        int nt = 0;
        for (int i = 1; i <= n; i++)
        {
            if (i == 1)
            {
                std::cout << t1 << " ";
                continue;
            }
            if (i == 2)
            {
                std::cout << t2 << " ";
                continue;
            }
            nt = t1 + t2;
            t1 = t2;
            t2 = nt;
            std::cout << nt << " ";
        }
    }
};

int main()
{
    Fibo f = Fibo();
    for (int i = 0; i < 5; i++)
    {
        std::cout << f.recursive(i) << " ";
    }
    std::cout << std::endl;
    f.iterative(5);
    return 0;
}