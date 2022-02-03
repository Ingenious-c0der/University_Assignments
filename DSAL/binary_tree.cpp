#include <iostream>
using namespace std;
//Beginning with an empty binary tree, Construct binary tree by inserting the values in the order given. After constructing a binary tree perform following operations on it-
//
//Perform inorder
//preorder and post order traversal
//Change a tree so that the roles of the left and right pointers are swapped at every node
//        Find the height of tree
//Copy this tree to another [operator=]
//Count number of leaves, number of internal nodes.
//Erase all nodes in a binary tree.
//(implement both recursive and non-recursive methods)
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

class Node{
    char data;
    Node* left_child = nullptr;
    Node * right_child  = nullptr;
    
    explicit Node(char d){
        data = d ;
    }
    friend class Binary_Tree;
};

class Binary_Tree {
    Node *root;
public:

    Binary_Tree() { root = nullptr; };

    void create(char x) {
        if (root)
            insert(root, x);
        else
            root = new Node(x);

    }
    Node *insert(Node *t, char c) {
        Node *P ;
        if (t == nullptr) {
            P = new Node(c);
            return P;
        } else {
            char choice;
            cout << "Where do you want to insert the node , left or right side of " << t->data<< " : ";
            cin >> choice;
            if (choice == 'l' or choice == 'L') {
                t->left_child = insert(t->left_child, c);
            } else {
                t->right_child = insert(t->right_child, c);
            }
        }
        return t;
    }
    void recursive_pre_order(Node* t){
        if (t){
            cout<<t->data<<" ";
            recursive_pre_order(t->left_child);
            recursive_pre_order(t->right_child);
            
        }
    }
    void recursive_post_order(Node* t){
        if(t){
            recursive_post_order(t->left_child);
            recursive_post_order(t->right_child);
            cout<<t->data<<" ";
            
        }
    }
    void recursive_in_order(Node*t){
        if(t){
            recursive_in_order(t->left_child);
            cout<<t->data<<" ";
            recursive_in_order(t->right_child);
            
        }
    }

    void Non_rec_in_order(){
        Stack<Node*,100> s;
        Node* T = get_root();
        while(T or ! s.is_empty()){
            while(T){
                s.push(T);
                T = T->left_child;
            }
            if(s.is_empty()){
                return ; 
            }
            T = s.get_top();
            s.pop();
            
            cout<<T->data<<" ";
            T = T->right_child;
        }
    }
    void Non_rec_pre_order(){
         Stack<Node*,100> s;
        Node* T = get_root();
        while(T or ! s.is_empty()){
            while(T){
                cout<<T->data<<" ";
                if(T->right_child){
                    s.push(T->right_child);
                }
                T = T->left_child;
            }
            
            if(s.is_empty()){
                return ; 
            }
            T = s.get_top();
            s.pop();
        }
    }
    void Non_rec_post_order(){
        Node * T = get_root(),*p1;Node*temp = new Node('#');
        Stack<Node*,100> s;
        while(true){
            while(T){
                s.push(T);
                if(T->right_child){
                    s.push(T->right_child);
                    s.push(temp);
                }
                T = T->left_child;
        }
        
        if(s.is_empty()){
            if(p1){
                cout<<p1->data<<" ";
                p1 = nullptr;
            }
            return ; 
        }
        else{
            p1 = s.get_top();
            s.pop();
        }
        while(p1!=temp and ! s.is_empty())
        {
            cout<<p1->data<<" ";
            p1 = s.get_top();
            s.pop();
        }
        if(!s.is_empty()){
            T = s.get_top();
            s.pop();
        }
        
        }
    }

    Node* get_root(){
        return root;
    }
    void DestroyRecursive(Node* t){
        if(t){
            DestroyRecursive(t->right_child);
            DestroyRecursive(t->left_child);
            delete t ;
        }
    }
    void operator = ( const Binary_Tree &T){

    }

    int height_of_tree(Node* t){
        if(!t)
            return 0;
        int l = height_of_tree(t->left_child);
        int r = height_of_tree(t->right_child);
        return max(l,r) + 1;
    }

    int mirror_tree(Node* t){
        if(!t)
            return 0;
        int l = mirror_tree(t->left_child);
        int r = mirror_tree(t->right_child);
        Node* temp = t->left_child;
        t->left_child = t->right_child;
        t->right_child = temp;
        return max(l,r) + 1;
    }

    int  count_leaf_nodes(Node* t){
        if(!t)
            return 0;
        if(!t->left_child and !t->right_child)
            return 1;
        int l = count_leaf_nodes(t->left_child);
        int r = count_leaf_nodes(t->right_child);
        return l + r;
    }

    ~Binary_Tree(){
        DestroyRecursive(get_root());
    }
};

int main(){
    Binary_Tree b1;
    char choice ='y';
    char root_val ;
    cout<<"Enter the Node value for root node : ";
    cin>> root_val;
    b1.create(root_val);
    while (choice=='y'){
        cout<<"Add one more node ? (y/n)";
        cin>>choice ;
        if (choice == 'y') {
            cout << "Enter the value for the node : ";
            cin >> root_val;
            b1.insert(b1.get_root(), root_val);
        }
    }
    cout<<"Inorder Traversal :",b1.recursive_in_order(b1.get_root());
    // cout<<"PreOrder Traversal :",b1.recursive_pre_order(b1.get_root());
    // cout<<"PostOrder Traversal :",b1.recursive_post_order(b1.get_root());
    // cout<<"Non-Recursive Inorder Traversal :",b1.Non_rec_in_order();
    // cout<<"Non-Recursive PreOrder Traversal :",b1.Non_rec_pre_order();
    // cout<<"Non-Recursive PostOrder Traversal :",b1.Non_rec_post_order();
    cout<<"Height of the tree : "<<b1.height_of_tree(b1.get_root());
    b1.mirror_tree(b1.get_root());	
    cout<<"Mirror of the tree : ";
    b1.recursive_in_order(b1.get_root());
    return 0 ;


}
