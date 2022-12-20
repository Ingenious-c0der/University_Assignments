#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Node
{
    long long digit;
    int id;
    bool swapped = false;
    Node *next;
    Node *prev;
    Node(long long digit, int id)
    {
        this->digit = digit;
        this->id = id;
        this->next = nullptr;
        this->prev = nullptr;
    }
    friend class CircularLinkedList;
};

class CircularLinkedList
{
    Node *head;
    int size;

public:
    CircularLinkedList(int size)
    {
        head = nullptr;
        this->size = size;
    }

    void addNode(long long digit, int id)
    {
        Node *newNode = new Node(digit, id);
        if (!head)
        {
            head = newNode;
            head->next = head;
            head->prev = head;
        }
        else
        {
            Node *newNode = new Node(digit, id);
            head->prev->next = newNode;
            newNode->prev = head->prev;
            newNode->next = head;
            head->prev = newNode;
        }
    }

    void displayList()
    {
        Node *temp = head;
        while (temp->next != head)
        {
            cout << temp->digit << " ";
            temp = temp->next;
        }
        cout << temp->digit << endl;
    }

    void decryptChain(int id, long long toswap)
    {

        if (toswap == 0)
        {
            return;
        }
        else
        {
            Node *toswapNode = head;
            Node *temp = nullptr;
            Node *temp_neighbor = nullptr;
            while (toswapNode->id != id)
            {
                toswapNode = toswapNode->next;
            }
            temp = toswapNode;
            toswap %= (size - 1);
            if (toswap < 0)
            {
                for (int i = 0; i < abs(toswap); i++)
                {
                    temp = temp->prev;
                }
                temp_neighbor = temp->prev;
                if (toswapNode->id == temp->id || toswapNode->id == temp_neighbor->id)
                {
                    return;
                }

                toswapNode->prev->next = toswapNode->next;
                toswapNode->next->prev = toswapNode->prev;

                toswapNode->next = temp;
                toswapNode->prev = temp_neighbor;
                temp_neighbor->next = toswapNode;
                temp->prev = toswapNode;
            }
            else
            {
                for (int i = 0; i < toswap; i++)
                {
                    temp = temp->next;
                }
                temp_neighbor = temp->next;
                if (toswapNode->id == temp->id || toswapNode->id == temp_neighbor->id)
                {
                    return;
                }
                toswapNode->prev->next = toswapNode->next;
                toswapNode->next->prev = toswapNode->prev;

                toswapNode->prev = temp;
                toswapNode->next = temp_neighbor;
                temp_neighbor->prev = toswapNode;
                temp->next = toswapNode;
            }
        }
    }
    void printSize()
    {
        Node *temp = head;
        int size = 0;
        while (temp->next != head)
        {
            size++;
            temp = temp->next;
        }
        size++;
        cout << size << endl;
    }

    long long getgrooveCoods(int vecSize)
    {

        Node *zeroNode = head;
        Node *ActZero;
        while (zeroNode->digit != 0)
        {
            zeroNode = zeroNode->next;
        }
        ActZero = zeroNode;
        int thousandth = 1000 % vecSize;
        int twoThousands = 2000 % vecSize;
        int threeThousands = 3000 % vecSize;
        for (int i = 0; i < thousandth; i++)
        {
            zeroNode = zeroNode->next;
        }
        long long first = zeroNode->digit;
        zeroNode = ActZero;
        for (int i = 0; i < twoThousands; i++)
        {
            zeroNode = zeroNode->next;
        }
        long long second = zeroNode->digit;
        zeroNode = ActZero;
        for (int i = 0; i < threeThousands; i++)
        {
            zeroNode = zeroNode->next;
        }
        long long third = zeroNode->digit;
        //cout << first << " " << second << " " << third << endl;
        return first + second + third;
    }
};

int main()
{
    CircularLinkedList *list = new CircularLinkedList(5000);
    fstream file("input.txt");
    string line;
    vector<long long> digits;
    int pointer = 0;
    long long key = 811589153;
    while (getline(file, line))
    {
        list->addNode(stoi(line) * key, pointer);
        digits.push_back(stoi(line) * key);
        pointer++;
    }
   // list->displayList();
    
    for (int i = 0; i < 10; i++)
    {
        int count = 0;
        for (auto digit : digits)
        {
            list->decryptChain(count, digit);
            count++;
        }
        cout<< "Round complete : " << i+1 << endl;
        //list->displayList();
    }

    long long x = list->getgrooveCoods(digits.size());
    cout << "Groove co ods : "<< x << endl;
    return 0;
}