#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include<vector>
using namespace std;
using namespace std::chrono;

// Function to partition the array for QuickSort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Deterministic QuickSort algorithm
void quickSortDeterministic(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSortDeterministic(arr, low, pivotIndex - 1);
        quickSortDeterministic(arr, pivotIndex + 1, high);
    }
}

// Randomized QuickSort algorithm
int partitionRandomized(vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high);
}

void quickSortRandomized(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partitionRandomized(arr, low, high);
        quickSortRandomized(arr, low, pivotIndex - 1);
        quickSortRandomized(arr, pivotIndex + 1, high);
    }
}

// Function to generate an array of random integers
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand();
    }
    return arr;
}

// Function to measure the execution time of a sorting algorithm
void measureExecutionTime(void (*sortingFunction)(vector<int>&, int, int), vector<int>& arr, int size) {
    auto start = high_resolution_clock::now();
    sortingFunction(arr, 0, size - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Execution Time: " << duration.count() << " microseconds\n";
}

int main() {
    srand(time(0)); // Seed for random number generation

    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    vector<int> arr = generateRandomArray(size);

    // Perform deterministic QuickSort and measure execution time
    cout << "\nDeterministic QuickSort:\n";
    vector<int> arrDeterministic = arr; // Copy the original array
    measureExecutionTime(quickSortDeterministic, arrDeterministic, size);

    // Perform randomized QuickSort and measure execution time
    cout << "\nRandomized QuickSort:\n";
    vector<int> arrRandomized = arr; // Copy the original array
    measureExecutionTime(quickSortRandomized, arrRandomized, size);

    return 0;
}
