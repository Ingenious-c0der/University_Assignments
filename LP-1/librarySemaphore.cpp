#include <iostream>
#include <string>
#include <thread>
#include <mutex>


/*
Person A: Implementing Semaphores in Java is so easy! 
Person B: Exactly why I chose to implement them in C++.
few days later... 
Person B : <Sitting in some underground cave trying to figure out how to group mutexes or construct semaphores in C++>
Person A : <Completes the task but does not feel the win>
*/

/*
Analogy : Library 
Shared resources: reading tables and books.
Utilizers : Readers
Reading Hall demonstrates the use of counting Semaphore
<In a reading hall , maximum of 2 Readers are allowed to read the book at once if at all it is available>
Issuing the books demonstrates the use of standard mutex or binary Semaphore.
<Once a book is issued, it is unavailable for other Readers for some period of time>
<If that book is being read in the reading hall, it is unavailable for issuing>
Readers are the threads trying to read and issue the books.
*/

//just to make the console output look better
std::mutex printer_mutex ;
bool is_printing = false; // condition variable for exclusive priting 
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

class Book
{
public:
    static int total_books;
    std::string name = " none ";
    std::string issuer_name = " None ";
    std::string reader1_name = " None ";
    std::string reader2_name = " None "; 
    bool is_issued = false; // condition variable for single mutex guard
    int id = -1;
    int shared_reader_count = 0;
    void display_Status()
    {
        if(is_issued)
        {
            printLine("#Book : " + name + " issued to " + issuer_name);
        }
        else if(shared_reader_count == 0)
        {
            printLine(name + " is available");
        }
        else {
           if(shared_reader_count == 1)
           {
               printLine("#Book : " + name + " is being read by " + reader1_name + " on table "+ std::to_string(id));
           }
           else if(shared_reader_count == 2)
           {
               printLine("#Book : " + name + " is shared with " + reader1_name + " and " + reader2_name);
           }
        }
    }
    Book()
    {
        name = "Book" + std::to_string(total_books);
        id = total_books;
        total_books++;
    }

    std::mutex m;
};
int Book::total_books = 0;
class Reader
{
public:
    std::string name;
    Reader(std::string name)
    {
        this->name = name;
    }
};

class Table
{
public:
    static int total_tables;
    std::string name;
    int chairs = 2;
    std::mutex m;

    Table()
    {
        name = "Table" + std::to_string(total_tables);
        total_tables++;
    }
};
int Table::total_tables = 0;
class ReadingHall
{

public:
    Table *tables = nullptr;
    ReadingHall()
    {
    }
    ReadingHall(int books)
    {
        tables = new Table[books];
    }
    void signal(Table &table,Book &book)
    {
        table.m.lock();
        book.m.lock();
        book.shared_reader_count--;
        if(book.shared_reader_count == 1)
        {
            book.reader1_name = book.reader2_name;
            book.reader2_name = "None";

        }
        ++table.chairs;
        book.m.unlock();
        table.m.unlock();
    }
    void wait_read(Book &book, Reader &reader, Table &table)
    {
        while (!can_read_on_table(table))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    void wait_deIssue(Book &book)
    {
        while (book.is_issued)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    };

    void book_chair(Book &book, Reader &reader, Table &table)
    {
        if (table.m.try_lock())
        {
            table.chairs--;
            book.m.lock();
            book.shared_reader_count++;
            if(book.shared_reader_count == 1)
            {
                book.reader1_name = reader.name;
            }
            else if(book.shared_reader_count == 2)
            {
                book.reader2_name = reader.name;
            }
            book.m.unlock();
            table.m.unlock();
        }
        else
        {
            wait_read(book, reader, table);
            book_chair(book, reader, table);
        }
    }

    bool can_issue(Table &table)
    {
        if (table.m.try_lock())
        {
            bool can = table.chairs == 2;
            table.m.unlock();
            return can;
        }
        else
        {
            return false;
        }
    }

    bool can_read_on_table(Table &table)
    {
        if (table.m.try_lock())
        {
            bool can = table.chairs > 0;
            table.m.unlock();
            return can;
        }
        else
        {
            return false;
        }
    }
    void read_book(Book &book, Reader &Reader)
    {
        if (book.is_issued)
        {
            printLine("Book is already issued " + Reader.name + " is waiting for the book to be available for reading");
         
            wait_deIssue(book);
            read_book(book, Reader);
        }
        else
        {

            if (can_read_on_table(tables[book.id]))
            {
                book_chair(book, Reader, tables[book.id]);
                printLine(Reader.name + " is now reading " + book.name + " on table " + tables[book.id].name + " in the reading hall.");

                // reading for 10 seconds
                std::this_thread::sleep_for(std::chrono::seconds(10));
                printLine( Reader.name + " is done reading " + book.name );
                signal(tables[book.id],book);
            }
            else
            {
                printLine( book.name + " is not available for reading to" + Reader.name );
                wait_read(book, Reader, tables[book.id]);
                read_book(book, Reader);
            }
        }
    };
};
class Library
{
public:
    Book *books;

