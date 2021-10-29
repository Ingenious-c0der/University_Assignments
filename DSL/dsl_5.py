class Student:
    def __init__(self,arr)->None:
        self.arr = arr


    def insertion_sort(self)->list:
        for i in range(1,len(self.arr)):
            n = self.arr[i]
            k = i-1
            while k>=0 and n<self.arr[k]:
                self.arr[k+1] = self.arr[k]
                k-=1
            self.arr[k+1] = n 
        return self.arr

    def shell_sort(self)->list:
        gap =len(self.arr)//2
        while gap>0:
    
          for i in range(len(self.arr)):
            try:
                if self.arr[i]>self.arr[i+gap]:
                        temp = self.arr[i]
                        self.arr[i]=self.arr[i+gap]
                        self.arr[i+gap]=temp
                k = i
                while k - gap > -1:
                    if self.arr[k - gap] > self.arr[k]:
                        self.arr[k-gap],self.arr[k] = self.arr[k],self.arr[k-gap]
                    k -= 1
                        
                        
                else:
                        pass
            except:
                pass
                
          gap//=2
        return self.arr



if __name__=="__main__":
    n = int(input("Enter the total number of students "))
    percentage_list  = [float(input(f"Enter the percentage for student {i+1} : ")) for i in range(n)]
    S_object = Student(percentage_list)
    insertion_sorted = S_object.insertion_sort()
    shell_sorted = S_object.shell_sort()
    print(f"The top five scores found by shell sort are : {shell_sorted[-5:]}")
    print(f"The top five scores found by insertion sort are : {insertion_sorted[-5:]}")


        
