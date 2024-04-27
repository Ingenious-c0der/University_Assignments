// assignment for matrix multiplication, parallel and sequential comparison
#include <iostream>

 __global__ void multiply(int *A, int *B, int *C, int size)
{

    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < size && col < size)
    {
        int sum = 0;
        for (int i = 0; i < size; i++)
        {
            sum += A[row * size + i] * B[i * size + col];
        }
        C[row * size + col] = sum;
    }
}

void print(int *mat, int size)
{
        for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            std::cout << mat[row * size + col] << " ";
        }
        std::cout << '\n';
    }
    std::cout << '\n';

}

void initialize(int *mat, int size)
{
    for (int i = 0; i < size; i++)
    {
        mat[i] = rand() % (21) - 10;
    }
}

int main()
{
    int N = 2;
    int mat_size = N * N;
    size_t mat_bytes = mat_size * sizeof(int);
    int num_THREADS = 2;
    int threadsPerBlock = N / num_THREADS;
    dim3 threads(num_THREADS, num_THREADS);
    dim3 blocks(2,2);
    int *A, *B, *C;
    A = new int[mat_size];
    B = new int[mat_size];
    C = new int[mat_size];

    initialize(A, mat_size);
    initialize(B, mat_size);
    std::cout << "Matrix A : " <<std::endl;
    print(A, N);
    std::cout << std::endl;

    std::cout << "Matrix B : " << std::endl;
    print(B, N);
    std ::cout << std ::endl;

    int *X, *Y, *Z;
    cudaMalloc(&X, mat_bytes);
    cudaMalloc(&Y, mat_bytes);
    cudaMalloc(&Z, mat_bytes);

    cudaMemcpy(X, A, mat_bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(Y, B, mat_bytes, cudaMemcpyHostToDevice);

    multiply<<< blocks, threads>>>(X, Y, Z, mat_size);

    cudaMemcpy(C, Z, mat_bytes, cudaMemcpyDeviceToHost);
    std::cout << "matrix C : " <<std::endl;
    print(C, N);



    delete[] A ;
    delete[] B;
    delete[] C;

    cudaFree(X); 
    cudaFree(Y); 
    cudaFree(Z); 

    return 0; 
}