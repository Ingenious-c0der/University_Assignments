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

class Book
{
public:
    static int total_books;
    std::string name;
    bool is_issued = false; // condition variable for single mutex guard
    int id = -1;

    int shared_reader_count = 0;

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
    void signal(Table &table)
    {
        table.m.lock();
        ++table.chairs;
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
            // std::cout<<"C:"<<table.chairs<<std::endl;
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
            // std::cout<<"C:"<<table.chairs<<std::endl;
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
            std::cout << "Book is already issued " << Reader.name << " is waiting for the book to be available for reading" << std::endl;
            wait_deIssue(book);
            read_book(book, Reader);
        }
        else
        {

            if (can_read_on_table(tables[book.id]))
            {
                book_chair(book, Reader, tables[book.id]);
                std::cout << Reader.name << " is now reading " << book.name << " on table " << tables[book.id].name << " in the reading hall." << std::endl;
                // reading for 10 seconds
                std::this_thread::sleep_for(std::chrono::seconds(10));
                std::cout << Reader.name << " is done reading " << book.name << std::endl;
                signal(tables[book.id]);
            }
            else
            {
                std::cout << "Book is not available for reading " << Reader.name << std::endl;
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
                std::cout << "Issuing " << book->name << " for " << reader.name << "\n"
                          << std::endl;
                // issued for 15 seconds

                std::this_thread::sleep_for(std::chrono::seconds(15));
                std::cout << "De-Issuing " << book->name << " for " << reader.name << std::endl;
                book->m.unlock();
                book->is_issued = false;
            }
            else
            {
               
                book->m.unlock();  // otherwise the lock will overflow
                std::cout << book->name << " issuing is currently unavailable for " << reader.name << std::endl;
                wait(*book, reader);
                issue_book(reader, book);
            }
        }
        else
        {
            std::cout << book->name << " issuing is currently unavailable for " << reader.name << std::endl;
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
    Library L1(6);
    Reader R1("R1");
    Reader R2("R2");
    Reader R3("R3");
    Reader R4("R4");
    Reader R5("R5");
    Reader R6("R6");
    Reader R7("R7");
    Reader R8("R8");
    Reader R9("R9");
    Reader R10("R10");
    Reader R11("R11");
    Reader R12("R12");
    std::thread t1([&L1, &R1]()
                   { L1.issue_book(R1, &L1.books[0]); });
    std::thread t3([&L1, &R3]()
                   { L1.issue_book(R3, &L1.books[0]); });
    std::thread t2([&L1, &R2]()
                   { L1.issue_book(R2, &L1.books[0]); });
    std::thread t4([&L1, &R4]()
                   { L1.issue_book(R4, &L1.books[0]); });
    std::thread t5([&L1, &R5]()
                   { L1.read_book(R5, &L1.books[1]); });
    std::thread t6([&L1, &R6]()
                   { L1.read_book(R6, &L1.books[1]); });
    std::thread t7([&L1, &R7]()
                   { L1.read_book(R7, &L1.books[1]); });
    std::thread t8([&L1, &R8]()
                   { L1.read_book(R8, &L1.books[1]); });
    std::thread t9([&L1, &R9]()
                   { L1.read_book(R9, &L1.books[1]); });
    std::thread t10([&L1, &R10]()
                    { L1.read_book(R10, &L1.books[1]); });
    std::thread t11([&L1, &R11]()
                    { L1.read_book(R11, &L1.books[1]); });
    std::thread t12([&L1, &R12]()
                    { L1.issue_book(R12, &L1.books[1]); });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();
    t11.join();
    t12.join();

    return 0;
}
