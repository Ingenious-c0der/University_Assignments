#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <omp.h>
#include <random>
#include <vector>

void printVec(const std::vector<int> &arr)
{
  for (int i : arr)
  {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}

void merge(std::vector<int> &arr, int l, int m, int r)
{
  int n1 = m - l + 1;
  int n2 = r - m;
  std::vector<int> arr_1(n1), arr_2(n2);

  // #pragma omp parallel for #overhead > perf. improvement
  for (int i = 0; i < n1; i++)
  {
    arr_1[i] = arr[l + i];
  }
  // #pragma omp parallel for #overhead > perf. improvement
  for (int i = 0; i < n2; i++)
  {
    arr_2[i] = arr[m + 1 + i];
  }

  int i = 0, j = 0, k = l;

  while (i < n1 && j < n2)
  {
    if (arr_1[i] < arr_2[j])
    {
      arr[k] = arr_1[i];
      i++;
    }
    else
    {
      arr[k] = arr_2[j];
      j++;
    }
    k++;
  }

  while (i < n1)
  {
    arr[k] = arr_1[i];
    i++;
    k++;
  }
  while (j < n2)
  {
    arr[k] = arr_2[j];
    j++;
    k++;
  }
}

void seqMergeSort(std::vector<int> &arr, int l, int r)
{
  if (l < r)
  {
    int m = l + (r - l) / 2;
    {
      seqMergeSort(arr, l, m);
      seqMergeSort(arr, m + 1, r);
    }
    merge(arr, l, m, r);
  }
}

void paraMergeSort(std::vector<int> &arr, int l, int r)
{
  if (l < r)
  {
    int m = l + (r - l) / 2;
#pragma omp parallel sections
    {
#pragma omp section
      paraMergeSort(arr, l, m);
#pragma omp section
      paraMergeSort(arr, m + 1, r);
    }
    merge(arr, l, m, r);
  }
}

void seqBubbleSort(std::vector<int> &arr)
{
  int n = arr.size();
  bool swapped;
  do
  {
    swapped = false;
    for (int i = 1; i < n; ++i)
    {
      if (arr[i - 1] > arr[i])
      {
        std::swap(arr[i - 1], arr[i]);
        swapped = true;
      }
    }
    --n;
  } while (swapped);
}

std::vector<int> paraBubbleSort(std::vector<int> &arr)
{
  bool swapped;
  int n = arr.size();

  do
  {
    swapped = false;

// Odd phase sort
#pragma omp parallel for shared(arr) reduction(|| : swapped)
    for (int i = 0; i < n - 1; i += 2)
    {
      if (arr[i] > arr[i + 1])
      {
        std::swap(arr[i], arr[i + 1]);
        swapped = true;
      }
    }

// Even phase sort
#pragma omp parallel for shared(arr) reduction(|| : swapped)
    for (int i = 1; i < n - 1; i += 2)
    {
      if (arr[i] > arr[i + 1])
      {
        std::swap(arr[i], arr[i + 1]);
        swapped = true;
      }
    }
  } while (swapped);

  // printVec(arr);
  return arr;
}

std::vector<int> generateRandomVector(int size)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1, 1000);

  std::vector<int> vec(size);
  for (int i = 0; i < size; ++i)
  {
    vec[i] = dis(gen);
  }
  return vec;
}

int main()
{
  int size = 50000;
  std::cout << "Array Size : " << size << std::endl;
  std::vector<int> unsorted = generateRandomVector(size);
  std::vector<int> unsorted_2(unsorted), unsorted_3(unsorted),
      unsorted_4(unsorted);
      
  // parallel merge sort timing
  const auto c1 = std::chrono::high_resolution_clock::now();
  paraMergeSort(unsorted, 0, unsorted.size() - 1);
  const auto c2 = std::chrono::high_resolution_clock::now();
  const auto diff =
      std::chrono::duration_cast<std::chrono::microseconds>(c2 - c1).count();
  std::cout << "Time required for paraMerge Sorting (microsec): ";
  std::cout << diff << std::endl;

  // seq merge sort timing
  const auto c3 = std::chrono::high_resolution_clock::now();
  seqMergeSort(unsorted_2, 0, unsorted_2.size() - 1);
  const auto c4 = std::chrono::high_resolution_clock::now();
  const auto diff2 =
      std::chrono::duration_cast<std::chrono::microseconds>(c4 - c3).count();
  std::cout << "Time required for seqMerge Sorting (microsec): ";
  std::cout << diff2 << std::endl;

  // para bubble sort timing
  const auto c5 = std::chrono::high_resolution_clock::now();
  paraBubbleSort(unsorted_3);
  const auto c6 = std::chrono::high_resolution_clock::now();
  const auto diff3 =
      std::chrono::duration_cast<std::chrono::milliseconds>(c6 - c5).count();
  std::cout << "Time required for paraBubble Sorting (millisec): ";
  std::cout << diff3 << std::endl;

  // sequential bubble sort timing
  const auto c7 = std::chrono::high_resolution_clock::now();
  seqBubbleSort(unsorted_4);
  const auto c8 = std::chrono::high_resolution_clock::now();
  const auto diff4 =
      std::chrono::duration_cast<std::chrono::milliseconds>(c8 - c7).count();
  std::cout << "Time required for seqBubble Sorting (millisec): ";
  std::cout << diff4 << std::endl;

  return 0;
  // sample output on m3 pro chip
  // Array Size : 50000
  // Time required for paraMerge Sorting (microsec): 22301
  // Time required for seqMerge Sorting (microsec): 19414
  // Time required for paraBubble Sorting (millisec): 3572
  // Time required for seqBubble Sorting (millisec): 8742
}
