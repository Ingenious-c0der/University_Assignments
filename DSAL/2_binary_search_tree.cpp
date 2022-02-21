
#include <iostream>
using namespace std;
class Node{
	Node* right;
	Node* left;
	string keyword;
	string meaning;
public:
	Node(string keyword, string meaning){
		this->meaning = meaning;
		this->keyword = keyword;
		right = nullptr;
		left = nullptr;
	}
	Node(){
		meaning = "";
		keyword = "";
		right = nullptr;
		left = nullptr;
	}
	~Node(){
		delete right; 
		delete left; 
	}
	friend class BinarySearchTree;
};
class BinarySearchTree{
	Node * root = nullptr ;
public:
	BinarySearchTree(){
		insert(root);
	}
	void insert(Node * n,string keyword = "",string meaning = ""){
		if(root){

		if(meaning==""){
		cout<<"Enter the meaning for the keyword : ";
		cin.ignore();
		getline(cin,meaning);
		}
		if(keyword==""){
			cout<<"Enter the keyword for the node : ";
			cin>>keyword;
		}
		if (keyword>n->keyword){
			if(n->right){

				insert(n->right,keyword,meaning);
			}
			else{
				n->right = new Node(keyword,meaning);
			}
		}
		else{
			if(n->left){
				insert(n->left,keyword,meaning);
			}else{
				n->left = new Node(keyword,meaning);
			}
		}
		}else{
			if(keyword == "" or  meaning == ""){
			cout<<"Enter the keyword for root node : ";
			cin>>keyword;

			cout<<"Enter the meaning for the word "<<keyword<<" : ";
			cin.ignore();
			getline(cin,meaning);
			}
			root  = new Node(keyword,meaning);
		}
	}
	void display_sorted(Node* n){
		if(!root){
			cout<<"empty binary search tree"<<endl ;
			return ;
		}
		if(n){
			display_sorted(n->left);
			cout<<n->keyword<<" : "<<n->meaning<<endl;
			display_sorted(n->right);
		}
	}
	void display_descending(Node* n){
		if(!root){
			cout<<"empty binary search tree"<<endl ;
			return ;
		}
		if(n){
			display_descending(n->right);
			cout<<n->keyword<<" : "<<n->meaning<<endl;
			display_sorted(n->left);
		}
	}

	bool Search_tree(string keyword){
		if(!root)
			return false; 
		
		Node* curr = root;
		
		while(curr->keyword!=keyword){
			if (curr->keyword>keyword){
				curr = curr->left;
			}
			else{
				curr = curr->right;
			}

			if(curr==nullptr){
				return false;
			}
		}
	   return true;

	}

	Node* Search_tree_return_node(Node* n ,string keyword){
		if(!root)
			return nullptr; 
		if(n->keyword == keyword)
			return n;
		else if (keyword>n->keyword){
			if(n->right)
				Search_tree_return_node(n->right,keyword);
			else
				return nullptr;
		}
		else{
			if(n->left)
				Search_tree_return_node(n->left,keyword);
			else
				return nullptr;
		}

	}

    void update_keyword(string keyword){

    	Node* key = Search_tree_return_node(this->root,keyword);
    	if(key == nullptr){
    		cout<<"Word not found"<<endl;

    	}
    	else{
    		string new_meaning;
    		cout<<"Enter the new meaning for the word "<<key->keyword<<" : ";
			cin.ignore();
    		getline(cin,new_meaning);
    		key->meaning = new_meaning;

    	}
    }

	Node* get_root(){
		return root;
	}

	void delete_node(string Keyword){
		if(!root){
				cout<<"tree is already empty !"<<endl;
				return;
			}
		Node* parent = root ;
		Node* child = root;
		//finding the appropriate parent and child. 
		while(child->keyword != Keyword){
			if(child->keyword>Keyword){
				parent = child;
				child = child->left;
			}
			else{
				parent = child;
				child = child->right;
			}
			if(child == nullptr ){
				cout<<"Word not found"<<endl;
				return;
			}
		}

		Node * to_be_deleted = child;
		//isolated root case (can be removed after overthinking a bit. it just seems to work rn )
		if(child == parent){
			if(child->left == nullptr and child->right == nullptr){
				root = nullptr;
				delete(child);
				return ; 
			}
			
		}
		//case I : both children are not none 
		//convert case I into case II or case III 
		//find the inorder successor 
		if(child->left != nullptr and child->right != nullptr){
			child = child->right ; 
			while(child->left != nullptr){
				parent = child ;
				child = child->left ; 
			}
			to_be_deleted->keyword  = child->keyword;
			to_be_deleted->meaning = child->meaning; 
			to_be_deleted = child; 
		}
		//case II , direct adoption => single child single parent. 
		if(to_be_deleted->right != nullptr )
		{	
			if(parent->left == child)
				parent->left = to_be_deleted->right; 
			else
				parent->right = to_be_deleted->right;
			to_be_deleted->right = nullptr; 
			delete(to_be_deleted);
			return;
		}
		//case III , leaf node 
		if(to_be_deleted->right == nullptr)
		{
			parent->left = nullptr; 
			delete(to_be_deleted);
		}
		cout<<"root val : "<<root->keyword<<endl; 

	}
};

int main() {
	int choice;
	string keyword;
	string meaning;
	BinarySearchTree b1;
	
	while(true){
		cout<<"\n*********Menu*********\n1.Insert a new Word\n2.Search a word\n3.Display in Ascending order\n4.Display in Descending order\n5.Update word\n6.Delete Node\n7.Exit\n";
		cin>>choice;
		switch(choice){
		case 1:
			bool check ;
			char ch;
			cout<<"Enter the keyword : ";
			cin>>keyword;
			check = b1.Search_tree(keyword);
			
			if (check){
				cout<<"The word "<<keyword<<" already exists.Do you want to update it ? (y/n) :";
				cin>>ch;
				if(ch=='y'){
					b1.update_keyword(keyword);
				}
			}
			else{
				cout<<"Enter the meaning for "<<keyword<<" : ";
				cin.ignore();
				getline(cin,meaning);
				b1.insert(b1.get_root(),keyword,meaning);
			}
			break;

		case 2:
			bool status;
			cout<<"Enter the word to be searched : ";
			cin>>keyword;
			status = b1.Search_tree(keyword);
			if(not status)
				cout<<"Word not found"<<endl;
			break;
		case 3:
			b1.display_sorted(b1.get_root());
			break;
		case 4:
			b1.display_descending(b1.get_root());
			break;
		case 5:
			cout<<"Enter the word to be updated : ";
			cin>>keyword;
			b1.update_keyword(keyword);
			break;
		case 6:
			cout<<"Enter the keyword for the node to be deleted : ";
			cin>>keyword;
			b1.delete_node(keyword);
			break;
		case 7:
			exit(0);

	}
	}
	return 0;
}
