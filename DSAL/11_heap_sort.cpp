#include <iostream>
using namespace std;

// Max Heap Implementation using array RP
class Heap
{

    int *array; // starts at zero . Lchild = 2*i + 1, Rchild = 2*i + 2
    int current_size = 0;
    int max_size;

public:
    Heap(int);
    void insertElement(int);
    int deleteElement();
    void heapSort();
    void displayHeap();
};

class Sorter
{
public:
    static void sort(int[], int);
};

Heap::Heap(int max_size)
{
    array = new int[max_size];
    this->max_size = max_size;
}

void Heap::insertElement(int element)
{
    if (current_size < max_size)
    {
        array[current_size] = element;
        int index = current_size;
        while (array[index / 2] < array[index])
        {
            int temp = array[index / 2];
            array[index / 2] = array[index];
            array[index] = temp;
            index /= 2;
        }
        current_size++;
    }
    else
    {
        cout << "Heap is full" << endl;
    }
}

int Heap::deleteElement()
{
    if (current_size == 0)
    {
        cout << "heap underflow";
        return 0;
    }
    int temp = 0;
    int deleted = array[0];
    array[0] = array[current_size - 1];
    int index = 0;

    while ((array[index] < array[2 * index + 2] || array[index] < array[2 * index + 1]) && 2 * index + 1 < current_size)
    {

        if (array[index * 2 + 1] > array[index * 2 + 2])
        {
            temp = array[index * 2 + 1];
            array[index * 2 + 1] = array[index];
            array[index] = temp;
            index = index * 2 + 1;
        }
        else
        {
            temp = array[index * 2 + 2];
            array[index * 2 + 2] = array[index];
            array[index] = temp;
            index = index * 2 + 2;
        }
    }
    current_size--;
    return deleted;
}

void Heap::heapSort()
{
    for (int i = 0; i < max_size; i++)
    {
        int top = deleteElement();
        cout << top << " ";
    }
    cout << endl;
}

void Heap::displayHeap()
{
    for (int i = 0; i < current_size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

void Sorter::sort(int *arr, int max_size)
{
    Heap h = Heap(max_size);
    for (int i = 0; i < max_size; i++)
    {
        h.insertElement(arr[i]);
    }
    cout << "The heap sorted elements are :";
    h.heapSort();
}
int main()
{
    // can be dynamic input
    int arr[] = {45, 78, 32, 14, 15, 56, 7};
    int size = 7;
    Sorter::sort(arr, size);
}
