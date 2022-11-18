#include<iostream>
#include<queue>
#include<vector>
using namespace std;

/*
Round Robbin Algorithm
*/

class Process{
    int burst_time, arrival_time, completion_time, remExe_time, priority;
public:
    Process(){
        burst_time = 0;
        arrival_time = 0;
        completion_time = 0;
        remExe_time = 0;
    }

    void set_static_Process_details(int bt, int at){
        burst_time = bt;
        arrival_time = at;
        remExe_time = burst_time;
    }

    void process_Details(){
        cout<<priority<<"       "<<arrival_time<<"       "<<burst_time<<"        "<<completion_time<<endl;
    }

    bool executeProcess(){
        //False => process ends
        //True => process still running 

        remExe_time--;
        if(remExe_time == 0) return false; 
        else return true;
    }

    void set_completion_time(int ct){ completion_time = ct;}
    
    void set_priority(int p){ priority = p;}

    void reset_process(){ remExe_time = burst_time; completion_time = 0;}

    int get_burst_time(){return burst_time;}

    int get_remExe_time(){return remExe_time;}

    int get_arrival_time(){return arrival_time;}
    
    int get_priority(){return priority;}
    
    int get_completion_time(){return completion_time;}
};

void Round_Robbin_schedule_Processes(vector<Process>& pt, int Quantum){
    queue<int> readyQueue;
    int sz = pt.size();
    vector<bool> process_status(sz, false);
    bool last_process = false; 

    //Reset Process table
    for(int i = 0; i < pt.size(); i++){
        pt[i].reset_process();
    }

    int currProcess = 0, newProcess = 1, curr_time = 0, clock_time = 0/*for quantum checking*/, quantum = Quantum;
    do{
        if(clock_time < quantum){
            //execute current process
            //keep track of new process
            curr_time++;
            clock_time++;

            if(!pt[currProcess].executeProcess()){
                //Process finished
                //finish = true;
                process_status[currProcess] = true;
                clock_time = quantum;
                pt[currProcess].set_completion_time(curr_time);
            }

            if(pt[newProcess].get_arrival_time() == curr_time){
                //new Process arrived
                readyQueue.push(newProcess);
                newProcess++;
            }
        }

        else{
            //Prempt current process and swicth to next process in queue
            
            if(!process_status[currProcess])readyQueue.push(currProcess); //Push to queue if current process is still running
            if(!readyQueue.empty()){ 
                currProcess = readyQueue.front();
                readyQueue.pop();
                if(readyQueue.empty()) last_process = true;
            }
            clock_time = 0;
        }

    }while(!last_process || !process_status[currProcess]);
}

void Non_premptive_Priority_schedule_Processes(vector<Process>& pt){
    auto cmp = [](Process* p1, Process* p2){
        return p1->get_priority() > p2->get_priority(); 
    };

    priority_queue <Process*, vector<Process*>, decltype(cmp)> readyQueue(cmp);
    
    //Reset Process table
    for(int i = 0; i < pt.size(); i++){
        pt[i].reset_process();
    }

    int sz = pt.size();
    bool last_process = false; 

    int newProcess = 1, curr_time = 0;
    Process* currProcess = &pt[0];

    do{
            //execute current process
            //keep track of new process
            curr_time++;

            if(!currProcess->executeProcess()){
                //Current Process finished
                //process_status[currProcess] = true;
                currProcess->set_completion_time(curr_time);
                if(!readyQueue.empty()){
                    currProcess = readyQueue.top();
                    readyQueue.pop();
                    if(readyQueue.empty()) last_process = true;
                }
            }

            if((pt[newProcess].get_arrival_time() == curr_time) && newProcess != sz){
                //new Process arrived
                readyQueue.push(&pt[newProcess]);

                newProcess++;
            }

    } while(!last_process || currProcess->get_remExe_time());
}

double avg_waiting_time(vector<Process>& pt){
   
    double avg_waitingTime = 0;
    
    for(int i = 0; i < pt.size(); i++){
        int wt = pt[i].get_completion_time() - pt[i].get_arrival_time() - pt[i].get_burst_time();
        avg_waitingTime += wt;
    }
   
    return avg_waitingTime/pt.size();
}

double avg_turnAround_time(vector<Process>& pt){

    double avg_turnAroundTime = 0;
    
    for(int i = 0; i < pt.size(); i++){
        int tat = pt[i].get_completion_time() - pt[i].get_arrival_time();
        avg_turnAroundTime += tat;
    }
    
    return avg_turnAroundTime/pt.size();
}

void FCFS_schedule_process(vector<Process>& pt){

    //Reset processes
    for(auto &p : pt) p.reset_process();

    queue<int> readyQueue;
    int currProcess = 0;
    int newProcess = 1;
    int clock = pt[currProcess].get_arrival_time();
    vector<bool> processStatus(false);

    while(!processStatus[pt.size() - 1]){ //until last process execution is not completed => continue
        clock++; //advance in time

        if(currProcess != -1 && !pt[currProcess].executeProcess()){
            //current process execution is completed
            pt[currProcess].set_completion_time(clock);
            processStatus[currProcess] = true;
            
            if(readyQueue.empty()){
                currProcess = -1;
            }
            else{
                currProcess = readyQueue.front(); //Get ready for next process in queue
                readyQueue.pop();
            }
        }

        if(newProcess < pt.size() && clock == pt[newProcess].get_arrival_time()){
            if(currProcess != -1) readyQueue.push(newProcess); //currProcess is valid or in running state
            else currProcess = newProcess; //No process was running and cpu was idle waiting for new process to arrive
            newProcess++;
        }
    }
}

