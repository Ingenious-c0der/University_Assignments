class Student :
    Student_list =  [ ]
    def __init__(self,roll_no):
        self.roll_no  = roll_no
        Student.Student_list.append(roll_no)



    def partition(low,high,array):
        pivot_index = low
        pivot = array[pivot_index]
        
        while low<high:
            while  low<len(array) and array[low]<=pivot :
                low+=1
            while array[high]>pivot :
                high-=1
            if low<high:
                array[low],array[high]= array[high],array[low]
            
        array[high], array[pivot_index] = array[pivot_index], array[high]

        return high

    def quick_sort(low,high,array):
        if high>low:
            mid = Student.partition(low,high,array)
            Student.quick_sort(low,mid-1,array)
            Student.quick_sort(mid+1,high,array)
        else:
            return 0 






if __name__ == "__main__":
    n = int(input("Enter the number of students : "))
    for i in range(n):
        r = int(input(f"The roll_no of student of student {i+1} : "))
        student = Student(r)

    while True:
        choice = int(input("****MENU****\n1.Search roll number with Quick Sort"))
        if choice==1:
            print(f"The sorted string is {Student.quick_sort(0,n-1,Student.Student_list)}")
        
