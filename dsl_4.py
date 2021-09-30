class Student:
    program_list = []
    def __init__(self,roll_no)->None:
        self.roll_no = roll_no
        Student.program_list.append(self.roll_no)

    def linear_search(roll_no :int)->int:
        """Performs linear search on the class program list and returns the index of the needed element, Complexity O(n)"""
        for i in range(len(Student.program_list)): #2 conditions are checked at every index one is array[i]==element and other is if i<n
            if Student.program_list[i]==roll_no:
                return i
        return False

    def sentinel_search(roll_no:int)->int:
        """Performs Sentinel search on the class program list and returns the index of the needed element, Complexity O(n)"""
        Student.program_list.append(roll_no)
        i=0
        while Student.program_list[i]!=roll_no: #only 1 condition checked at each index
            i+=1
        Student.program_list.pop()
        if i==len(Student.program_list):
            return False
        else:
            return i
    
    def binary_search(roll_no:int)->int:
        """Performs Binary search on the class program list and returns the index of the needed element, Complexity O(logn)"""
        left = 0
        right = len(Student.program_list)
        Student.program_list.sort()
        mid = int((left+right)/2)
        while Student.program_list[mid]!=roll_no:
            
            if left>right or right==left+1:
                return False

            if Student.program_list[mid]<roll_no:
                left=mid+1
            else :
                right = mid-1
            mid = int((left+right)/2)
        return mid

    def Fibonacci(n:int)->int:
        if n < 0:
            print("Incorrect input")

        elif n == 0:
            return 0

        elif n == 1 or n == 2:
            return 1
    
        else:
            return Student.Fibonacci(n-1) + Student.Fibonacci(n-2)


    def fibonacci_search(roll_no:int)->int:
        """Performs Fibonacci search on the class program list and returns the index of the needed element, Complexity O(logn)"""
        Student.program_list.sort()
        work_list = Student.program_list
        n = len(work_list)
        for i in range(n+3):
            if Student.Fibonacci(i)>=n:
                x = i
                fibo = Student.Fibonacci(x)
                break
        
  
        fm = fibo 
        fm1 = Student.Fibonacci(x-1)
        fm2 = fm-fm1
        offset = -1
        
        while fm> 1 :
            i = min(offset+fm2, len(work_list)-1)

            if work_list[i]==roll_no:
                return i

            if work_list[i]>roll_no:

                fm = fm2
                fm1 = fm1-fm2
                fm2 = fm-fm1

            if work_list[i]<roll_no:
                
                fm=fm1
                fm1 = fm2
                fm2 = fm-fm1
                offset = i
 
        return -1




        

if __name__=="__main__":
    n = int(input("Enter the total number of students : "))
    for i in range(n):
        j = int(input(f"Enter the roll_no of student {i+1} : "))
        student = Student(j)
    while True:


        choice = int(input("""******MENU*****\n Enter the choice\n1.Search using linear search\n2.Search using sentinel search\n3.Search using binary search\n4.Search using Fibonacci Search\n5.Exit\n"""))
        if choice==1:
            m = int(input("Enter the roll_no to be found : "))
            return_value = Student.linear_search(m)
            if return_value:
                print(f"The element {m} was found at index {Student.linear_search(m)} in the Student list.")
            else:
                print("Match not found")
        elif choice==2:
            m = int(input("Enter the roll_no to be found : "))
            return_value = Student.sentinel_search(m)
            if return_value:
                print(f"The element {m} was found at index {Student.sentinel_search(m)} in the Student list.")
            else:
                print("Match not found")
    
        elif choice==3:
            m = int(input("Enter the roll_no to be found : "))
            return_value = Student.binary_search(m)
            if return_value:
                print(f"The element {m} was found at index {Student.binary_search(m)} in the Student list.")
            else:
                print("Match not found")

        elif choice==4:
            m = int(input("Enter the roll_no to be found : "))
            return_value = Student.fibonacci_search(m)
            if return_value:
                print(f"The element {m} was found at index {Student.fibonacci_search(m) } in the Student list.")
            else:
                print("Match not found")


        else:
            break
