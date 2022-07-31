#include<iostream>
using namespace std;


class Pair{
	string word = "";
	string meaning = "";
	Pair(){
		word = "";
		meaning = "" ;
	};
	Pair(string word,string meaning){
		this->word = word;
		this->meaning = meaning;
	}

	friend class LinkedList;
	friend class Node ;

};

class Node{
	Node* next = nullptr;
	Pair* pair ;
	Node(){

	 pair = nullptr;
	}
	Node(string word , string meaning){
		pair = new Pair(word,meaning);
	}

	friend class LinkedList;
};


class LinkedList{
	Node * first ;

	LinkedList(){
		first = nullptr;
	}
	void insert(string word,string meaning){
		if (first){
			Node * temp = new Node(word,meaning);
			temp->next = first->next;
			first->next = temp ;
		}
		else{
			first = new Node(word,meaning);
		}
	}
	bool search(string word){
		//really hacky way to iterate through two variables of different data types
		for(struct {Node* temp  ;int count;} s = {first,0}; s.temp!=nullptr ; s.temp = s.temp->next,s.count = s.count+1){
			if(s.temp->pair->word == word ){

							cout<<"Word : "<<word <<"   "<<"Meaning : "<<s.temp->pair->meaning<<" Comparisons Required : "<<s.count<<endl;
							return true;

						}
		}
		cout<<"Word to be searched : " <<word << " not found"<<endl;
        return false;
	}


    bool _search(string word){
		//really hacky way to iterate through two variables of different data types
		for(struct {Node* temp  ;int count;} s = {first,0}; s.temp!=nullptr ; s.temp = s.temp->next,s.count = s.count+1){
			if(s.temp->pair->word == word ){

							cout<<"Word : "<<word <<"   "<<"Meaning : "<<s.temp->pair->meaning<<" Comparisons Required : "<<s.count<<endl;
							return true;

						}
		}
		
        return false;
	}


	void update(string word, string meaning){
	    for(struct {Node* temp  ;int count;} s = {first,0}; s.temp!=nullptr ; s.temp = s.temp->next,s.count = s.count+1){
			if(s.temp->pair->word == word ){
                s.temp->pair->meaning = meaning;
		}
		}
		cout<<"Word to be updated : " <<word << " not found"<<endl;

	}

	void _delete(string word){


		for(auto temp = first, prev = first ; temp!=nullptr ; prev = temp,temp = temp->next){
			if(temp->pair->word == word){
				prev->next = temp->next;
				delete temp ;
				cout<<"Word " << word << " deleted"<<endl ;
				return ;
			}
		}
		cout<<"Word to be deleted : "<< word <<" not found "<<endl ;
	}
	friend class Hash_table;
};

class Hash_table{
	LinkedList * array ;
	int max_val = 0 ;
public:
	Hash_table(int);
	int _hash(string );
	void search(string );
	void _delete(string );
	void insert(string,string);


};

Hash_table::Hash_table(int max_val){
	this->max_val = max_val;
	array = new LinkedList[max_val];
}

int Hash_table::_hash(string word){
	
	return tolower(word[0])%26;
}
void Hash_table::search(string word){

	 array[_hash(word)].search(word);
}

void Hash_table::insert(string word, string meaning){
    if( array[_hash(word)]._search(word))
    {
        char choice ;
        cout<<"Word already exists in the dictionary. Do you want to update the meaning?(y/n) ";
        cin>>choice;
        if(choice == 'y'){
            string mean;
            cout<<"Enter the new meaning : ";
            cin>>mean;
            array[_hash(word)].update(word,meaning);
            cout<<"Word updated successfully "<<endl;
        }
        else{
            return ;
        }

    }
    else{
	  array[_hash(word)].insert(word,meaning);
    }

}

void Hash_table::_delete(string word){
	array[_hash(word)]._delete(word);
}



int main(){
	Hash_table ht(30) ;
	ht.insert("hello","greeting");
    ht.insert("highway","Roadway connecting two or more cities");
	ht.insert("physics","a subject");
	ht.insert("picometer","unit of measure");

	ht.search("hello");
    ht.search("highway");
    ht.search("physics");
    ht.search("himalayas");
    ht.search("picometer");
}
