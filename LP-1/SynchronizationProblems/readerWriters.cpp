#include<mutex> 
#include<thread>
#include<iostream> 

std::mutex printer_mutex ;
bool is_printing = false; // condition variable for exclusive printing 
void wait_print()
{
    while(is_printing)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void printLine(std::string line ){

    if(printer_mutex.try_lock())
    {
        is_printing = true;
        std::cout<<"Event :  "<<line<<std::endl;
        printer_mutex.unlock();
        is_printing = false; 
    }
    else
    {
        wait_print();
        printLine(line);
    }

}
class Document{
    std::mutex writer_mutex; 
    int readerCountSemaphore = 0 ; 
    std:: mutex sem_guard; 
    bool is_writing = false;
    public: 
    std::string doc_name ="unnamed" ;
    Document(std::string name){
         doc_name = name;
     }
    void signal(int val)
    {
        if(sem_guard.try_lock())
        {
            readerCountSemaphore += val;
            sem_guard.unlock();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
            signal(val);
        }
    }

    friend class InteractionSpace; 
} ; 
class Reader{ 
    std::string readerName  = ""; 
    public:
     Reader(const std::string name)
     {
        this->readerName  = name ;
     }
     std::string getReaderName()
     {
            return readerName;
     }
       
} ; 
class Writer {
     std::string writerName  = ""; 
    public:
     Writer(const std::string name)
     {
        this->writerName  = name ;

     }
     std::string getWriterName()
     {
         return writerName;
     }
};
class InteractionSpace {
   
    public: 
    void wait_writer(Document& d)
    {
        while(d.readerCountSemaphore != 0 || d.is_writing )
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
        }
    }

    void wait_read(Document&d)
    {
        while(d.is_writing)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000)); 
        }

    }

    void write(Document& d ,Writer w)
    {
       if(d.writer_mutex.try_lock() && d.readerCountSemaphore == 0 )
       {
            d.is_writing = true ;
            printLine("Writer "+ w.getWriterName() + " is now writing " + d.doc_name +" ! ");
            std::this_thread::sleep_for(std::chrono::seconds(15));
            printLine("Writer "+ w.getWriterName() + " is done writing " + d.doc_name +" ! ");
            d.writer_mutex.unlock() ; 
            d.is_writing = false; 

       }
       else
       {
            printLine("Writer "+ w.getWriterName() + " is waiting to write " + d.doc_name +" ! ");
            wait_writer(d); 
            write(d,w) ; 
       }

    }



    void read(Document& d, Reader r)
    {
        if(!d.is_writing)
        {
            d.writer_mutex.try_lock() ; 
            d.signal(1) ;
            printLine("Reader "+ r.getReaderName() + " is now reading " + d.doc_name+" ! ");
            std::this_thread::sleep_for(std::chrono::seconds(10));
            printLine("Reader "+ r.getReaderName() + " is done reading " + d.doc_name+" ! ");
            d.signal(-1) ;
            d.writer_mutex.unlock(); 
        }
        else
        {
            printLine("Reader "+ r.getReaderName() + " is waiting to read " + d.doc_name+" ! ");
            wait_read(d); 
            read(d,r) ; 
        }
    }




}; 
int main()
{
    InteractionSpace IS;
    Document doc("Document");  
    int choice = 0 ;
    while(true)
    {
        std::cout<< "****** MENU ****** \n1.Add a reader \n2.Add a writer \n3.Exit"<<std::endl;
        std::cin>> choice; 
        switch(choice)
        {
        
            case 1:
            {
                std::string readerName = "";
                std::cout<<"Enter the name of the reader"<<std::endl;
                std::cin>>readerName;
                Reader r = Reader(readerName);                
                std::thread t1(&InteractionSpace::read,IS,std::ref(doc),r);
                t1.detach();
                break;
            }
            case 2:
            {
                std::string writerName = "";
                std::cout<<"Enter the name of the writer"<<std::endl;
                std::cin>>writerName;
                Writer w = Writer(writerName);
                std::thread t2(&InteractionSpace::write, IS, std::ref(doc), w); 
                t2.detach(); 
                break;
            }
            case 3 : {
                exit(0);
            }
            default:
            {
                std::cout<<"Invalid choice"<<std::endl;
                break;
            }
        }
    } 

}

