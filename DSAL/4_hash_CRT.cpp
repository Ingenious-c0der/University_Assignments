#include<iostream>
using namespace std;

//declare a max_size var globally , and avoid hard codingt the
//comparison ints  


class Record;
class Hash{
	Record* HashTable_Wrlc;
    Record* HashTable_Worlc ;
	int max_val = 0 ;
public:
	Hash(int);
	bool insert(string, long long int);
	int _hash(Record);
	void search(string);
	void _delete(string);
	~Hash();
};

class Record{

public:
	string name;
		long long int tele_number;
	Record(){
		name = "";
		tele_number = 0 ;
	}
	Record(string name ,long long int tele_number){
		this->name = name ;
		this->tele_number = tele_number;
	}
	void display_record(){
		cout<< "Name : "<<name<<"  Telephone Number : "<<tele_number<<endl ;
	}
	void delete_record(){
		this->name =  "record deleted";
		this->tele_number = 0 ;
	}

};


Hash::Hash(int max){
	max_val = max;
	//hash table for with replacment operations
	HashTable_Wrlc = new Record[max_val];
    //Hash table for without replacement operations
    HashTable_Worlc = new Record[max_val];
}
Hash::~Hash(){
	delete HashTable_Worlc ;
    delete HashTable_Wrlc;
}

bool Hash::insert(string Name , long long int tele_number){
    int count; 
	Record r(Name,tele_number);
    int i = _hash(r);

	if(_hash(HashTable_Wrlc[i]) != i){
        Record t = HashTable_Wrlc[i];
        HashTable_Wrlc[i] = r;
        r = t; 
	}
	else{
		while(HashTable_Wrlc[i% max_val].name != "" && count < max_val){
            count++;
            i++;
           
        }
		if(count!=max_val){
			HashTable_Wrlc[i%max_val] = r;
           
		}
		else{
			cout<<"Following Record was lost because of linear probing with replacement and full slots from hashtable with replacement"<<endl;
			r.display_record();
			

		}
	}
     r.name = Name ;
     r.tele_number = tele_number ;
     i = _hash(r);
     count = 0 ;
     
    while(HashTable_Worlc[i%max_val].name !="" && count < max_val){
        i++;
        count++; 
    }
    if(count!=max_val){
        HashTable_Worlc[i%max_val] = r;
        return true; 
    }else{
        cout<<"No empty place find for inserting the record in hashtable without replacement"<<endl;
        return false;
    }
}




int Hash::_hash(const Record r){

	//can be mod%26 
	return tolower(r.name[0])%max_val;

}



void Hash::search(string Name){
	int comparisons = 1 ;
	int index = _hash(Record(Name, 0));
	cout<<index;

    while(HashTable_Wrlc[index%max_val].name != Name && comparisons<11){
        comparisons++;
    }
    if(comparisons!=11){
        cout<<"Record found in the hashtable with replacement. With "<<comparisons<<" comparisons"<<endl;
         HashTable_Wrlc[index%max_val].display_record();
    }else{
        cout<<"Record not found in the hashtable with replacement"<<endl;
    }

    comparisons = 1; 
    index = _hash(Record(Name, 0));
    while(HashTable_Worlc[index%max_val].name != Name && comparisons<11){
        comparisons++;
    }
    if(comparisons!=11){
        cout<<"Record found in the hashtable without replacement. With "<<comparisons<<" comparisons"<<endl;
         HashTable_Worlc[index%max_val].display_record();
    }else{
        cout<<"Record not found in the hashtable without replacement"<<endl;;
    }



}



void Hash::_delete(string Name){
    int comparisons = 1 ;
	int index = _hash(Record(Name, 0));
    while(HashTable_Wrlc[index%max_val].name != Name && comparisons<11){
        comparisons++;
    }
    if(comparisons!=11){
      
         HashTable_Wrlc[index%max_val].delete_record();
         cout<<"Record deleted from hashtable with replacment"<<endl;
    }else{
        cout<<"Record to be deleted not found in the hashtable with replacement"<<endl;
    }

    comparisons = 1; 
    index = _hash(Record(Name, 0));
    while(HashTable_Worlc[index%max_val].name != Name && comparisons<11){
        comparisons++;
    }
    if(comparisons!=11){
     
         HashTable_Worlc[index%max_val].delete_record();
          cout<<"Record deleted form hashtable without replacement"<<endl;

    }else{
        cout<<"Record to be deleted not found in the hashtable without replacement"<<endl;
    }

}



int main(){
	int choice = 0 ;
	bool suc,sucn;
		Hash table(10);

		while(true){
			cout<<"***********MENU**********\n1. Insert \n2.Search Record \n3.Delete Record \n4.Exit"<<endl;
			cin>>choice;
			switch(choice){
			case 1:{
				string name ;
                cout<<"Enter the name : ";
				cin>>name; 
				cout<<"Telephone number  :";       
                long long int tele_number ;
                cin>>tele_number;
				suc = table.insert(name,tele_number);
            }
				
				break;
			case 2:{
                	string name  ;
				cout<<"Enter the name of the Person to searched";
				cin>>name;
				 table.search(name);
		         break ;
            }
			
			case 3:
			{
				string name  ;
				cout<<"Enter the name of the Person to deleted";
				cin>>name;
				table._delete(name) ;
				
				break;
			}

			case 4:{
                return 0 ;
			
			}
			}
		}





}
