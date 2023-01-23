#include<iostream> 
using namespace std; 
int solve(int N , int K)
{
    int burnt_wax = N ;
    int unburnt_candles = 0 ;
    while(true)
    {
        
        N += unburnt_candles ;
        burnt_wax += unburnt_candles ;
        if(burnt_wax < K)
        {
            break;
        }
        unburnt_candles = burnt_wax/K ;
        burnt_wax %= K ;
    }
    return N ;

}
int main()
{
    int N , K ; 
    cin>>N>>K ; 
    cout<<solve(N,K)<<endl;
    return 0 ;
}
