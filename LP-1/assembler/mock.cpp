#include<iostream> 
#include<vector> 
#include<algorithm> 

class FirstFit{
    int * memory_array_sizes ; 
    int * memory_array;
    int * memory_capture_array ;  
    int mem_size = 0 ; 
    public: 
    FirstFit(int mem_size)
    {   
        this->mem_size = mem_size ; 
        memory_array_sizes = new int[mem_size];
        memory_array = new int[mem_size];
        memory_capture_array = new int[mem_size];
        for(int i = 0 ;i<mem_size ; i++)
        {
            memory_capture_array[i] = 0 ; 
        }  
        for(int i = 0 ; i< mem_size ; i++)
        {
            std::cout<< "Enter the memory size of block "<< i +1<<" : " ;
            std::cin >> memory_array_sizes[i] ;
        }

    }
    FirstFit(int mem_size, std::vector<int> block_sizes)
    {
        this->mem_size = mem_size ; 
        memory_array_sizes = new int[mem_size];
        memory_array = new int[mem_size];
        memory_capture_array = new int[mem_size];
        for(int i = 0 ;i<mem_size ; i++)
        {
            memory_capture_array[i] = 0 ; 
        }  
        for(int i = 0 ; i< mem_size ; i++)
        {
           
           memory_array_sizes[i] = block_sizes[i];
        }



    }

    void display_Memory_block()
    {
        int total_wastage = 0 ; 
        for(int i = 0 ; i<mem_size; i++)
        {
            if(memory_capture_array[i] == 1)
            std::cout<< "|| "<<memory_array_sizes[i] << " || " << memory_array[i]<<" || "<<std::endl;
            else 
            std::cout<< "|| "<<memory_array_sizes[i] << " || " << "Empty" <<" || "<<std::endl;

            total_wastage+= memory_array_sizes[i] -  memory_array[i] ; 
        }
        std::cout<<"Total memory wasted "<<total_wastage<<" kb"<<std::endl; 
    }

    void Fit(std::vector<int> memories)
    {
        std::vector<int> waiting ; 
        bool found = false; 
        int memory_to_place = 0 ; 
        for(int i = 0 ; i < memories.size() ;i++)
        {
            memory_to_place = memories[i];
            for(int i = 0 ; i<mem_size ; i++ )
            {
                if(memory_to_place < memory_array_sizes[i] && memory_capture_array[i]==0)
                {
                    memory_array[i] = memory_to_place ; 
                    memory_capture_array[i]=1 ; 
                    found = true; 
                    break ; 
                }
            }
            if(!found)
            {
                waiting.push_back(memory_to_place); 
            }
            found = false; 

        }
        std::cout<< "Following memory allocations are still pending \n"; 
        for(int i = 0 ; i<waiting.size();i++)
        {
            std::cout<< waiting[i] <<"  "; 
        }
        std::cout<<std::endl; 

    }





};


class BestFit{
    int * memory_array_sizes ; 
    int * memory_array;
    int * memory_capture_array ;  
    int mem_size = 0 ; 
    public: 
    BestFit(int mem_size)
    {   
        this->mem_size = mem_size ; 
        memory_array_sizes = new int[mem_size];
        memory_array = new int[mem_size];
        memory_capture_array = new int[mem_size];
        for(int i = 0 ;i<mem_size ; i++)
        {
            memory_capture_array[i] = 0 ; 
        }  
        for(int i = 0 ; i< mem_size ; i++)
        {
            std::cout<< "Enter the memory size of block "<< i +1<<" : " ;
            std::cin >> memory_array_sizes[i] ;
        }

    }
    BestFit(int mem_size, std::vector<int> block_sizes)
    {
        this->mem_size = mem_size ; 
        memory_array_sizes = new int[mem_size];
        memory_array = new int[mem_size];
        memory_capture_array = new int[mem_size];
        for(int i = 0 ;i<mem_size ; i++)
        {
            memory_capture_array[i] = 0 ; 
        }  
        for(int i = 0 ; i< mem_size ; i++)
        {
           
           memory_array_sizes[i] = block_sizes[i];
        }



    }

    void display_Memory_block()
    {
        int total_wastage = 0 ; 
        for(int i = 0 ; i<mem_size; i++)
        {
            if(memory_capture_array[i] == 1)
            std::cout<< "|| "<<memory_array_sizes[i] << " || " << memory_array[i]<<" || "<<std::endl;
            else 
            std::cout<< "|| "<<memory_array_sizes[i] << " || " << "Empty" <<" || "<<std::endl;

            total_wastage+= memory_array_sizes[i] -  memory_array[i] ; 
        }
        std::cout<<"Total memory wasted "<<total_wastage<<" kb"<<std::endl; 
    }

