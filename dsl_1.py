"""In second year computer engineering class, group A student’s play cricket, group B students play badminton
 and group C students play football.  Write a Python program using functions to compute following: -  
 a) List of students who play both cricket and badminton  
 b) List of students who play either cricket or badminton but not both  
 c) Number of students who play neither cricket nor badminton 
 d) Number of students who play cricket and football but not badminton.
  (Note- While realizing the group, duplicate entries should be avoided, Do not use SET built-in functions)"""
class  Set():
    def __init__(self,r_list):
        self.list=r_list
    def  union(self,list)->list:
        result= []
        net = self.list+list.list
        
        for i in range(list_length(net)):
            if not membership(net[i],result):
                result.append(net[i])
        return result
    def intersection(self,list)->list:
        result = []
        for i in range(list_length(self.list)):
            for j in range(list_length(list.list)):
                if self.list[i]==list.list[j] and not membership(self.list[i],result): 
                    result.append(self.list[i])
                    break
        return result
    def display_set(P_list):
        
        return set(list(map(int,P_list)))


def list_length(list):
    """Returns the length of the list"""
    i=0
    while True:
        try:
            x=list[i]
            i+=1

        except:
            break
    return i 

def membership(element,list):
    """Returns True if the list contains the element"""
    i=0
    while True:
        try :
            if list[i]==element:
                
                return True
            i+=1
        except:
            break
    return False



    

def input_rollnos(Number :int)->Set:
    """This function is used to create roll no.lists for groups"""
    result=[]
    for i in range(Number):       
        roll_no =input(f"Enter the roll no for student number {i+1} :")            
        if roll_no=="":
            print("Invalid roll no")
            roll_no = input(f"Enter the roll no for student number {i+1} :")
            result.append(roll_no)
        
        if  not membership(roll_no,result):
            result.append(roll_no)
       
        else:
            while membership(roll_no,result) :
                print(f"Roll no {roll_no} already exists!")
                roll_no = input(f"Enter the roll no for student number {i+1} :")

            result.append(roll_no)

    return Set(result)


if __name__ == "__main__ ":
    Total_students=int(input("Enter the total number of students in class :"))

    A_students =int(input("Enter the number of students who play cricket :"))
    A_rollnos=input_rollnos(A_students)

    B_students = int(input("Enter the number of students who play badminton :"))
    B_rollnos = input_rollnos(B_students)

    C_students = int(input("Enter the number of students who play football :"))
    C_rollnos= input_rollnos(C_students)

    while True:
        user_input = int(input("""\n MENU \n 
        Select one of the options given below \n
        1. List of students who play both cricket and badminton \n 
        2. List of students who play either cricket or badminton but not both \n 
        3. Number of students who play neither cricket nor badminton \n 
        4. Number of students who play cricket and football but not badminton \n 
        5. Exit \n :"""))
        if user_input==1:
            print(f"Case 1 answer : {Set.display_set(A_rollnos.intersection(B_rollnos))}"),
        elif user_input==2:
            print(f"Case 2 answer is : {Set.display_set([A_rollnos.union(B_rollnos)[i] for i in range(list_length(A_rollnos.union(B_rollnos))) if not membership(A_rollnos.union(B_rollnos)[i],A_rollnos.intersection(B_rollnos)) ])}")
        elif user_input==3:
            print(f"Case 3 answer is : {Total_students - list_length(A_rollnos.union(B_rollnos))}")
            print(Set.display_set([str(i) for i in range(1,Total_students+1)if  not membership(str(i),A_rollnos.union(B_rollnos))])) 
        elif user_input==4:
            print(f"Case 4 answer is: {list_length([A_rollnos.intersection(C_rollnos)[i] for i in range(list_length(A_rollnos.intersection(C_rollnos)))if not membership(i,B_rollnos.list)])},{Set.display_set([A_rollnos.intersection(C_rollnos)[i] for i in range(list_length(A_rollnos.intersection(C_rollnos)))if not membership(i,B_rollnos.list)])}")  
        else:  
            break




