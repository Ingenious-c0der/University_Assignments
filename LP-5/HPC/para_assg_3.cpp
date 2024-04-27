#include<iostream>
#include<vector>
#include<algorithm>
#include<chrono>
#include<omp.h>
using namespace std;

template<typename T>
T seq_min(vector<T>& arr){
    T result = arr[0];

    for(int i = 1; i < arr.size(); i++){
        result = min(result, arr[i]);
    }
    return result;
}

template<typename T>
T seq_max(vector<T>& arr){
    T result = arr[0];

    for(int i = 1; i < arr.size(); i++){
        result = max(result, arr[i]);
    }
    return result;
}

template<typename T>
T seq_sum(vector<T>& arr){
    T result = 0;

    for(int i = 0; i < arr.size(); i++){
        result += arr[i];
    }
    return result;
}

template<typename T>
float seq_avg(vector<T>& arr){
    float result = seq_sum(arr);
    result = result/arr.size();
    
    return result;
}

template<typename T>
T para_min(vector<T>& arr){
    T result = arr[0];

    #pragma omp parallel for reduction(min:result)
    for(int i = 1; i < arr.size(); i++){
        result = min(result, arr[i]);
    }
    return result;
}

template<typename T>
T para_max(vector<T>& arr){
    T result = arr[0];

    #pragma omp parallel for reduction(max : result)
    for(int i = 1; i < arr.size(); i++){
        result = max(result, arr[i]);
    }
    return result;
}

template<typename T>
T para_sum(vector<T>& arr){
    T result = 0;

    #pragma omp parallel for reduction(sum : result)
    for(int i = 0; i < arr.size(); i++){
        result += arr[i];
    }
    return result;
}

template<typename T>
float para_avg(vector<T>& arr){
    float result = para_sum(arr);
    result = result/arr.size();
    
    return result;
}

void initialize(vector<int>& arr){
    for(int i = 0; i < arr.size(); i++){
        arr[i] = rand()%10;
    }
}

void print(vector<int>& arr){
    for(int i = 0; i < arr.size(); i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main(){
    vector<int> arr(10);
    initialize(arr);
    
    const auto c1 = chrono::high_resolution_clock::now();
    int sum_para = para_sum<int>(arr);
    const auto c2 = chrono::high_resolution_clock::now();
    const auto time_sum_para = chrono::duration_cast<chrono::microseconds>(c2 - c1).count();
    cout<<"sum_para: "<<sum_para<<endl;
    cout<<"time_sum_para: "<<time_sum_para<<endl;

    const auto c3 = chrono::high_resolution_clock::now();
    int sum_seq = seq_sum<int>(arr);
    const auto c4 = chrono::high_resolution_clock::now();
    const auto time_seq_sum = chrono::duration_cast<chrono::microseconds>(c4 - c3).count();
    cout<<"sum_seq: "<<sum_seq<<endl;
    cout<<"time_seq_sum: "<<time_seq_sum<<endl;
    
    
    return 0;
}