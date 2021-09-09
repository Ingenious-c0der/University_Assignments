#include <bits/stdc++.h>
using namespace std;

int main()
{  
int c;
string sys_choice;
    string choice;
    bool exit = true;
    while (exit){
        int *foo = new int;
    cout<<"Enter your choice\n1.Rock \n2.Paper\n3.Scissors\n4.Exit"<<endl;
    cin>> c;
    switch(c){
        case 1:
         choice = "Rock";
         break;
        case 2:
         choice = "Paper"; 
         break;
        case 3: 
         choice = "Scissors";
         break;
        case 4:
         exit = false;
         break;

          
    }
 if((*foo)%6==0)
 {
     sys_choice = "Rock";
 }
 else if((*foo)%5==0)
 {
     sys_choice = "Scissors";
 }
 else
 {
   sys_choice = "Paper";
 }
if (sys_choice== choice)
{
    cout<<"Tied"<<endl;
}
else if ((sys_choice=="Scissors" and choice=="Rock") or (sys_choice=="Rock" and choice=="Paper" or (sys_choice=="Paper" and choice=="Scissors")))
{
    cout<<"You Win!"<<endl;
}
else
{
    cout<<"You lose"<<endl;
}
    }

    
    return 0;
}
