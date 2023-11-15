#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an item
struct Item {
    int weight;
    int value;
};

// Function to solve the 0-1 Knapsack problem using dynamic programming
int knapsackDynamicProgramming(vector<Item>& items, int capacity) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            if (items[i - 1].weight <= w) {
                dp[i][w] = max(dp[i - 1][w], items[i - 1].value + dp[i - 1][w - items[i - 1].weight]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

int main() {
    int n; // Number of items
    cout << "Enter the number of items: ";
    cin >> n;

    vector<Item> items(n);

    // Input the weight and value of each item
    for (int i = 0; i < n; ++i) {
        cout << "Enter weight and value for item " << i + 1 << ": ";
        cin >> items[i].weight >> items[i].value;
    }

    int capacity; // Knapsack capacity
    cout << "Enter the knapsack capacity: ";
    cin >> capacity;

    // Solve the 0-1 Knapsack problem using dynamic programming
    int maxValue = knapsackDynamicProgramming(items, capacity);

    cout << "Maximum value in Knapsack = " << maxValue << endl;

    return 0;
}
