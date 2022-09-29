class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        std::vector<ListNode*> store; 
        int node_count = 0  ; 
        while(head)
        {
            node_count++; 
            store.push_back(head) ;
            head = head->next; 
        }
        if(node_count == 1 or node_count == 0 )
        {
            head = nullptr; 
            return head; 
        }
        if(node_count == n )
        {
            return store[1];
        }
        if(n == 1)
        {
           store[node_count-n-1]->next = nullptr; 
            return store.front();
        }
        
        store[node_count-n-1] -> next = store[node_count-n+1]; 
        store[node_count-n] ->next = nullptr; 
        delete(store[node_count-n]) ; 
        return store.front();
    }
};
