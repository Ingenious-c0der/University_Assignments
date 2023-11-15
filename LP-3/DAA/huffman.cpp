#include <iostream>
#include <queue>
#include <vector>

class HTN
{
public:
    char data;
    int freq;
    HTN *right = nullptr;
    HTN *left = nullptr;
    HTN(char data, int freq);
};

class Compare
{
public:
    bool operator()(HTN *a, HTN *b)
    {
        return a->freq > b->freq;
    }
};
HTN::HTN(char data, int freq)
{
    this->data = data;
    this->freq = freq;
    left = right = nullptr;
};

void printCodes(HTN *root, std::vector<int> arr, int top)
{
    if (root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (!root->left && !root->right)
    {
        std::cout << root->data << " ";
        for (int i = 0; i < top; i++)
        {
            std::cout << arr[i];
        }
        std::cout << std::endl;
    }
}

HTN *generateTree(std::priority_queue<HTN *, std::vector<HTN *>, Compare> pq)
{
    while (pq.size() != 1)
    {
        HTN *left = pq.top();
        pq.pop();
        HTN *right = pq.top();
        pq.pop();
        HTN *node = new HTN('$', left->freq + right->freq);
        node->left = left;
        node->right = right;
        pq.push(node);
    }
    return pq.top();
}

void HuffmanCode(std::vector<char> data, std::vector<int> freq)
{
    std::priority_queue<HTN *, std::vector<HTN *>, Compare> pq;
    int size = data.size();
    for (int i = 0; i < size; i++)
    {
        HTN *node = new HTN(data[i], freq[i]);
        pq.push(node);
    }
    HTN *root = generateTree(pq);
    std::vector<int> arr(100); 
    int top = 0 ; 
    printCodes(root, arr,top); 
}

int main()
{
    int n;
    std::cin >> n;
    std::vector<char> data;
    std::vector<int> freq;
    char x;
    for (int i = 0; i < n;i++){
        std::cin >> x;
        data.push_back(x);
    }
    int y;
    for (int i = 0; i < n; i++)
    {
        std::cin >> y;
        freq.push_back(y);
    }
    HuffmanCode(data, freq);
    return 0;
}