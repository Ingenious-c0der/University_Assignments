#include <iostream>
#include <map>
#include <math.h>

using namespace std;
std::map<char, int> precedence_map = {
	{'/', 2},
	{'-', 1},
	{'+', 1},
	{'*', 2},
	{'^', 3}};
template <typename T, int size>
class Stack
{
private:
	T *stack;
	int top = -1;

public:
	Stack();
	void pop();
	void push(T const &val);
	T get_top();
	void show();
	bool is_empty();
};
template <typename T, int size>
void Stack<T, size>::pop()
{
	if (top == -1)

	{
		cout << "Stack Underflow" << endl;
	}
	else
	{
		top--;
	}
}
template <typename T, int size>
bool Stack<T, size>::is_empty()
{
	return top == -1;
}
template <typename T, int size>
void Stack<T, size>::push(T const &val)
{
	if (top < size - 1)

	{
		top++;
		stack[top] = val;
	}
	else
	{
		cout << "stack overflow" << endl;
		top = -1;
	}
}
template <typename T, int size>
Stack<T, size>::Stack()
{
	stack = new T[size];
}
template <typename T, int size>
void Stack<T, size>::show()
{
	for (int i = 0; i < top + 1; i++)

	{
		cout << stack[i] << " ";
	}
	cout << endl;
}
template <typename T, int size>
T Stack<T, size>::get_top()
{
	return stack[top];
}
class InfixtoPostfix
{
	string input;
	string result;
	Stack<char, 10> stack;

public:
	InfixtoPostfix(string s)
	{
		input = s;
	}

	bool precedence_check(char operator_1, char operator_2)
	{
		return precedence_map[operator_1] > precedence_map[operator_2];
	}
	bool is_operator(char c)
	{
		return (c == '*' or c == '-' or c == '/' or c == '^' or c == '+');
	}

	string convert()
	{
		for (int i = 0; i < input.length(); i++)
		{
			if (is_operator(input[i]))
			{
				char operator_1 = input[i];
				char operator_2 = stack.get_top();
				while (not precedence_check(operator_1, operator_2))

				{
					result.push_back(operator_2);
					stack.pop();
					operator_2 = stack.get_top();
				}
				stack.push(operator_1);
			}

			else if (input[i] == '(')
			{

				stack.push(input[i]);
			}
			else if (input[i] == ')')
			{
				while (stack.get_top() != '(')
				{
					result.push_back(stack.get_top());
					stack.pop();
				}
				stack.pop(); //popping the last (
			}
			else
			{
				result.push_back(input[i]);
			}
		}
		while (not stack.is_empty())
		{
			result.push_back(stack.get_top());
			stack.pop();
		}
		return result;
	}

	float match_operator(char op, float operand_1, float operand_2)
	{
		if (op == '+')
			return operand_1 + operand_2;
		else if (op == '-')
			return operand_2 - operand_1;
		else if (op == '*')
			return operand_1 * operand_2;
		else if (op == '/')
			return operand_2 / operand_1;
		else if (op == '^')
			return pow(operand_2, operand_1);
		else
			return 0;
	}

	float evaluate()
	{
		float storage = 0;
		float value = 0;
		Stack<float, 10> num_stack;
		map<char, int> operand_map;
		if (result == "")
		{
			cout << "Invalid Expression" << endl;
			return 0;
		}
		else
		{
			for (int i = 0; i < result.length(); i++)
			{
				if (is_operator(result[i]))
				{
				}
				else
				{
					cout << "Enter the value for " << result[i] << " : ";
					cin >> value;
					cout << endl;
					operand_map[result[i]] = value;
				}
			}
			for (int i = 0; i < result.length(); i++)
			{
				if (is_operator(result[i]))
				{
					auto operand_one = num_stack.get_top();
					num_stack.pop();
					auto operand_two = num_stack.get_top();
					num_stack.pop();

					storage = match_operator(result[i], operand_one, operand_two);
					num_stack.push(storage);
				}
				else
				{
					num_stack.push(operand_map[result[i]]);
				}
			}
		}
		cout<<"The result is : "<<storage<<endl;
		return storage;
	}
};

int main()
{
	int choice;
	string input;

	while (true)
	{
		cout << "***********Menu***********\nEnter your choice\n1.Input Expression\n2.Get postfix notation\n3.Get Value\n4.Exit\nchoice : ";
		cin>>choice ; 
		switch (choice)
		{
		case 1:
		{

			cout << "Enter the expression : ";
			cin >> input;

			break;
		}

		case 2:
		{
			InfixtoPostfix infix(input);
			cout << "Postfix notation : " << infix.convert() << endl;
			break;
		}
		case 3:
		{
			InfixtoPostfix infix(input);
			infix.convert();
			infix.evaluate() ;
			break;
		}

		case 4:
			exit(0);
		}
	}
}
