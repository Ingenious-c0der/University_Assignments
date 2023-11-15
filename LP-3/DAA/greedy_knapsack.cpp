#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to represent an item
struct Item {
    int weight;
    int value;
    double ratio; // Value-to-weight ratio
};

// Function to compare items based on their ratio
bool compareItems(Item a, Item b) {
    return a.ratio > b.ratio;
}

// Function to solve the fractional knapsack problem
double fractionalKnapsack(vector<Item>& items, int capacity) {
    // Calculate value-to-weight ratios for all items
    for (auto& item : items) {
        item.ratio = static_cast<double>(item.value) / item.weight;
    }

    // Sort items based on value-to-weight ratio in non-ascending order
    sort(items.begin(), items.end(), compareItems);

    double totalValue = 0.0;
    
    for (const auto& item : items) {
        if (capacity >= item.weight) {
            // If the whole item can be added
            totalValue += item.value;
            capacity -= item.weight;
        } else {
            // If only a fraction of the item can be added
            totalValue += (static_cast<double>(capacity) / item.weight) * item.value;
            break;
        }
    }

    return totalValue;
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

    // Solve the fractional knapsack problem
    double maxValue = fractionalKnapsack(items, capacity);

    cout << "Maximum value in Knapsack = " << maxValue << endl;

    return 0;
}
