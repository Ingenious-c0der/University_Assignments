class Student :
    Student_list =  [ ]
    def __init__(self,roll_no):
        self.roll_no  = roll_no
        Student.Student_list.append(roll_no)



    def QuickSort(lst,start,end):
        i = start 
        j = end 
        if start<end:
            pivot = lst[i]
            while i<j:
                while i<len(lst) and lst[i]<=pivot:
                    i+=1
                while  lst[j]>pivot:
                    j-=1
                if j>i:
                    lst[i],lst[j] = lst[j],lst[i]

            lst[start],lst[j] = lst[j],lst[start]
            QuickSort(lst,start,j-1)
            QuickSort(lst,j+1,end)






if __name__ == "__main__":
    n = int(input("Enter the number of students : "))
    for i in range(n):
        r = float(input(f"The percentage of student  {i+1} : "))
        student = Student(r)

    while True:
        choice = int(input("****MENU****\n1.Sort with Quick Sort"))
        if choice==1:
            print(f"The sorted list of percentages is {Student.QuickSort(Student.Student_list,0,n-1)}")
        
