#include <iostream>
#include <thread>
#include <mutex>
#include <string>



//machine power is the rate at which the machine can process jobs
std::mutex printer_mutex;
bool is_printing = false; // condition variable for exclusive printing
void wait_print()
{
    while (is_printing)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void printLine(std::string line)
{

    if (printer_mutex.try_lock())
    {
        is_printing = true;
        std::cout << "Event :  " << line << std::endl;
        printer_mutex.unlock();
        is_printing = false;
    }
    else
    {
        wait_print();
        printLine(line);
    }
}

bool paused = false;
void wait_pause()
{
    while (paused)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

class Job
{
    int weight = 0;
    bool is_completed = false;
    std::string name = "none";
    static int jobs_count;

public:
    Job()
    {

    }
    Job(std::string name)
    {
        this->name = name;
    }
    Job(int weight)
    {
        this->weight = weight;
        name = "Job" + std::to_string(jobs_count);
        jobs_count++;

    }

    void executeJob(int executed)
    {
        weight -= executed;
        if (weight <= 0)
        {
            is_completed = true;
            printLine("Job " + name + " completed.");
        }
    }
    friend class CircularLinkedList;
};
class Node
{
    Node *next;
    Job job;

public:
    Node(Job job)
    {
        this->job = job;
    }
    friend class CircularLinkedList;
};
class CircularLinkedList
{
    int node_count = 0;
    Node* head ;
    static Node *current;

public:
    CircularLinkedList()
    {
        head = nullptr;
    }

    void NodeStatus()
    {
        int loop_ctr = 0;
        
        if(!head)
        {   
           
            std::cout << "Job queue is Empty" << std::endl;
            return;
        }
        printLine("------------- Job Status ------------");
        for (auto ptr = head, fptr = head; ptr->next != nullptr; fptr = ptr, ptr = ptr->next)
        {

            if (ptr->job.name == head->job.name)
            {
                loop_ctr++;
                if (loop_ctr == 2)
                {
                    printLine("-------------------------------------");
                    return;
                }
            }
            
            printLine(ptr->job.name + " : " + std::to_string(ptr->job.weight));
           
        }
         
    }

    void addNode(Job j)
    {
        if (head)
        {
            Node *newJob = new Node(j);
            newJob->next = head->next;
            head->next = newJob;
            node_count++;
            printLine(newJob->job.name + " added.");
        }
        else
        {
            node_count++;
            head = new Node(j);
            head->next = head;
            printLine(head->job.name + " added.");
        }
    }
    void _displayStruct()
    {

    }
    void removeNode(Job j)
    {
        int loop_ctr = 0;
        for (auto ptr = head->next, fptr = head; ptr->next != nullptr; fptr = ptr, ptr = ptr->next)
        {
            if (ptr->job.name == j.name)
            {
                if(ptr->job.name == head->job.name)
                {
                    if(node_count>1)
                    {
                        head = head->next;
                    }
                    else
                    {
                        head = nullptr;
                    }
                    
                }
                fptr->next = ptr->next;
                ptr = nullptr; 
                delete (ptr);
                node_count--;
                printLine(j.name + " removed.");
                return;
            }
            if (ptr->job.name == head->job.name)
            {
                loop_ctr++;
                if (loop_ctr == 2)
                {
                    printLine("No job named " + j.name + " found.");
                    return;
                }
            }
        }
    }

    void updateNextJob(int val)
    {
        if (current)
        {
            printLine(current->job.name + " is currently under execution.");
            current->job.executeJob(val);
            Node* nxt = current->next; // incase the current Node * job is completed
            if (current->job.is_completed)
            {
                removeNode(current->job);
            }
             current = nxt;           
        }
        else
        {
            head->job.executeJob(val);
            current = head->next;
        }
        
        if (node_count == 0)
        {
            printLine("--- Execution Life Cycle Complete ---");
            printLine("Node count : "+ std::to_string(node_count));
            head = nullptr; 
            current = nullptr; 
            return;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
        if (paused)
        {
            printLine("--- Execution Paused ---");
            wait_pause();
        }
        updateNextJob(val);
    }
};
Node *CircularLinkedList::current = nullptr;

int Job::jobs_count = 0;

class Executor
{

    std::thread current_thread;
    CircularLinkedList round_robin_CLL;

public:
    Executor()
    {
        round_robin_CLL = CircularLinkedList();
    }

    void beginExecution(int power)
    {
        //begin is called to resume the execution to
        if(paused)
        {
           printLine("Resuming Execution");
           resumeExecution();
           return; 
        }
        current_thread = std::thread([this, power]()
                                     { round_robin_CLL.updateNextJob(power); });
        current_thread.detach();
    }
    void displayStatus()
    {
        round_robin_CLL.NodeStatus();
    }
    void stopExecution()
    {
        paused = true;
    }
    void resumeExecution()
    {
        if (!paused)
        {
            printLine("Execution is not paused.");
            return ; 
        }
        paused = false;
        printLine("Execution resumed");
    }
    void addJob(Job j)
    {
        round_robin_CLL.addNode(j);
    }
    void removeJob(Job j)
    {
        round_robin_CLL.removeNode(j);
    }
};

int main()
{
    Executor ex = Executor();
    while (true)
    {
        std::cout << "*********MENU*********\n1.Add Job\n2.Remove Job\n3.Display Status\n4.Pause Execution\n5.Start/Resume Execution" << std::endl;
        int choice;
        std::cin >> choice;
        switch (choice)
        {
        case 1:
        {
            int weight;
            std::cout << "Enter weight of job : ";
            std::cin >> weight;
            Job j = Job(weight);
            ex.addJob(j);
            break;
        }
        case 2:
        {
            std::string name;
            std::cout << "Enter name of the job to be removed : ";
            std::cin >> name;
            Job j = Job(name);
            ex.removeJob(j);
            break;
        }
        case 3:
        {
            ex.displayStatus();
            break;
        }
        case 4:
        {
            ex.stopExecution();
            break;
        }
        case 5:
        {   int power = 0 ; 
            printLine("Enter the power of the machine :");
            std::cin>>power ;
            ex.beginExecution(power);
            break;
        }
        default:
        {
            printLine("Invalid choice.");
            break;
        }
        }
    }
}