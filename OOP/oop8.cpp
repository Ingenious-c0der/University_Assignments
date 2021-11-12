#include<iostream>
using namespace std;



template<typename T>
void Display(T arr[],int size){
    for (int i = 0 ; i<size;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}


template <typename T>
T* selection_sort(T arr[],int size){
 T min,temp;
 int min_index;

 for(int n = 0 ; n<size;n++)
    {
        min = arr[n];
        min_index = n;
    	for(int k = n ; k<size ;k++)
        {
            if (arr[k]<min)
            {
                min = arr[k];
                min_index = k ;
            }
        }
    temp = arr[n];
    arr[n] = min;
    arr[min_index] = temp;
    }
return arr;
}

int main()
{   
    char arr[4] = {'d','a','b','c'};
    selection_sort<char>(arr,4);
    Display<char>(arr,4);
    return 0;
}
