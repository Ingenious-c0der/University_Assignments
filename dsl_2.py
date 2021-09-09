"""Write a Python program to compute following operations on String:  

a) To display word with the longest length  <->

b) To determines the frequency of occurrence of particular character in the string  <->

c) To check whether given string is palindrome or not  <->

d) To display index of first appearance of the substring  <->

e) To count the occurrences of each word in a given string  <->

 """
class Mystring():

    def __init__(self,sentence:list)->None:
        """  Class Constructor  
            Gives two object attributes 1.sentence -> Passed list value (sentence)
                                        2.main_list -> list of all the words in the sentence"""
        self.sentence = sentence
        main_list=  []
        word_list = []
        self.sentence.append("")
        for i in range(len(self.sentence)):
            if self.sentence[i]!="":
                word_list.append(self.sentence[i])
            else:
                word = "".join(word_list)
                main_list.append(word)
                word_list = []

        self.main_list = main_list
    

    def longest_word(self)->str:
        """Returns the longest word in the sentence/string"""
      
        lengths = [len(self.main_list[i]) for i in range(len(self.main_list))]
        return self.main_list[lengths.index(max(lengths))]

    def frequency_character(self,a:str)->int:
        """Returns the number of times the passed letter was repeated"""
        return len([self.sentence[i] for i in range(len(self.sentence)) if self.sentence[i]==a])


    def palindromes(self)->list:
        """Returns list of palindromes from the given string/sentence"""
        
        palindromes = []
        for i in range(len(self.main_list)):
            rev_lst = (list(self.main_list[i]))[::-1]
            if all([list(self.main_list[i]) == rev_lst,self.main_list[i]!="",len(self.main_list[i])!=1,len(self.main_list)!=2]):
                palindromes.append(self.main_list[i])
        return palindromes if (len(palindromes)!=0) else False


    def occurence_indices(self)->list:
        """Returns the list of words with their starting indices 
        Output format: [(indice,'word')]"""
        occurences = []
        self.sentence.insert(0,"")
       
        for i in range(len(self.sentence)):
            if self.sentence[i] == "":
                
                test_list = []
                x = i+1
                try:
                    while self.sentence[x]!="":
                       
                        test_list.append(self.sentence[x])
                        x+=1

                    y = "".join(test_list)
                    if y!="":
                        occurences.append((i,y))
                except:
                    break
        self.sentence.pop(0)

        return occurences


    def word_count(self)->list:
        """Returns the list of the words with the amount of times they occurred in the sentence
            Example Output : [('Word':str,Number of times it occured:int)]"""
  
        r_list = []
        for i in range(len(self.main_list)):
            intermidiate = 1 
            for j in range(len(self.main_list)):
                if self.main_list[i]==self.main_list[j] and i!=j  :
                    intermidiate+=1
           
            if  not Mystring.ismember((self.main_list[i],intermidiate),r_list) and self.main_list[i]!="":
         
                r_list.append((self.main_list[i],intermidiate))

        return r_list

    def substring(self,sub:str)->tuple:
        """Returns the first occurence index of the given substring in the string
           Example Output : ("substring",index of occurence)
           Returns False if given substring is not found"""    
        for i in range(len(self.sentence)):
            c = 0 
            for j in range(len(sub)):
                try:
                    if self.sentence[i+j] == sub[j] :
                            c+=1
                except:
                    break
                
            if c == len(sub):
                    return (sub,i)

           
        return False

    @staticmethod
    def len(list:list)->int:
        """Returns the length of the list"""
        i=0
        while True:
            try:
                x = list[i]
                i+=1
            except:
                break

        return i

    @staticmethod
    def ismember(element,list:list)->bool:
        """Returns True if element is in the list , else returns False"""
        for i in range(len(list)):
            if element==list[i]:
                return True
        return False

            
            
if __name__ == "__main__":

    n = int(input("Enter the length of the character array : "))
    l =[input() for i in range(n)]

    object= Mystring(l)
    while (True):
        print("""***MENU*** \n1.Display word on longest length? \n2.Determine frequency of a character in the sentence
3.Find the palindromes\n4.Find the index of first appearance of all the words. \n5.Find the number of times the word was repeated\n6.Substring\n7.Exit""")
        n = int(input("Enter your choice : "))
        if n == 1:
            print(object.longest_word())

        elif n == 2:
            char=  input("Enter the character whose frequency is to be check : ")
            print(f"The character {char} appeared {object.frequency_character(char)} times")

        elif n == 3:
            if object.palindromes():
                for i in range(len(object.palindromes())):
                    print(f"{object.palindromes()[i]} is a palindrome!" )
            else:
                print("No palindromes in the given sentence")
            
        elif n == 4:
            for i in range(len(object.occurence_indices())):
                print(f"The word {object.occurence_indices()[i][1]} appeared first at index {object.occurence_indices()[i][0]}")
     

        elif n == 5:
            for i in range(len(object.word_count())):
                print(f"The word {object.word_count()[i][0]} appeared {object.word_count()[i][1]} times!")

        elif n == 6:
            substring = input("enter the substring : ")
            print( f"The substring {object.substring(substring)[0]} appeared first at {object.substring(substring)[1]} index" if object.substring(substring) else "No such substring found")

        else :
            break
            