    void Fit(std::vector<int> memories)
    {
        std::vector<int> waiting ; 
        
        int memory_to_place = 0 ; 
        
        std::sort(memories.begin(),memories.end());
        for(int i = 0 ; i < memories.size() ;i++)
        {
            int least_fit_size = 99999999 ;
            int least_fit_index = -1 ;
            memory_to_place = memories[i];

            for(int i = 0 ; i<mem_size ; i++ )
            {
                if(memory_to_place < memory_array_sizes[i] && memory_capture_array[i]==0 && memory_array_sizes[i] < least_fit_size)
                {
                    least_fit_size = memory_array_sizes[i]; 
                    least_fit_index = i ; 
                }
            }
         
            if(least_fit_index== -1)
            {
                waiting.push_back(memory_to_place); 
            }
            else
            {
                memory_array[least_fit_index] = memory_to_place ; 
                memory_capture_array[least_fit_index] = 1 ; 
            }

        }
        std::cout<< "Following memory allocations are still pending \n"; 
        for(int i = 0 ; i<waiting.size();i++)
        {
            std::cout<< waiting[i] <<"  "; 
        }
        std::cout<<std::endl; 

    }





};
class WorstFit{
    int * memory_array_sizes ; 
    int * memory_array;
    int * memory_capture_array ;  
    int mem_size = 0 ; 
    public: 
    WorstFit(int mem_size)
    {   
        this->mem_size = mem_size ; 
        memory_array_sizes = new int[mem_size];
        memory_array = new int[mem_size];
        memory_capture_array = new int[mem_size];
        for(int i = 0 ;i<mem_size ; i++)
        {
            memory_capture_array[i] = 0 ; 
        }  
        for(int i = 0 ; i< mem_size ; i++)
        {
            std::cout<< "Enter the memory size of block "<< i +1<<" : " ;
            std::cin >> memory_array_sizes[i] ;
        }

    }
    WorstFit(int mem_size, std::vector<int> block_sizes)
    {
        this->mem_size = mem_size ; 
        memory_array_sizes = new int[mem_size];
        memory_array = new int[mem_size];
        memory_capture_array = new int[mem_size];
        for(int i = 0 ;i<mem_size ; i++)
        {
            memory_capture_array[i] = 0 ; 
        }  
        for(int i = 0 ; i< mem_size ; i++)
        {
           
           memory_array_sizes[i] = block_sizes[i];
        }



    }

    void display_Memory_block()
    {
        int total_wastage = 0 ; 
        for(int i = 0 ; i<mem_size; i++)
        {
            if(memory_capture_array[i] == 1)
            std::cout<< "|| "<<memory_array_sizes[i] << " || " << memory_array[i]<<" || "<<std::endl;
            else 
            std::cout<< "|| "<<memory_array_sizes[i] << " || " << "Empty" <<" || "<<std::endl;

            total_wastage+= memory_array_sizes[i] -  memory_array[i] ; 
        }
        std::cout<<"Total memory wasted "<<total_wastage<<" kb"<<std::endl; 
    }

    void Fit(std::vector<int> memories)
    {
        std::vector<int> waiting ; 
        
        int memory_to_place = 0 ; 
        
        std::sort(memories.begin(),memories.end());
        for(int i = 0 ; i < memories.size() ;i++)
        {
            int least_fit_size = -1 ;
            int least_fit_index = -1 ;
            memory_to_place = memories[i];

            for(int i = 0 ; i<mem_size ; i++ )
            {
                if(memory_to_place < memory_array_sizes[i] && memory_capture_array[i]==0 && memory_array_sizes[i] > least_fit_size)
                {
                    least_fit_size = memory_array_sizes[i]; 

                    
                    least_fit_index = i ; 
                }
            }
         
            if(least_fit_index== -1)
            {
                waiting.push_back(memory_to_place); 
            }
            else
            {
                memory_array[least_fit_index] = memory_to_place ; 
                memory_capture_array[least_fit_index] = 1 ; 
            }

        }
        std::cout<< "Following memory allocations are still pending \n"; 
        for(int i = 0 ; i<waiting.size();i++)
        {
            std::cout<< waiting[i] <<"  "; 
        }
        std::cout<<std::endl; 

    }





};

int main()
{
        std::vector<int> memories; 
        std::vector<int> block_mems; 
        int block_mem; 
        int blocks_size  = 0  ; 
        std::cout<<"Enter the number of memory blocks available :"; 
        std::cin >> blocks_size;
        for(int i = 0 ; i<blocks_size ;i++)
        {
             std::cout<< "Enter the memory size of block "<< i +1<<" : " ;
             std::cin>> block_mem; 
            block_mems.push_back(block_mem) ;

        }
        FirstFit FF(blocks_size,block_mems);
        int var = 0 ;
        int mem_size = 0 ; 
        std::cout<<"Enter the number of memories to be inserted :";
        std::cin>>mem_size ;
        for(int i = 0 ; i<mem_size ;i++)
        {
            std::cout<<"Enter the amount of memory needed for process "<<i+1<<" : ";
            std::cin>>var ;
            memories.push_back(var);  
        }
      
        FF.Fit(memories); 
        FF.display_Memory_block(); 

        BestFit BF(blocks_size,block_mems);
        BF.Fit(memories);
        BF.display_Memory_block();

        WorstFit WF(blocks_size,block_mems); 
        WF.Fit(memories);
        WF.display_Memory_block();

}