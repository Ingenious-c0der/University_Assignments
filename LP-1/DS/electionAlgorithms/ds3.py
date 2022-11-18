class election:
    def message(self,p,n,status,co):
        for i in range(p+1,n):
            if status[i]!=0:
                if i!=co:
                    print("Election Message sent from {} to {}".format(p,i))
                    print("{} responded 'OK'".format(i))
        for i in range(p+1,n):
            if status[i]!=0 and i!=co:
                return i


    def bully(self):
        status=[]
        print("Enter Number of Processes")
        n=int(input())
        for i in range(n):
            print("Is {} process working or dead(1/0)".format(i))
            status.append(int(input()))
        print("Who is co-ordinator now")
        co=int(input())
        print("Coordinator Not Responding")
        print("Who Initiated Election?")
        p=int(input())
        m=0
        for i in range(n-1,-1,-1):
            if status[i]==1 and i!=co:
                m=i
                break
        q1=self.message(p,n,status,co)
        #print("Coordinator now {}".format(q1))
        while q1!=m:
            q1=self.message(q1,n,status,co)
            print("Coordinator now {}".format(q1))
        print("Final Coordinator is {}".format(q1))




q=election()
q.bully()