void SJF_Premptive_schedule_process(vector<Process>& pt){
    
    //Reset processes
    for(auto &p : pt) p.reset_process();

    auto cmp = [](Process* p1, Process* p2){
        return p1->get_remExe_time() > p2->get_remExe_time();
    };
    
    priority_queue<Process*, vector<Process*>, decltype(cmp)> prioQueue(cmp);
    int newProcess = 1;
    Process* currProcess = &pt[0];
    int clock = currProcess->get_arrival_time();
    
    while(newProcess < pt.size() || currProcess->get_remExe_time() != 0){ //Until last process is not executed completely
        clock++;

        if(!currProcess->executeProcess()){
            //Current process completed its execution
            
            currProcess->set_completion_time(clock);
            if(!prioQueue.empty()){
                currProcess = prioQueue.top();
                prioQueue.pop();
            }
        }

        if(newProcess < pt.size() && clock == pt[newProcess].get_arrival_time()){
            //new process has arrived

            if(currProcess->get_remExe_time() <= pt[newProcess].get_remExe_time()){
                //No need to prempt current process
                prioQueue.push(&pt[newProcess]);
            }
            else{
                //Current process must be prempted
                prioQueue.push(currProcess); //current process pushed to queue
                currProcess = &pt[newProcess]; //current process prempted and switched to new arrived process
            }
            newProcess++;
        }
    }
}

int main(){

    cout<<"----------Process Scheduling---------------"<<endl;

    vector<Process> processTable;

    int choice = 0;
    cout<<"MENU\n1. Add process\n2. Round Robbin Schedule processes\n3.Non Premptive Priority Schedule processes\n4. Display average turnAround time\n5. Display average waiting time\n6. Show process table\n7. Exit\n8. FCFS Schedule processes\n9. Premptive SJF Schedule processes"<<endl;
    

    while(true){
        cout<<"Enter choice: ";
        cin>>choice;
        switch(choice){
            case 1:{
                //Add process
                int at, bt, p;
                cout<<"Enter Priority, Arrival and Burst time: ";
                cin>>p>>at>>bt; //Arrival Burst time
                Process* newProcess = new Process;
                newProcess->set_static_Process_details(bt, at);
                newProcess->set_priority(p);
                processTable.emplace_back(*newProcess);
                break;
            }
            case 2:{
                //Round Robbin Schedule Processes
                int quantum = 0;
                cout<<"quantum: ";
                cin>>quantum;
                Round_Robbin_schedule_Processes(processTable, quantum);
                cout<<"Processes scheduled successfully!!"<<endl;
                break;
            }
            case 3:{
                //Premptive Priority Schedule Processes
                Non_premptive_Priority_schedule_Processes(processTable);
                cout<<"Processes scheduled successfully!!"<<endl;
                break;
            }
            case 4:{
                //average turnAround 
                cout<<endl;
                cout<<"Average TurnAround time: "<<avg_turnAround_time(processTable)<<endl;
                break;
            }
            case 5:{
                //average waiting time
                cout<<endl;
                cout<<"Average Waiting time: "<<avg_waiting_time(processTable)<<endl;
                break;
            }
            case 6:{
                //show process table
                cout<<endl;
                cout<<"Priority  Arrival  Burst   Completion (Time in ms)"<<endl;
                
                for(auto p : processTable){
                    p.process_Details();
                }
                break;
            }
            case 7:{
                //Exit
                return 0;
                break;
            }
            case 8:{
                //Exit
                FCFS_schedule_process(processTable);
                cout<<"Processes scheduled successfully!!"<<endl;
                break;
            }
            case 9:{
                //Exit
                SJF_Premptive_schedule_process(processTable);
                cout<<"Processes scheduled successfully!!"<<endl;
                break;
            }
        }   
    }
    return 0;
}

/*

----------Process Scheduling---------------
MENU
1. Add process
2. Round Robbin Schedule processes
3. Premptive Priority Schedule processes
4. Display average turnAround time
5. Display average waiting time
6. Show process table
7. Exit
Enter choice: 1
Enter Priority, Arrival and Burst time: 2 0 11
Enter choice: 1
Enter Priority, Arrival and Burst time: 1 2 10
Enter choice: 1
Enter Priority, Arrival and Burst time: 0 5 28
Enter choice: 1
Enter Priority, Arrival and Burst time: 4 9 16
Enter choice: 1
Enter Priority, Arrival and Burst time: 3 12 2
Enter choice: 6

Priority  Arrival  Burst   Completion (Time in ms)
2       0       11        0
1       2       10        0
0       5       28        0
4       9       16        0
3       12       2        0
Enter choice: 3
Processes scheduled successfully!!
Enter choice: 6

Priority  Arrival  Burst   Completion (Time in ms)
2       0       11        49
1       2       10        40
0       5       28        33
4       9       16        67
3       12       2        51
Enter choice: 2
quantum: 2
Processes scheduled successfully!!
Enter choice: 6

Priority  Arrival  Burst   Completion (Time in ms)
2       0       11        37
1       2       10        32
0       5       28        67
4       9       16        55
3       12       2        20
Enter choice: 4

Average TurnAround time: 36.6
Enter choice: 5

Average Waiting time: 23.2
Enter choice: 7

*/