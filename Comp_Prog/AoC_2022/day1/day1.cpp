// https://adventofcode.com/2022/day/1

#include <iostream>
#include <fstream>
#include <sstream>
#include <sstream>
#include <vector>

std::vector<int> compare_update(std::vector<int> top_three, int val)
{
    int min_val = INT_MAX;
    int min_index = 0;
    for (int i = 0; i < top_three.size(); i++)
    {
        if (top_three[i] < min_val)
        {
            min_val = top_three[i];
            min_index = i;
        }
    }
    if (val > min_val)
    {
        top_three[min_index] = val;
    }
    return top_three;
}

int main()
{
    std::ifstream input("input.txt");
    int grand_total = 0;
    int k = 0;
    std::vector<int> tt = {0, 0, 0};
    std::string line;
    int total = 0;
    int min_val = 0;
    int min_index = 0;
    while (!input.eof())
    {
        std::getline(input, line);
        std::istringstream iss(line);
        if (line == "")
        {
            std::cout << "generated total : " << total << std::endl;
            tt = compare_update(tt, total);
            total = 0;
        }
        else
        {
            iss >> k;
            total += k;
        }
    }
    for (int k : tt)
    {
        grand_total += k;
        std::cout << k << std::endl;
    }

    std::cout << grand_total << std::endl;
    return 0;
}