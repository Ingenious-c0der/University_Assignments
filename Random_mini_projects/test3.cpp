#include <iostream>
#include <vector>

int main()
{

    int size = 0;
    std::cin >> size;
    std::vector<int> vec ;
    int temp = 0 ; 
    for (int i = 0; i < size; ++i)
    {
        std::cin>>temp; 
        vec.push_back(temp) ;
    }
    int streak = 0;
    int max_streak = 0;
    for (auto elem : vec)
    {
        if (elem > 6)
            streak++;
        else
        {
            if (streak > max_streak)
                max_streak = streak;
            streak = 0;
        }
    }
    std::cout<< max_streak << std::endl;

    return 0;
}