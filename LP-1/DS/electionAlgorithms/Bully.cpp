#include<iostream> 
#include<vector> 
class ProcessNode{
    
    bool active = true ;
    int priority = 0 ; 
    ProcessNode(int priority)
    {
        this->priority = priority ;
    }
    ProcessNode(){}
    friend class Bully; 
}; 

class Bully { 
    int processCount; 
    int co_od_index = 0 ; 
    std::vector<ProcessNode> processes; 
    public:
    Bully(int processCount)
    {
        this->processCount = processCount;
        co_od_index = processCount - 1 ; 
        for(int i = 0 ; i < processCount ; i++)
        {
            processes.push_back(ProcessNode(i+1)) ;
        }
    }   
    void startElection()
    {
        int wbn = 0;  
        int total = 0 ;
        int n ; 
        std::cout << "Enter the total number of process Nodes which have failed  : " ;
        std::cin>>total ;
        for(int i = 0 ; i< total ; i++)
        {
            std::cout<< "Enter the dead process number " <<i+1 <<" : "; 
            std::cin>> n ; 
            processes[n-1].active = false ;
        }
        std::cout << "Enter the node which detected the failure : ";
        std::cin >> wbn ;
        electionProcesing(processes[wbn-1]); 
    }

    void electionProcesing(ProcessNode whistleBlowerNode){
        std::vector<ProcessNode> replyVector; 
        std::vector<ProcessNode> activeVector; 
        for(int i = 0 ; i< processCount ; i++)
        {
            if ( processes[i].priority > whistleBlowerNode.priority)
            {
                std::cout<< "Process Node " << whistleBlowerNode.priority << " sent election message to "<< processes[i].priority <<std::endl; 
                replyVector.push_back(processes[i]); 
            }
        }
        for(auto i : replyVector)
        {   if(i.active)
           { 
            std::cout<< "Process Node "<< i.priority << " Passes Ok to Process Node " << whistleBlowerNode.priority << std::endl ; 
            activeVector.push_back(i) ;
          }
        }
        
        if(activeVector.size() !=0 )
        {
            electionProcesing(processes[activeVector[0].priority - 1 ]); 
        }
        else
        {   
            std::cout<< "Process Node "<< whistleBlowerNode.priority << " has become the new Co ordinator !"<<std::endl; 

            for(auto x : processes)
            {
                if(x.active && x.priority != whistleBlowerNode.priority)
                std::cout<< "Process Node " << whistleBlowerNode.priority << " passes Coordinator message to "<< x.priority <<std::endl; 
            }
            std::cout<<"Election Ends ! "<<std::endl; 
        }
    }
} ;


int main()
{
    int n = 0 ; 
std::cout<<"Enter the total number of processes :";
std::cin >> n ; 
  Bully b(n) ;
  b.startElection() ; 

}