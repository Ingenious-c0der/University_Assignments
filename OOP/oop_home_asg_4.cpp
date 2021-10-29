#include<iostream>
using namespace std;

class Vector{
    int *p;
     int size;
    public:
   
    Vector(){
        p = new int;
        *p = 0 ;
        size = 0; 
    }
    Vector(const Vector& Vec){

            this->p = new int;
            this->size = Vec.size;
           
            for(int i=0;i<size;i++){
            
                *(this->p+i) = *(Vec.p+i);
                
            }
            
        
    }
    Vector(int size){

        this->size = size;
        
        p = new int[size];
        for (int i = 0 ; i<size;i++){
            *(p+i)= 0 ; 
        }
    }
    friend ostream& operator <<(ostream& output,Vector &V);
    friend istream& operator >>(istream& input,Vector &V);
    friend Vector operator *(int multiplier, Vector&V);
    void add_element(int);
    void delete_element(int);
    Vector operator-(Vector &);
   
};

ostream& operator <<(ostream& output,Vector &V){
    for(int i =0 ; i<V.size;i++){
        cout<<*(V.p +i)<<" ";
    }
    return output;

        
}
istream& operator >>(istream& input,Vector &V){
    for(int i=0;i<V.size;i++){
        cout<<"Enter the element number "<<i+1<<" :";
        cin>>*(V.p+i);
    }

    return input;
}
Vector operator *(int multiplier, Vector&V){
        for(int i=0;i<V.size;i++){
            *(V.p+i) = multiplier**(V.p+i);
        }
        return V;
}
void Vector::add_element(int ele){
    *(p+size) = ele;
    size++;
}
void Vector::delete_element(int index){
    int n = size-index;
    for (int i = 0 ; i<n;i++){
        *(p+index+i) = *(p+index+i+1);
    }
    size--;

}
Vector Vector::operator - (Vector & V){
    Vector temp(size);
    if (size==V.size){
        for(int i=0;i<size;i++){
            *(temp.p+i)=*(p+i)-*(V.p+i);
            
           
        }
        
        return temp; }
    else{
        cout<<"Vector sizes don't match"<<endl;
       return temp;
    }
    
        

    
}


int main()
{
    
    Vector vec1;
    vec1.add_element(3);
    vec1.add_element(4);
    vec1.add_element(7);
    vec1.add_element(6);
    vec1.delete_element(1);
    Vector vec2(3);
    cin>>vec2;
    
    vec2 = vec2-vec1;
   
    Vector vec3(vec2);
    cout<<vec3<<endl;

    //Essentially this is happening because before C++17, this doesn't actually construct a Vector directly. 
    //it'll first try to construct one from the int 
    //and then construct vec4 from the temporary Vector produced there. 
    //In C++17, this code works just fine, but the problem is also mostly because 
    //of the way your Vector class is written: it can only be constructed from another Vector that can be modified, 
    //which is not the case for a temporary (i.e. an rvalue). This can easily be fixed by changing the constructor to take const Vector& instead of Vector&, since it doesn't need to be modified in that constructor 
    
    // The int value tries to create a vector and returns  it. So the compiler creates a temporary object which is copied to t2 using copy 
    // constructor in the original program (The temporary object is passed as an argument to copy constructor). 
    // The reason for compiler error is, compiler created temporary objects cannot be bound to non-const references and 
    // the original program tries to do that. 
    // It doesn’t make sense to modify compiler created temporary objects as they can die any moment.
   
    Vector vec4 = 5;
   
    cout<<vec4<<endl;
    return 0;
}
