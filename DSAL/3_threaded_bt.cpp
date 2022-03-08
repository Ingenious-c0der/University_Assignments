#include <iostream>
using namespace std;


class Node{

	int data,lbit,rbit;
	Node * left =nullptr;
	Node* right = nullptr;
public:

	Node(int data,int lbit = 0 ,int rbit = 0 ){
		this->data = data;
		this->lbit = lbit;
		this->rbit = rbit;
		left = nullptr;
		right = nullptr;

	 }
	//unable to implement custom destructor? 
	friend class TBT;

};

class TBT{
	Node* root_node = nullptr;
public:
	TBT(int data){
		insert(data);
	}
	Node* getPredecessor(Node* curr){
		if(curr->lbit == 1)
		{
			return curr->left;
		}
		else
		{
			curr = curr->left; 
			while(curr->rbit == 0)
			{
				curr = curr->right;
			}
			return curr;
		}
	}
	Node* getSuccessor(Node* curr){
		if(curr->rbit == 1){
			if(curr->data > curr->right->data){

				return curr;
			}
			else{

				return curr->right;
			}
		}
		else
		{
			curr = curr->right;
			while(curr->lbit == 0 ){
				curr = curr->left;
			}
			return curr;
		}
	}
	void insert(int data){
		Node * curr = root_node;
		if (curr == nullptr){
			//case for inserting the first node in TBT
			root_node = new Node(data,1,1);
			root_node -> left = root_node;
			root_node->right = root_node;
			return ;
		}//finding the appropriate node which will be the parent of the new node
		while(1){
			if(data>curr->data ){
				if(curr->rbit == 0 ){
				curr = curr->right;
				}
				else{
					break;
				}
			}
			if(data<curr->data ){
				if(curr->lbit == 0 ){
				curr = curr->left;
				}
				else{
					break;
				}
			}
		}

		if(curr->lbit == 1 and curr->data>data){
			//if the new node is left child
			Node* new_node = new Node(data,1,1);
			new_node ->left = curr->left;
			new_node->right = curr;
			curr->left = new_node;
			curr->lbit  = 0 ;

		}
		else{
			//if the new node is right child
			Node* new_node = new Node(data,1,1);
			new_node ->right = curr->right;
			new_node->left= curr;
			curr->right = new_node;
			curr->rbit  = 0 ;

		}

	}
	
	// void delete_node(int data){
	// 	Node* parent = root_node; 
	// 	Node* child = root_node; 
	// 	Node* to_be_deleted; 
	// 	//finding the to be deleted child and its parent
	// 	while(child->data != data){
	// 		if (data>child->data){
	// 			parent = child;
	// 			child = child->right;
	// 		}
	// 		else
	// 		{
	// 			parent = child; 
	// 			child = child->left; 
	// 		}
	// 	}
	// 	cout<<"parent : "<<parent->data<<endl;
	// 	cout<<"child : "<<child->data<<endl;  

	// 	//checking cases now 
	// 	// root case to be implemented 
	// 	if(parent == child){
	// 		root_node = nullptr;
	// 		return ; 
	// 	}
	// 	to_be_deleted = child; 
	// 	//case I 
	// 	if(child->lbit == 0 and child ->rbit == 0 ){
	// 		parent = child;
	// 		child = child->right;
	// 		while(child->lbit == 0){
	// 			parent = child;
	// 			child = child->left; 
	// 		}
	// 		to_be_deleted->data = child->data;
	// 		to_be_deleted = child; 
	// 	}
	// 	//case II
	// 	if(to_be_deleted->rbit == 0){
	// 		if(parent->right == to_be_deleted)
	// 		{
	// 			Node* pred = getPredecessor(to_be_deleted);
	// 			Node* succ = getSuccessor(to_be_deleted);
	// 			succ->left = pred;
	// 			parent->right = to_be_deleted->right;
	// 		}
	// 		else
	// 		{
	// 			Node* pred = getPredecessor(to_be_deleted);
	// 			Node* succ = getSuccessor(to_be_deleted);
	// 			succ->right = pred;
	// 			parent->left = to_be_deleted->right;
	// 		}
	// 		delete(to_be_deleted);
	// 		return; 
	// 	}
	// 	if(to_be_deleted->lbit == 0 ){
	// 		if(parent->right == to_be_deleted)
	// 		{
	// 			Node* pred = getPredecessor(to_be_deleted);
	// 			Node* succ = getSuccessor(to_be_deleted);
	// 			succ->left = pred;
	// 			parent->right = to_be_deleted->right;
	// 		}
	// 		else
	// 		{
	// 			Node* pred = getPredecessor(to_be_deleted);
	// 			Node* succ = getSuccessor(to_be_deleted);
	// 			succ->right = pred;
	// 			parent->left = to_be_deleted->right;
	// 		}
	// 		delete(to_be_deleted);
	// 		return; 
	// 	}
	// 	//case III
	// 	if(to_be_deleted->rbit == 1 ){
	// 		if(parent->right == to_be_deleted)
	// 		{
	// 			parent->right = to_be_deleted->right;
	// 			parent->rbit = 1 ;
				
				
	// 		}
	// 		else
	// 		{
	// 			parent->left = to_be_deleted->left; 
	// 			parent->lbit = 1 ;
	// 		}
	// 		to_be_deleted->left,to_be_deleted->right = nullptr ;
	// 		delete(to_be_deleted);
	// 	}
	// }


	void Inorder(){

		Node* ptr = root_node;
		if (ptr == nullptr){
			cout<<"Tree is empty"<<endl;
			}
		//getting the to the leftmost node
		while(ptr->lbit == 0 ){
			ptr = ptr->left ;
		}
		Node* next;
		while(1){
			cout<<ptr->data<<" ";
			next = getSuccessor(ptr);
			if(ptr == next){
				//condition for rightmost node
				break;
			}
			else{
				ptr = next;
			}
		}
	}
	void Preorder(){
		Node* ptr = root_node;
		//empty tree case
		if (ptr == nullptr){
			cout<<"Tree is empty"<<endl;
			return ;
		}
		//flag for checking whether the link came from a thread or from a branch
		//if it comes from the thread , the left sub tree is already printed , so no need to print it
		// if it comes from the branch its the same sub problem as the original case
		int flag = 0 ;
		//exit condition when we reach the rightmost node
		bool Not_reached_end = true;
		while(Not_reached_end){
			//only if the node is not already printed, print it
			if (flag == 0 ){
				cout<<ptr->data<<' ';
			}
			
			while(ptr->lbit == 0 and flag == 0){

					ptr = ptr->left;
					cout<<ptr->data<< " ";

			}
			//if we are traveling down with a right branch , flag should be 0 
			if(ptr->rbit == 0){
				ptr = ptr->right;
				flag = 0 ;
			}
			else{
				//checking if the current node (ptr) is the rightmost node or not 
				//if it is the rightmost node , break and while loop and return 
				if(ptr->data >= ptr->right->data){
					Not_reached_end = false;
				}
				//now we are traveling up with the help of right threads ,so flag should be one
				else{
					ptr = ptr->right;
					flag = 1;
				}
			}
		}

	}
};

int main(){
	TBT tree(10);
	tree.insert(5);
	tree.insert(4);
	tree.insert(6);
	tree.insert(7);
	tree.insert(11);
	tree.insert(13);
	tree.insert(12);
	
	tree.Inorder();
	return 0 ;
}
