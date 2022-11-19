#include <thread>
#include <iostream>
#include <mutex>
#include <vector>
#include<string> 


const float production_to_consumption_ratio = 1.2; // sooner or later if this is not one, the buffer will either tend to be frequently full or empty
const int base_wait_millis = 1000; // the base wait time for the producer and consumer threads

std::mutex printer_mutex; 
void printLine(std::string line )
{
    while(true) 
    {
        if(printer_mutex.try_lock())
        {
            std::cout<< "Event :  "<<line << std::endl;
            printer_mutex.unlock();
            break ; 
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }

    }
}



class Buffer
{

    int max_cap = 0;
    int count = 0;
    

public:
    std::mutex buffer_mutex;
    int* buffer;
    Buffer(int max_cap)
    {
        this->max_cap = max_cap;
        buffer = new int[max_cap];
        for(int i  = 0 ; i < max_cap ; i++ )
        {
            buffer[i] = -1 ;
        }
    }
    bool isFull()
    {
        return count == max_cap;
    }
    void push(int Item)
    {
        buffer[count++] = Item;
        displayBuffer(); 
    }
    
    bool isEmpty()
    {
        return count == 0;
    }
    int consume()
    {
        int top = buffer[count - 1];
        buffer[count - 1] = - 1 ;
        count -- ;
        displayBuffer(); 
        return top;
    }

    void wait_full()
    {
        while (isFull())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    void wait_empty()
    {
        while (isEmpty())
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
    void displayBuffer()
    {
        std::string buffer_string = "Buffer : ";
        for(int i = 0 ; i < max_cap; i++)
        {
            buffer_string+= std::to_string(buffer[i]) + " | ";
        }
        printLine(buffer_string);
    }
};
class Item
{
    int id = 0;

public:
    Item()
    {
        id = std::rand() % 100;
    }
    friend class Producer;
    friend class Consumer;
};

class Producer
{
    public: 
    Producer()
    {
    }
    void produce(Buffer &buffer)
    {
        while (true)
        {
            Item item = Item();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
           
            printLine("Producer Produced Item with id " + std::to_string(item.id));
            if (buffer.isFull())
            {
                
                printLine("Buffer is full , Producer is waiting for empty slot");
                buffer.wait_full();
            }
            while (true)
            {
                if (buffer.buffer_mutex.try_lock())
                {
                    buffer.push(item.id);
                    buffer.buffer_mutex.unlock();
                    break;
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            }
        }
    }
};

class Consumer
{
     public: 
    Consumer(){ }; 
    void consume(Buffer & buffer)
    {
        while (true)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(int(base_wait_millis * production_to_consumption_ratio)));
            if (buffer.isEmpty())
            {
                printLine("Buffer is empty , Consumer is waiting for item");
                buffer.wait_empty();
            }
            while (true)
            {
                if (buffer.buffer_mutex.try_lock())
                {
               
                    printLine("Consumer Consumed item with id " + std::to_string(buffer.consume()));
                     buffer.buffer_mutex.unlock();
                    break;
                }
                else
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                }
            }
        }
    }
};



int main()
{
    Buffer buffer(10);
    Producer producer;
    Consumer consumer;
    
    std::thread producer_thread(&Producer::produce, producer, std::ref(buffer));
    std::thread consumer_thread(&Consumer::consume, consumer, std::ref(buffer));
    consumer_thread.join();
    producer_thread.join();
   
    return 0;
}