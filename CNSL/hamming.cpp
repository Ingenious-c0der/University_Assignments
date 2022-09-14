#include<iostream>
#include<math.h>


void setParityBits(int** pbitsPos, int * hammingCode, int r_size)
{

    //print pbitsPos
   
    int index = 0 ;
    for ( int i = 0 ; i < r_size ; i++)
    {
        int xorRes = 0 ;
        int parityPosInfo[2] = {pbitsPos[i][0],pbitsPos[i][1]};
        int startIndex = parityPosInfo[0] ;
        //std::cout<<"\nparity bit position :"<<parityPosInfo[0]<<" "<<std::endl;
        for( int k = startIndex ; k > -1; k = k - 2*(parityPosInfo[1])) 
        {
            
            for(int j = k ; j > k-(parityPosInfo[1]) && j > -1  ; j--)
            {

               //std::cout<<"j :"<<j<<std::endl;
                if(hammingCode[j] != -1)
                {  
                     xorRes = xorRes ^ hammingCode[j];
                }
               
            }
           // std::cout<<"Jumping from "<<k<<" to "<<k - 2*(parityPosInfo[1])<<std::endl;
            
        }
        //std::cout<<"parity bit value for "<< parityPosInfo[0] <<" : "<<xorRes<<std::endl;
        hammingCode[parityPosInfo[0]] = xorRes;

    }
}

void getHammingCode(int dataStream[] , int size)
{
    int m = size ; 
    int r = 0 ;
    while(pow(2,r) < m+r+1)
    {
        r++;
    }
    int* hammingCode = new int [ m + r ];
    for (int i = 0; i< m+r ; i++)
    {
        hammingCode[i] = -1;
    }
    
    int ** pbitsPos = new int* [r];
    //initializing the pbitsPos array
    for(int i = 0 ; i < r ; i++)
    {
        pbitsPos[i] = new int[2];
    }
    //filling up the hamming code with databits first
    int j = 0 ; 
    int store = 0 ; 
    int logical_index = 0 ;
    int ds_counter =  size-1;  
    for( int actual_index = m+r-1 ; actual_index  > -1 ; actual_index --)
    {


       if( logical_index + 1 == pow(2,j))
       {
          // hammingCode[actual_index] = -1;
           logical_index++;

           
           pbitsPos[store][0] = actual_index;
              pbitsPos[store][1] = logical_index;   
           
           store++;
           j++; 
           
       
       }
       else
       {
           hammingCode[actual_index] = dataStream[ds_counter];
           ds_counter --; 
           logical_index++;

       }
    
    }

    

    setParityBits(pbitsPos,hammingCode,r);
    //displaying the hamming code
    for(int i = 0 ; i < m+r ; i++)
    {
        std::cout<<hammingCode[i]<<" ";
    }

}

int main()
{

    int array[] = {0,1,1,1,1};
    getHammingCode(array,sizeof(array)/sizeof(array[0]));
    return 0;
}