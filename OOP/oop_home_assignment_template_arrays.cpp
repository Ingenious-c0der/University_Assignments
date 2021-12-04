#include <iostream>
using namespace std;

template<class T>
class array_handler{
    T* arr ;
    int arr_size;
public:
    array_handler(){
        arr = nullptr;
        arr_size = 0;
    }

    array_handler(int size){
        arr_size = size ;
        arr = new T[arr_size];

    }
    void add_data(){
        for(int i=0 ;i <arr_size; i++){
            cout<<"Input the element number "<<i+1<<" : ";
            cin>>arr[i];
        }
    }

    void add_element(T element){
        arr_size++;
        arr[arr_size-1] = element ;
    }
    void delete_element(int index){
        for(int i=index; i<arr_size; i++){
            arr[i] = arr[i+1];
        }
        arr_size--;

    }


    array_handler<T> operator +(array_handler<T> arr_other){

        auto max_size = arr_size>arr_other.arr_size?arr_size:arr_other.arr_size;
        auto smaller_size = arr_size<arr_other.arr_size?arr_size:arr_other.arr_size;
        array_handler<T> result(max_size);
        if (arr_size<max_size){
      
            for(int i=max_size-smaller_size;i>0;i--){
                 
                add_element(0);
                arr_size--; 
                
                

            }
        }else{
           
            for(int i=max_size-arr_other.arr_size;i>0;i--){
                
                arr_other.add_element(0);

            }
       
        }


        for(int i = 0 ; i<max_size; i++){
            result.arr[i] = arr[i]+arr_other.arr[i];

        }

        return result;
    }
    void operator = (const array_handler<T>& arr_other){
        if(arr){
            arr_size = arr_other.arr_size;
        }else{
            this->arr = new float [arr_other.arr_size];
            arr_size = arr_other.arr_size;

        }
        for (int i = 0; i<arr_other.arr_size; i++){
            arr[i] = arr_other.arr[i];
        }

    }
    void display(){
        if (arr){
            for(int i=0; i<arr_size; i++){
                cout<<arr[i]<<",";
            }
        }
        else{
            cout<<"The array is empty"<<endl;
        }
        cout<<endl;
    }
    void replace_element(int index, T element){
        arr[index] = element;
    }

    template <typename K>
    void multiply_by(K val){
        for(int i=0; i<arr_size; i++){
            arr[i] = arr[i]*val;
        }
    }



};


int main()
{
    array_handler<float> arr1(7);
    array_handler<float> arr2(4);
    arr1.add_data();
    arr2.add_data();
    array_handler<float> arr3;

    arr3 = arr1 + arr2;
    arr3.multiply_by(6);
    arr3.delete_element(2);
    arr3.replace_element(2,100);
    arr3.display();
    return 0;
}
