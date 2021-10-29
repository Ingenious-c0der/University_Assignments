#include<iostream>
using namespace std;



int * merge_sort(int arr1[],int arr2[],int size_arr1,int size_arr2)
{int i=0,j=0,k=0;
int* result_arr = new int[size_arr1+size_arr2];
    while (i<=size_arr1 && j<=size_arr2){
        if (arr1[i]>=arr2[j])
        {   
            result_arr[k] = arr2[j];
        
            j++;
            k++;
        }
        else
        {
            result_arr[k] = arr1[i];
            
            i++;
            k++;

        }


    }
    while(i<=size_arr1){
        result_arr[k] = arr1[i];
        i++;
        k++;
    }
    while(j<=size_arr2){
        result_arr[k] = arr2[j];
        j++;
        k++;
    }
    return result_arr;



}

int main()
{   int arr[6] = {1,3,5,6,18,34};
    int arr2[5] = {2,8,9,11,56};
    int * p = merge_sort(arr,arr2,6,5);
    for(int i  = 0;i<11;i++){
        cout<<*(p+i)<<" "; 
    }
     

    return 0;
}
