def sieve(n):
    l = [1 for i in range(n+1)]
    l[0] = 0 ;l[1]=0;
    for i in range(2,int(n/2)+1):
        if l[i]==1:
            for j in range(2,int(n/i)+1):
                        l[i*j]=0
             
    return [i for i in range(n+1) if l[i]==1]