    int book_count;
    ReadingHall reading_hall;
    Library(int n)
    {
        books = new Book[n];
        reading_hall = ReadingHall(n);
        book_count = n;
    }
    void wait(Book &book, Reader &Reader)
    {
        while (book.is_issued || !reading_hall.can_issue(reading_hall.tables[book.id]))
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    };

    void issue_book(Reader &reader, Book *book)
    {

        if (book->m.try_lock())
        {
            if (reading_hall.can_issue(reading_hall.tables[book->id]))
            {
                book->is_issued = true;
                book->issuer_name = reader.name;
                printLine("Issued " +  book->name + " for " + reader.name );
                // issued for 15 seconds
                std::this_thread::sleep_for(std::chrono::seconds(15));
                printLine("De-Issued " + book->name + " for " + reader.name);
                book->m.unlock();
                book->is_issued = false;
            }
            else
            {
               
                book->m.unlock();  // otherwise the lock will overflow
                printLine( book->name + " issuing is currently unavailable for " + reader.name );
                wait(*book, reader);
                issue_book(reader, book);
            }
        }
        else
        {
            printLine(book->name + " issuing is currently unavailable for " + reader.name);
            //std::cout << book->name << " issuing is currently unavailable for " << reader.name << std::endl;
            wait(*book, reader);
            issue_book(reader, book);
        }
    }
    void read_book(Reader reader, Book *book)
    {
        reading_hall.read_book(*book, reader);
    }
};



int main()
{
    
   std::cout << "Enter the number of books in the library: ";
    int n;
    std::cin >> n;
    Library L1 = Library(n);
    int choice = 0  ; 
    std::string readerName  = "R1"; 
    while(true)
    {
        std::cout<<"***** MENU ******\n1.Read Book\n2.Issue Book\n3.Display Library Status\n4.Exit"<<std::endl;
        std::cin>>choice;
        switch(choice)
        {
            case 1 : {
    	            std::cout<<"Enter the name of the reader: ";
                    std::cin>>readerName; 
                    Reader R1 = Reader(readerName);
                    std::cout<<"Enter the number of the book: ";
                    int bookNumber;
                    std::cin>>bookNumber;
                    if(bookNumber>n)
                    {
                        std::cout<<"Invalid book number"<<std::endl;
                        break;
                    }
                    std::thread t1([&L1, &R1,bookNumber]()
                   { L1.read_book(R1, &L1.books[bookNumber]); });
                   t1.detach();
                    break; 
            }
            case 2 :{
                    std::cout<<"Enter the name of the reader: ";
                    std::cin>>readerName; 
                    Reader R2 = Reader(readerName);
                    std::cout<<"Enter the number of the book: ";
                    int bookNumber2;
                    std::cin>>bookNumber2;
                    if(bookNumber2>n)
                    {
                        std::cout<<"Invalid book number"<<std::endl;
                        break;
                    }
                    std::thread t2([&L1, &R2,bookNumber2]()
                   { L1.issue_book(R2, &L1.books[bookNumber2]); });
                   t2.detach();
                    break;
            }
            case 3 :{
                    std::cout<<"Library Status"<<std::endl;
                   
                       for(int i = 0 ; i< n ;i++)
                       {
                        L1.books[i].display_Status();
                       }
                    
                    break;
            }
            case 4:
                return 0 ;
                    


        }

       
    }
  
    return 0 ; 
}