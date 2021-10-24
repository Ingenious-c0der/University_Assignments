#include <iostream>
using namespace std;

template<typename T,int size>
class Stack {
private:
	T* stack;
	int top = -1;
public:
	Stack();
    void pop();
	void push(T const &val);

	void show();



};
template<typename T , int size>
void Stack<T,size>::pop(){
        if (top == -1) 
		{
			cout << "Stack Underflow" << endl; 
		}
		else 
		{
			top--;
		}
}
template<typename T , int size>
void Stack<T,size>::push(T const& val){
	if (top < size-1)
        {
		top++;
		stack[top] = val;
	}
	else 
	{
		cout << "stack overflow" << endl;
	}
	
}
template<typename T , int size>
Stack<T,size>::Stack()
{
    	stack = new T[size];
}
template<typename T , int size>
void Stack<T,size>::show() {
	for (int i = 0; i < top+1; i++)
		{
		    cout << stack[i] <<" ";
		}
        cout<<endl;
}


int main() {
   Stack<string,3> s1;
    s1.push("str1");
    s1.push("str2");
    s1.push("str3");
    s1.push("str4");
    s1.show();

    Stack<char,3> c1;
    c1.push('c');
    c1.show();

    Stack<int,3> i1;
    i1.push(3);
    i1.push(7);
    i1.push(8);
    i1.show();
	return 0; 
}
