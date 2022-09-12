#include<iostream>


class Page {
    int pageNumber; 
    int data; 
    int Priority;
    static int pageCounter ; 
    Page(

    )
    {
        pageNumber = pageCounter; 
        data = 0 ; 
        Priority = 0 ; 
        pageCounter++; 
    }
    Page(int PageNumber)
    {
        this->pageNumber = PageNumber ;
        data = 0 ; 
        Priority = 0 ; 
    }
    friend class LRUMemory; 
    friend class FIFOMemory ; 
};
int Page::pageCounter = 0 ; 
class LRUMemory
{
    int frameSize = 0 ; 
    Page * buffer;
    int totalPageFaults = 0;
    Page * pageFaultArray ; 
    int * bufferAgeArray ; 
    bool isBufferFull = false; 
    public:
    LRUMemory(int bufferSize)
    {
        frameSize = bufferSize; 
        buffer = new Page[bufferSize];
        for(int i = 0  ; i< frameSize ; i++)
        {
            buffer[i] = Page(-1) ; 
        }
        pageFaultArray = new Page[20]; //side feature
        bufferAgeArray = new int[bufferSize];
        
    }

    ~LRUMemory()
    {
        delete buffer;
    }
    void displayLRU()
    {
        for(int i = 0 ; i<frameSize ; i++)
        {
            std::cout<< buffer[i].pageNumber <<" | "; 

        }
        std::cout<<std::endl; 
    }

    void insertToBuffer(Page page)
    {
        //finding the most aged pageNumber or least recently used page number in the buffer
        
        if(isBufferFull)
        {
        int LRU_index = 0 ; 
        int age = 0 ; 
        for(int i = 0 ; i< frameSize; i++)
        {
            if (age < bufferAgeArray[i])
            {
                age = bufferAgeArray[i];
                LRU_index = i ; 
            }
        }
        std::cout<<"Page Number "<<buffer[LRU_index].pageNumber<<" was least recently used and hence replaced with "<<page.pageNumber<<" at frame Location "<<LRU_index<<std::endl ;
        buffer[LRU_index] = page;
        bufferAgeArray[LRU_index] = 0 ;
        }
        else
        {
            int neg_count = 0 ; 
            for( int i = 0 ; i<frameSize;i++)
            {
                if(buffer[i].pageNumber  == -1)
                {
                   neg_count ++ ; 
                    
                }
            
            }
            if (neg_count == 1)
            {
                isBufferFull = true; 
            }

            for( int i = 0 ; i<frameSize;i++)
            {
                if(buffer[i].pageNumber  == -1)
                {
                    buffer[i] = page;
                    return ;  

                }
            }
            

        } 

    }


    bool getPage(Page page)
    {
        for(int i = 0 ; i< frameSize ;i++)
        {
            
                bufferAgeArray[i] ++ ; 
            
        }
        for(int i = 0 ; i< frameSize ;i++)
        {
            if(buffer[i].pageNumber == page.pageNumber)
            {
               std::cout<<"HIT "<<page.pageNumber<<std::endl;
                 displayLRU();
                bufferAgeArray[i] = 0 ; 
                return true;
            }
            
        }
        std::cout<<"MISS "<<page.pageNumber<<std::endl;
        totalPageFaults++; 
        insertToBuffer(page);
        displayLRU();
        return false ; 
    }

    void enterSequenceLRU(int * arr , int size)
    {
        for ( int i = 0; i < size ; i++ )
        {
            getPage(Page(arr[i]));
        }
        std::cout<<"Total Page Faults for the given Page Sequence with LRU with frameSize "<<frameSize <<" are "<<totalPageFaults<<std::endl; 
    }

};



class FIFOMemory
{
    int frameSize = 0 ; 
    Page * buffer;
    int totalPageFaults = 0;
    Page * pageFaultArray ; 
    int * bufferAgeArray ; 
    bool isBufferFull = false; 
    public:
    FIFOMemory(int bufferSize)
    {
        frameSize = bufferSize; 
        buffer = new Page[bufferSize];
        for(int i = 0  ; i< frameSize ; i++)
        {
            buffer[i] = Page(-1) ; 
        }
        pageFaultArray = new Page[20]; //side feature
        bufferAgeArray = new int[bufferSize];
        
    }

    ~FIFOMemory()
    {
        delete buffer;
    }
    void displayFIFO()
    {
        for(int i = 0 ; i<frameSize ; i++)
        {
            std::cout<< buffer[i].pageNumber <<" | "; 

        }
        std::cout<<std::endl; 
    }

    void insertToBuffer(Page page)
    {
        //finding the most aged pageNumber or least recently used page number in the buffer
        
        if(isBufferFull)
        {
        int LRU_index = 0 ; 
        int age = 0 ; 
        for(int i = 0 ; i< frameSize; i++)
        {
            if (age < bufferAgeArray[i])
            {
                age = bufferAgeArray[i];
                LRU_index = i ; 
            }
        }
        std::cout<<"Page Number "<<buffer[LRU_index].pageNumber<<" was least recently used and hence replaced with "<<page.pageNumber<<" at frame Location "<<LRU_index<<std::endl ;
        buffer[LRU_index] = page;
        bufferAgeArray[LRU_index] = 0 ;
        }
        else
        {
            int neg_count = 0 ; 
            for( int i = 0 ; i<frameSize;i++)
            {
                if(buffer[i].pageNumber  == -1)
                {
                   neg_count ++ ; 
                }
            
            }
            if (neg_count == 1)
            {
                isBufferFull = true; 
            }

            for( int i = 0 ; i<frameSize;i++)
            {
                if(buffer[i].pageNumber  == -1)
                {
                    buffer[i] = page;
                    return ;  

                }
            }
            

        } 

    }


    bool getPage(Page page)
    {

        for(int i = 0 ; i< frameSize ;i++)
        {
            
                bufferAgeArray[i] ++ ; 
            
        }
        for(int i = 0 ; i< frameSize ;i++)
        {
            if(buffer[i].pageNumber == page.pageNumber)
            {
                std::cout<<"HIT "<<page.pageNumber<<std::endl;
                 displayFIFO();
                return true;
            }
          
        }
     std::cout<<"MISS "<<page.pageNumber<<std::endl;
        totalPageFaults++; 
        insertToBuffer(page);
        displayFIFO();
        return false ; 
    }

    void enterSequenceFIFO(int * arr , int size)
    {
        for ( int i = 0; i < size ; i++ )
        {
            getPage(Page(arr[i]));
        }
        std::cout<<"Total Page Faults for the given Page Sequence with FIFO with frameSize "<<frameSize <<" are "<<totalPageFaults<<std::endl; 
    }

};




int main()
{

    int arr[]  = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 3};
    int arr2[] = {1, 3, 0, 3, 5, 6, 3};
    FIFOMemory f(3);
    LRUMemory l(4); 
    std::cout<<"LRU MEMORY OPERATIONS START"<<std::endl; 
    l.enterSequenceLRU(arr, 14);
    std::cout<<"LRU MEMORY OPERATIONS END"<<std::endl; 

    
    std::cout<<"FIFO MEMORY OPERATIONS START"<<std::endl;
    f.enterSequenceFIFO(arr2,7);
     std::cout<<"FIFO MEMORY OPERATIONS END"<<std::endl;


}