#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
class Page
{
    int pageNumber = 0;
    int page_age;
    Page() {}
    Page(int PageNumber)
    {
        this->pageNumber = PageNumber;
        page_age = 0;
    }
    friend class LRUMemory;
    friend class OptimalMemory;
    friend class FIFOMemory;
};

class LRUMemory
{
    int frameSize = 0;
    Page *buffer;
    int totalPageFaults = 0;

public:
    LRUMemory(int bufferSize)
    {
        frameSize = bufferSize;
        buffer = new Page[bufferSize];
        for (int i = 0; i < frameSize; i++)
        {
            buffer[i] = Page(-1);
        }
    }
    ~LRUMemory()
    {
        delete buffer;
    }
    void displayLRU()
    {
        for (int i = 0; i < frameSize; i++)
        {
            std::cout << buffer[i].pageNumber << " | ";
        }

        std::cout << std::endl;
    }

    void insertToBuffer(Page page)
    {
        // finding the most aged pageNumber or least recently used page number in the buffer

        int LRU_index = 0;
        int age = 0;
        for (int i = 0; i < frameSize; i++)
        {
            if (age < buffer[i].page_age)
            {
                age = buffer[i].page_age;
                LRU_index = i;
            }
        }
        std::cout << "Page Number " << buffer[LRU_index].pageNumber << " was least recently used and hence replaced with " << page.pageNumber << " at frame Location " << LRU_index << std::endl;
        buffer[LRU_index] = page;
        buffer[LRU_index].page_age = 0;
    }

    bool getPage(Page page)
    {
        for (int i = 0; i < frameSize; i++)
        {
            buffer[i].page_age++;
        }
        for (int i = 0; i < frameSize; i++)
        {
            if (buffer[i].pageNumber == page.pageNumber)
            {
                std::cout << "HIT " << page.pageNumber << std::endl;
                displayLRU();
                buffer[i].page_age = 0;
                return true;
            }
        }
        std::cout << "MISS " << page.pageNumber << std::endl;
        totalPageFaults++;
        insertToBuffer(page);
        displayLRU();
        return false;
    }

    void enterSequenceLRU(int *arr, int size)
    {
        for (int i = 0; i < size; i++)
        {
            getPage(Page(arr[i]));
        }
        std::cout << "Total Page Faults for the given Page Sequence with LRU with frameSize " << frameSize << " are " << totalPageFaults << std::endl;
    }
};

class FIFOMemory
{
    int max_size = 0;
    int page_faults = 0;
    std::unordered_set<int> current_pages;
    std::queue<Page> buffer;

public:
    FIFOMemory(int max_size)
    {
        this->max_size = max_size;
    }
    void displayFIFO()
    {
        for (auto i : current_pages)
        {
            std::cout << i << " | ";
        }
    }

    void insert(Page page)
    {

        if (current_pages.find(page.pageNumber) != current_pages.end())
        {
            std::cout << "HIT " << page.pageNumber << std::endl;
            return;
        }
        std::cout << "MISS " << page.pageNumber << std::endl;
        page_faults++;
        if (buffer.size() == max_size)
        {
            Page temp = buffer.front();
            buffer.pop();
            current_pages.erase(temp.pageNumber);
            std::cout << "REPLACING " << temp.pageNumber << " with " << page.pageNumber << std::endl;
        }
        buffer.push(page);
        current_pages.insert(page.pageNumber);
        displayFIFO();
        std::cout << std::endl;
    }

    void enterSequenceFIFO(int *arr, int size)
    {
        for (int i = 0; i < size; i++)
        {
            insert(Page(arr[i]));
        }
        std::cout << "Total Page Faults for the given Page Sequence with FIFO with frameSize " << max_size << " are " << page_faults << std::endl;
    }
};

class OptimalMemory
{

    int max_size = 0;
    std::vector<Page> buffer;
    int page_faults = 0;
    int readHead = 0;
    std::vector<int> pageNumbers;

public:
    OptimalMemory(int max_size, std::vector<int> pageNumbers)
    {
        this->max_size = max_size;
        this->pageNumbers = pageNumbers;
    }
    void displayOptimal()
    {
        for (auto i : buffer)
        {
            std::cout << i.pageNumber << " | ";
        }
    }

    void insert(Page page)
    {

        for (int i = 0; i < buffer.size(); i++)
        {
            if (buffer[i].pageNumber == page.pageNumber)
            {
                std::cout << "HIT " << page.pageNumber << std::endl;
                
                return;
            }
        }
        page_faults++;
        if (buffer.size() == max_size)
        {
            int replace_index = findfarthest(); // finding the farthest page number in the future
            std::cout<< "Replacing " << buffer[replace_index].pageNumber << " with " << page.pageNumber << std::endl;
            buffer[replace_index] = page;
        }
        else
        {
            buffer.push_back(page);
        }
        displayOptimal(); 
        std::cout<<std::endl; 
       
    }

    int findfarthest()
    {
            int farthest = 0 ; 
            int replace_index = 0;
            std::cout<<"Read Head at : "<<readHead<<std::endl ;
            for (int i = 0; i < max_size; i++)
            {
                
                for (int j = readHead; j < pageNumbers.size(); j++)
                {
                    if(buffer[i].pageNumber == pageNumbers[j] )
                    {             
                        if(j > farthest)
                        {
                            farthest = j ; 
                            replace_index = i ; 
                        }
                        std::cout<< "Page Number " << buffer[i].pageNumber << " is at distance " << j-readHead << " from read head " << std::endl;
                        break ; 
                    }
                    if(j == pageNumbers.size()-1)
                    {
                        std::cout<< "Page Number " << buffer[i].pageNumber << " is at distance infinite from read head " << std::endl;
                        return i ; 
                    }
                    
                }
            }
            std::cout<< "Next Farthest :"<<buffer[replace_index].pageNumber <<" at "<< farthest<< std::endl; 
            return replace_index;
    }

    void enterSequenceOptimal()
    {
        for (int i = 0; i < pageNumbers.size(); i++)
        {
            insert(Page(pageNumbers[i]));
            readHead++;
        }
        std::cout << "Total Page Faults for the given Page Sequence with Optimal with frameSize " << max_size << " are " << page_faults << std::endl;
    }


};
int main()
{

    int arr[] = {7, 0, 1, 2,
               0, 3, 0, 4, 2, 3, 0, 3, 2, 1,
               2, 0, 1, 7};
    int arr2[] = {1, 3, 0, 3, 5, 6, 3};
    std::vector<int> pageNumbers(arr, arr + sizeof(arr) / sizeof(arr[0]));
    LRUMemory l(4);
    FIFOMemory f(3);
    OptimalMemory o(3, pageNumbers);
    std::cout << "LRU MEMORY OPERATIONS START" << std::endl;
    l.enterSequenceLRU(arr, 14);
    std::cout << "LRU MEMORY OPERATIONS END" << std::endl;

    std::cout << "FIFO MEMORY OPERATIONS START" << std::endl;
    f.enterSequenceFIFO(arr2, 7);
    std::cout << "FIFO MEMORY OPERATIONS END" << std::endl;

    std::cout << "OPTIMAL MEMORY OPERATIONS START" << std::endl;
    o.enterSequenceOptimal();
    std::cout << "OPTIMAL MEMORY OPERATIONS END" << std::endl;


}