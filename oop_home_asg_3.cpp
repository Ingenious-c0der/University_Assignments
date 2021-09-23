#include <iostream>
using namespace std; 

int array[10] = {12,33,56,45,18,67,21,18,25,35};

int ele_finder(int n){
    int *p;
    p = array;
    for (int i=0;i<10;i++){
        if (n==*(p+i)){
            cout<<"Element found at index "<<i<<endl;
            return 0;
        }

    }
    cout<<"Element not found"<<endl;
    return 0;
}



int main(){
    int n;
    cout<<"Enter the number to be found :";
    cin>>n;
   ele_finder(n);

    return 0 ;
}
