#include<iostream>
#include<cstdlib>

using namespace std;
class Guesser{
    int balance;
    string name;
  
    public:
    Guesser();
    friend void get_info(Guesser&);
    friend void display_info(Guesser&);
    friend void change_amount(Guesser&,int );
    friend void run_game(Guesser& G);
};
Guesser::Guesser(){
    name = "Anonymous";
    balance = 10000;
}
void display_info(Guesser & G){
    cout<<"The guesser's name is "<<G.name<<endl;
    cout<<"The current balance is "<<G.balance<<endl;
}
void get_info(Guesser &G){
    cout<< "Enter your name"<<endl;
    cin>>G.name;
    cout<<"Your balance is set to 10k by default! , happy Guessing"<<endl;

}
void change_amount(Guesser &G,int amount){
    G.balance = G.balance + amount;
}
void run_game(Guesser & G){
    int amount;int guess;
    int dice = rand()%10+1;
    do{
        cout<<"Enter your betting amount!"<<endl;
        cin>>amount;}
    while (amount>G.balance);

    
    cout<<"Enter your guess!!"<<endl;
    cin>>guess;
    if(dice==guess){
        cout<<"your guess was correct!!,you have won additional "<<amount<<endl;
        change_amount(G,amount);

    }else{
        cout<<"Oops your guess wasn't correct,the number was " <<dice<< " ,you lose "<<amount<<endl;
        change_amount(G,-amount);
    }
}
int main(){
    bool exit = true;
    Guesser g1;
    while(exit){
        int choice;
        cout<<"***Menu*** \n1.Start\n2.Guess\n3.Check Info\n4.Exit"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                    get_info(g1);//g1.get_info doesn't work because its not a member funciton of Guesser class
                    break;
            case 2:
                    run_game(g1);
                    break;
            case 3:
                    display_info(g1);
                    break;
            case 4:
                    cout<<"Thankyou for playing"<<endl;
                    exit = false;
                    break;
        }
    }
}
