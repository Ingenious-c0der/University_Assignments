#include<iostream> 
#include<vector> 
class Process {
    int id; 
    bool active = true; 
    Process(int id)
    {
        this->id = id; 
    }

    bool checkCircuit(std::vector<int> message_circuit)
    {
        //std::cout<<"check  circuit called by" << id <<std::endl ;
        for(auto p : message_circuit)
        {

            if(p == id)
            {
                 std::cout<<"Circuit Complete" << id <<std::endl ;
                return true; 
            }
        }
        return false; 


    }
    friend class Ring; 

}; 



class Ring {
     int processCount = 0 ;
     std::vector<Process> ring; 
        public: 
     Ring(int totalProcesses)
     {
        processCount = totalProcesses ;
        for(int i = 0 ; i < totalProcesses ; i++)
            ring.push_back(Process(i)) ; 
     }


    void startElection()
    {       
        int k ,n ,s ; 
        std::cout<< "Enter the total number of nodes which have failed : "; 
        std::cin >> n ;
        for(int i = 0 ; i< n ; i++ )
        {
            std::cout<< "Enter the process number which has failed :"; 
            std::cin >>k ;
            ring[k].active  = false; 
        }
        std::cout<< "Enter the starting node : "; 
        std::cin>> s ;
        electionProcessing(ring[s]) ; 

    }

    void electionProcessing(Process p)
    {
        std::vector<int> msg_circuit ;
        int index = p.id; 
        bool done = false; 
        while(!done)
        {
            if(ring[index].checkCircuit(msg_circuit)){
                int co_od = 0 ; 
                for(int k: msg_circuit)
                {
                    if(k> co_od)
                        co_od = k ; 
                }
                std::cout<<"Process "<< co_od<< " is the new co od"<<std::endl; 
                done = true; 
            } 
            else{
            int prev_index= index; 
            msg_circuit.push_back(index);
            index = (index+1)%processCount; ;
            while(!ring[index].active)
            {
                index = (index+1 )%processCount; 
            }
             std::cout<<"Process "<< prev_index << " sent message to Process "<< index<<std::endl; 
                
            };
         

        }
        std::cout<<"Election ends"<<std::endl; 

    }



}; 

int main()
{
        int n ;
        std::cout<< "Enter the size of the ring : " ;
        std::cin>> n ;
        Ring r(n) ;
        r.startElection(); 
}