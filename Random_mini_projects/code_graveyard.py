#this file contains large amount of graveyard code. Don't expect to find anything proper here , its just a code dump of me solving differene competitve programming questions.









# year = 2018
# month_list = [31,28,31,30,31,30,31,31,30,31,30,31]
# for month in range(len(month_list)):
#       for day in range(month_list[month]):
#           print(f"{day+1} {month+1} {year}")



#assume cobweb is a group of concentric n sided polygons
#the outermost cobweb is a n sided polygon with length of each side 2n+1 units
#the distance between 2  consecutive cobweb polygons is n 
#find the number of triangles in the cobweb given n

# import math
# def number_of_triangles(number_of_sides_of_polygon):
#     #first we need to find the length of perpendicular from the side of the outermost polygon to the centre
#     side_length = 2*number_of_sides_of_polygon+1
#     distance_between_2_polygons = number_of_sides_of_polygon
#     perpendicular_dist = (side_length/2)/(math.tan(math.radians(360/(number_of_sides_of_polygon*2))))
#     print(perpendicular_dist)
    
#     max_polygons = 1+math.floor(perpendicular_dist/distance_between_2_polygons)
#     print(max_polygons)
#     number_of_triangles = number_of_sides_of_polygon*max_polygons
#     return number_of_triangles


# print(number_of_triangles(10))

#find the least number pair which when raised to each other (exponents) has a 8- digit difference 

# for x in range(10000):
#     if x**(x+1)-(x+1)**x>9999999:
#         print(x,x+1)
#         break


#how many prime numbers are there between 700 and 1000
# def primecheck(n)->bool:
#     if n==0 or n==1:
#         return False
#     for i in  range(2,int(n/2)):
#         if n%i==0 :
#             return False


#     return True
            


# def primes( n1,n2)->int:
  
#     primes=[i for i in range(n1,n2) if primecheck(i)]
#     return len(primes)
# primes(5976,955746)


# print(primes(700,1000))

#the 3x+1 problem 

# def solve(n):
#     list=[]
#     while True:
#         if n%2 ==0:
#             n=n/2
#         else:
#             n= 3*n+1
#         if n==4:
#             break
#         list.append(n)
#     return max(list)

# print(solve(27))

# def primecheck(n)->bool:
#     if n==0 or n==1 :
#         return False
#     for i in  range(2,int(n)):
#         if n%i==0:
#             return False


#     return True
            


# def twin_primes_probability(n1,n2)->int:

  
#     twin_primes=[(i,i+2) for i in range(n1,n2) if primecheck(i) and primecheck(i+2)]
#     print((twin_primes))
#     probability = (len(twin_primes)*2)/(((n2-n1)*(n2-n1-1))/2)
#     return probability

# print(float(twin_primes_probability(0,3000)))
#This is the given list = [23,31,44,55,43,12,12,3]

#find the GCD of the given numbers in the list such that it should not exceed n and should be the GCD of  maximum possible numbers in the list.(you need to find gcd of all sublists for that).Take n=1300
# l  = [4800,96000,1200,12200,2000,38000,2880]

# def test_function(l):
#     def find_gcd(x, y):  
#         while(y):
#             x, y = y, x % y
     
#         return x
#     try:
#         num1 = l[0]
#         num2 = l[1]
#     except:
#         return None
#     gcd = find_gcd(num1, num2)
#     for i in range(2, len(l)):
#         gcd = find_gcd(gcd, l[i])
     
#     return gcd
# def driver_function(limit :int,list : l):
#     lists = [[]]
#     gcd_list=[]
#     for i in range(len(l) + 1):
#         for j in range(i):
#             lists.append(l[j: i])
   
#     for i in lists:
#         gcd_list.append((test_function(i),len(i)))

#     gcd_list= [i for i in gcd_list if gcd_list[gcd_list.index(i)][0]!=None]
#     gcd_set = set(gcd_list)
#     gcd_list = [i for i in gcd_set]
#     gcd_list.sort()
#     limited_list =[i for i in gcd_list if gcd_list[gcd_list.index(i)][0]<limit ]
#     return gcd_list
# print(driver_function(1300,l))
# import random 
# l = [2,7,5,13,9,8]
# o = []

# for i in  range(10000):
#     random.shuffle(l)
#     sum = 0 
#     for i in l:
#         l[i]-l[i+1] +=sum

#     if sum%2!=0:
#         print(l)
#         break


# print(o)

#all sublists of l 
# 1+l[0],2+l[1].....n+l[n-1]
# k = [i+l[i-1] for i in range(1,len(l))]
# print(k)
# import random
# l = [random.choice(["yes","no"]) for i in range(1000000)]


# print("yes" if l.count("yes")>l.count("no") else "no")







#binary keyboard
# string = "Paragraph"
# sep_list=[i for i in ["".join([bin(ord(i))[2:] for i in string])][0]]
# print(abs((sep_list).count("1")-sep_list.count("0")))

#How many Sundays were between the dates 19th august 2021 and 19th august 2051. Such that the date on which it is Sunday is odd. (example - 15th august 2021 Sunday) 
# from datetime import date, timedelta
# dstart = date(2021,8,19)
# dend = date(2051,8,19)
# days = [dstart + timedelta(days=x) for x in range((dend-dstart).days + 1) if (dstart + timedelta(days=x)).weekday() == 6]
# day_tuple=[tuple(i.timetuple()) for i in days]
# odd_sundays = [i for i in day_tuple if i[2]%2!=0]
# print(odd_sundays)
# print(len(odd_sundays))


# list1=[1,2,4,5,8]
# list2 = [3,5,7,8]

# result=[i  for i in list1 if i in list2]
# print(result)   



# import io,os,time,sys
# def fast_io():
    
#     # Reinitialize the Input function
#     # to take input from the Byte Like 
#     # objects
#     input = io.BytesIO(os.read(0, \
#          os.fstat(0).st_size)).readline
  
#     # Fast Input / Output
#     start = time.perf_counter()
  
#     # Taking input as string 
#     s = input().decode()
      
#       # Stores the end time
#     end = time.perf_counter()
  
#     # Print the time taken
#     print("\nTime taken in Fast I / O:", \
#                       end - start)
#     print(input)


# fast_io()

# def fast_out():
  
#     start = time.perf_counter()
#     # Output Integer
#     n = 5
#     sys.stdout.write(str(n)+"\n")
  
#     # Output String
#     s = "GeeksforGeeks\n"
#     sys.stdout.write(s)
  
#     # Output Array
#     arr = [1, 2, 3, 4]
#     sys.stdout.write(
#         " ".join(map(str, arr)) + "\n"
#     )
          
#     # Stores the end time
#     end = time.perf_counter()
      
#     # Print the time taken
#     print("\nTime taken in Fast Output:", \
#                       end - start)


# fast_out()



# from sys import stdout,stdin
# print("Enter the string")
# string = (stdin.readline())

# stdout.write(len([i for i in string if i in {"a","e","i","o","u"}]))
# from sys import stdin

# def primecheck(n)->bool:
#     if n==0 or n==1 :
#         return False
#     for i in  range(2,int(n)):
#         if n%i==0:
#             return False


#     return True

# x = stdin.readline()
# l=[i for i in (bin(x)[2:])]
# print(abs(l.count(1)-l.count(0)))























# def first_appear(string, word):
#         for i in range(len(string) - len(word)+1):
#             if string[i:i+len(word)] == word:
#                 return i
#         return 'Not Found'

# print(first_appear("rocket go brrrrr","rrrrr"))















# import random
# l=[1,2,3,4]
# print(random.choice(l))
# """
#    Problem Statement::
#         Write a Python program to compute following operations on String:
#             a)	To display word with the longest length
#             b)	To determines the frequency of occurrence of particular character in the string
#             c)	To check whether given string is palindrome or not
#             d)	To display index of first appearance of the substring
#             e)	To count the occurrences of each word in a given string

# """
# class string:
#     def frequency(self,s,char):
#         cnt=0
#         for i in s:
#             if(i==char):
#                 cnt+=1
#         return cnt
#     def substr(self,str):
#         w = ""
#         all = []
#         d=[]
#         str = str + " "
#         for i in range(0,len(str)):
#             if (str[i] != ' '):
#                 w = w + str[i]
#             else:
#                 all.append(w)
#                 w = ""
#         for i in all:
#             if(i not in d):
#                 d.append(i)
#             else:
#                 continue
#         for j in d:
#             cnt=0
#             for k in all:
#                 if(j==k):
#                     cnt+=1
#             print("the occurence of",j,"is:",cnt)
#     def index(self,s,sub):
#         l=len(sub)
#         for i in range(len(s)):
#             if(s[i:i+l]==sub):
#                 return i
#     def is_palindrome(self,str):
#         l=len(str)
#         rev=""
#         while l>0:
#             rev+=str[l-1]
#             l=l-1
#         if(rev==str):
#             return True
#         else:
#             return False
#     def long_word(self,str):
#         w = ""
#         all = []
#         str = str + " "
#         for i in range(0, len(str)):
#             if (str[i] != ' '):
#                 w = w + str[i]
#             else:
#                 all.append(w)
#                 w= ""

#         large = all[0]
#         for j in all:
#             if(len(j)>len(large)):
#                 large=j
#         return large


# a=string()
# print("Operations")
# print("1-> Enter a string to display a word with longest length")
# print("2-> Enter a string to determine the frequency of occourence of particular character")
# print("3-> Enter a string to check whether it is palindrome or not")
# print("4-> Enter a string and substring to check the index of first appearance of substring")
# print("5-> Enter a string to see the occurence of each word in the string")
# print("======")
# print()
# while(True):
#     ch=int(input("Enter your choice"))
#     if(ch==1):
#         str=input("Enter the string")
#         print(a.long_word(str))
#     elif(ch==2):
#         str=input("Enter the string")
#         char=input("Enter the character")
#         print(a.frequency(str,char))
#     elif(ch==3):
#         str=input("Enter the string ")
#         print(a.is_palindrome(str))
#     elif(ch==4):
#         str = input("Enter the string ")
#         sub=input("Enter the substring ")
#         print(a.index(str,sub))
#     elif(ch==5):
#         str = input("Enter the string ")
#         print(a.substr(str))
#     else:
#         break
#     print()
#     print("enter 0 to exit")











# def substring(sentence,sub:str):
#         """Returns the first occurence index of the given substring in the string"""    
#         for i in range(len(sentence)):
#             c = 0 
#             for j in range(len(sub)):
#                 try:
#                     if sentence[i+j] == sub[j] :
#                             c+=1
#                 except:
#                     break
                
#             if c==len(sub):
#                     return (sub,i)

           
#         return False


# print(substring(list("hahahaha rocket go brrrrr"),"rock"))


# def ismember(element,list:list)->bool:
#         """Returns True if element is in the list , else returns False"""
#         for i in range(len(list)):
#             if element==list[i]:
#                 return True
#         return False

# l=[(1,2),(5,6),(9,10)]
# print(ismember((1,2),l))
























# import time
# def sieve(n):
#     l = [1 for i in range(n+1)]
#     l[0] = 0 ;l[1]=0;
#     for i in range(2,int(n/2)+1):
#         if l[i]==1:
#             for j in range(2,int(n/i)+1):
#                         l[i*j]=0
             
#     return [i for i in range(n+1) if l[i]==1]

# print(len(sieve(5001)))




# # Python program to print all
# # primes smaller than or equal to
# # n using Sieve of Eratosthenes
 
 
# def SieveOfEratosthenes(n):
 
#     # Create a boolean array
#     # "prime[0..n]" and initialize
#     #  all entries it as true.
#     # A value in prime[i] will
#     # finally be false if i is
#     # Not a prime, else true.
#     prime = [True for i in range(n+1)]
#     prime[0]=0;prime[1]=0;
#     p = 2
#     while (p * p <= n):
 
#         # If prime[p] is not
#         # changed, then it is a prime
#         if (prime[p] == True):
 
#             # Update all multiples of p
#             for i in range(p * p, n+1, p):
#                 prime[i] = False
#         p += 1
 
#     # Print all prime numbers
#     return [i for i in range(len(prime)) if prime[i]==True]
 
 

# SieveOfEratosthenes(30)
# t2 = time.perf_counter()
# print(t2-t1)

















# def numbersWith3Divisors(n):
  
#     prime=[True]*(n+1);
#     prime[0] = prime[1] = False;
#     p=2;
#     while (p*p <= n):
         
#         # If prime[p] is not changed,
#         # then it is a prime
#         if (prime[p] == True):
             
#             # Update all multiples of p
#             for i in range(p*2,n+1,p):
#                 prime[i] = False;
#         p+=1;
 
# #     # print squares of primes upto n.
    
# #     i=0;
# #     while (i*i <= n):
# #         if (prime[i]):
# #             print("YES");
# #         else:
# #             print("NO")
# #         i+=1;
 
# # # Driver program
 
# # n = 96
# # numbersWith3Divisors(n);
# import math
# import sys
# def primecheck(n)->bool:
#     if n==0 or n==1 :
#         return False
#     for i in  range(2,int(n/2)+1):
#         if n%i==0:
#             return False
#     return True

# def f(n):
#     i = int(math.sqrt(n))
#     if n == i*i and primecheck(i):
#         sys.stdout.write('YES')
#     else:
#         sys.stdout.write('NO')

# n= input()
# l = list(map(int,input().split()))
# for i in l:
#     f(i)















# y=[]

# n= int(input())
# k = input()
# x = list(k)
# for i in range(len(x)):
#     try:
#         if x[i]==x[i+1]:
#             x.pop(i+1)
#             if x[i]==x[i+1]:
#                 x.pop(i+1)

#     except:
#         break

# print(x)






















# import sys
# n = int(input())
# l = list(map(int,input().split(" ")))
# def Divisors(n) :
#     z=0
    
#     for i in range(2,int(n/2)+1):
#         if n%i==0:
#             z+=1
#     return z

# for i in l:
#     if (Divisors(i))+2==3:
#         sys.stdout.write('YES')
#     else:
#         sys.stdout.write('NO')









# n = int(input())
# l = list(map(int,input().split(" ")))
# l.sort()

# x = l[-1]-l[0]-n+1
    
# print(x)


















# def gcd(m,n):
#     if m< n: 
#         (m,n) = (n,m)
#     while (m % n != 0):
#         (m, n) = (n, m % n)
#     return n


# def fact(n):
   
#     fact = 1
  
#     for i in range(1,n+1):
#         fact = fact * i

#     return fact




# x,y = map(int,input().split(" "))
# def f(x,y):
#     return gcd(fact(x),fact(y))


# print(f(x,y))













# def primecheck(n)->bool:
#     if n==0 or n==1 :
#         return False
#     for i in  range(2,int(n)):
#         if n%i==0:
#             return False
#     return True



# def f(n):
#     for i in range(1,1000):
#         if primecheck(i*n+1):
#             continue
#         else:
#             return i

# n= int(input())
# print(f(n))




























# def Divisors(n) :
#     l=[]
#     for i in range(1,n):
#         if n%i==0:
#             l.append(i)
#     return l



# def almost_prime(n):
#     x=0
#     for i in range(1,n+1):
#         final_list = [i for i in Divisors(i) if primecheck(i)]
     
#         if (len(final_list)==2):
#             x+=1

#     return x
    
# n = int(input())
# print(almost_prime(n))



















# from time import perf_counter
# t1 = perf_counter()
# def len(list:list)->int:
#         """Returns the length of the list"""
#         i=0
#         while True:
#             try:
#                 x = list[i]
#                 i+=1
#             except:
#                 break

#         return i
# x =len([1,2,3,4,5,6,7,8])
# t2 = perf_counter()
# print(t2-t1)























# x= "jump higher"
# y = "you have to jump higher than that"
# w_list=[]
# for i in range(len(y)):
#         if len(w_list)==0:
#             for j in range(len(x)):
#                 try:
#                     if y[i+j] == x[j]:
#                         w_list.append(x[j])
#                     else:
#                         break
#                 except:
#                     break
#         else:
#             break
# print(w_list)
























# l = x.split("\n")
# k=v.split("\n")
# for i in range(len(l)):
#     print(f"radiance21_{l[i]}_{i+1}",f"radiance21_{l[i]}_{i+1}+",k[i])



# string = "abscew"
# print(list(string))
# # l  = [12,45,36,28]
# x=[]
# def Divisors(n) :
#     l=[]
#     for i in range(1,n+1):
#         if n%i==0:
#             l.append(i)
#     return l
# for i in l:
#     x.append(len(Divisors(i)))


# print(x)
# print(sum(x))















# import random
# def binaryToDecimal(binary):
    
#     binary1 = binary
#     decimal, i, n = 0, 0, 0
#     while(binary != 0):
#         dec = binary % 10
#         decimal = decimal + dec * pow(2, i)
#         binary = binary//10
#         i += 1
        
#     return decimal 

# l = ["1","0","1","1","0","0","1"]
# done_list = []
# for i in range(100000):
#     random.shuffle(l)
#     x = int("".join(list(map(str,l))))
#     if binaryToDecimal(x) not in done_list:
#         done_list.append(binaryToDecimal(x))


# print(done_list,len(done_list))



















# def SieveOfEratosthenes(n):
#     list=[]
#     prime = [True for i in range(n + 1)]
#     p = 2
#     while (p * p <= n):
#         if (prime[p] == True):
        
#             for i in range(p ** 2, n + 1, p):
#                 prime[i] = False
#         p += 1
#     prime[0]= False
#     prime[1]= False
#     for p in range(n + 1):
#         if prime[p]:
#             list.append(p)

#     return list 

# l = SieveOfEratosthenes(2893390039)
# k=[i for i in l if 2893390039%i==0]


# print((k))

































# import random
# l = ["1","4","7","8"]
# done_list = []
# for i in range(1000000):
    
#         random.shuffle(l)
#         x=  int("".join(l))
        
#         if  x not in done_list and primecheck(x):
            
#             done_list.append(x)
# print(done_list)            
            













# l = [i for i in range(1,80)]
# while len(l)>1:
#     l.pop()
#     l.remove(l[0])






# print(l)








# l = [1,2,4,5,6,7]
# x = [7,5,6,2,4,1]
# k=0
# while l!=x:
#     for i in range(len(x)):
#         try:
#             if x[i]>x[i+1]:
#                 k+=1
#                 temp=x[i]
#                 x[i] =x[i+1]
#                 x[i+1]=temp
#         except:
#             continue
# print(k)
# print(x,l)
























# import math



# main_list = [i for i in range(0,10001) if Divisors(i)==3]
# print(len(main_list))
















# l=[5,12,45,23,16,8]
# k=[]
# for i in l:
#     for j in l:
#         if i!=j and (i,j) not in k and (j,i) not in k and (i+j)%2==0:
#             k.append((i,j))
            
# print(len(k),k)





























# for i in range (1,1000000):
  
#     s=1
    
#     x = str(i)
#     l=[int(y) for y in x]
#     for k in l:
#         s=s*k
    
#     if i==46*s:
#         print(i)
        

















# def f(string):
#     s = 0
#     for i in string :
#         x = ord(i)
#         s+=x
#     print(s)
#     if s%7==0:
#         return True

#     return False


# print(f("A"))













# import itertools
# list_p = [1,3,8,13,16,17]

# all_combinations = []
# for r in range(len(list_p) + 1):

#     combinations_object = itertools.combinations(list_p, r)
#     combinations_list = list(combinations_object)
#     all_combinations += combinations_list
# print(len([i for i in all_combinations if sum(list(i))%2==0]))























# print(computeGCD(60,48))
# # def compute_lcm(x, y):

#    # choose the greater number
#    if x > y:
#        greater = x
#    else:
#        greater = y

#    while(True):
#        if((greater % x == 0) and (greater % y == 0)):
#            lcm = greater
#            break
#        greater += 1

#    return lcm
# list_p = []
# for i in range(1,44):
#     for j in range(1,44):
#         if i!=j :
#             list_p.append(((i,j),computeGCD(i,j),compute_lcm(i,j)))
# print(list_p)
# # new_list = []
# # x_list = []
# for i in list_p:
    
#         new_list.append(sum(list(i)))
        
    

# print(x_list[new_list.index(max(new_list))])





















# class Set():
#     def _init_(self,n:int):
#         self.lst = []
#         self.n = n
#         self.set_creation(n)

#     def length (self, lst):              #returns length of lst
#         count = 0
#         for i in lst:
#             count += 1
#         return count

#     def add_element(self, item):   #This function adds item at the end of lst
#         self.lst += [item]

#     def is_exist(self , name):
#         for i in range(0,self.length(self.lst)):
#             if (self.lst[i] == name):
#                 return True
#         return False

#     def set_creation(self,n):
#         for i in range(n):
#             student = input("Enter name of student : ")
#             if (self.is_exist(student) == False):
#                 self.add_element(student)

#     def set_difference(self, Grp1, Grp2):
#         diff = []
#         for i in range(self.length(Grp1)):
#             count=0
#             for j in range(self.length(Grp2)):
#                 if (Grp1[i] != Grp2[j]):
#                     count += 1
#             if(count==self.length(Grp2)):
#                 diff += [Grp1[i]]
#         return diff

#     def display_set(self,lst):          # this function print given lst in format of set
#         print("{",end=" ")
#         for i in range(0,self.length(lst)):
#             if (lst[i]!=lst[len(lst)-1]):
#                 print(lst[i],end=" , ")
#             else:
#                 print(lst[i],end=" ")
#         print("}")

#     def set_intersection(self,Grp2):     #returns intersection of Grp1 and Grp2
#         Intersection = []
#         m = self.length(self.lst)
#         n = self.length(Grp2)
#         for i in range(m):
#             for j in range(n):
#                 if (self.lst[i] == Grp2[j]):
#                     Intersection += [Grp2[j]]
#         return Intersection

#     def set_union(self, Grp2):           #returns union of Grp1 and Grp2
#         Union = []
#         for i in range(self.length(self.lst)):
#             Union += [self.lst[i]]
#         for i in range(self.length(Grp2)):
#             for i in range(self.length(Grp2)):
#                 count = 0
#                 for j in range(self.length(Union)):
#                     if (Grp2[i] != Union[j]):
#                         count = count + 1
#                 if (count == self.length(Union)):
#                     Union += [Grp2[i]]
#         return Union

# N1 = int(input("Enter Number of student Who plays Cricket:"))
# cricket=Set(N1)
# N2 = int(input("Enter Number of student Who plays Badminton:"))
# badminton=Set(N2)
# N3 = int(input("Enter Number of student Who plays Football:"))
# football=Set(N3)

# print("Grp1:",end=" ")
# cricket.display_set(cricket.lst)
# print("Grp2:", end=" ")
# badminton.display_set(badminton.lst)
# print("Grp3:", end=" ")
# football.display_set(football.lst)

# print("MAIN MENU \n1.Students playing cricket and badminton \n2.Students playing cricket or badminton but not both")
# print("3.Number of students playing neither cricket nor badminton \n4.Number of students playing cricket and football but not badminton")

# while(True):
#     choice=int(input("Enter choice:"))
#     if(choice == 1):
#         Ans1 = cricket.set_intersection(badminton.lst)
#         print("Students playing cricket and badminton:", end=" ")
#         cricket.display_set(Ans1)
#     elif(choice == 2):
#         Grp1 = cricket.set_union(badminton.lst)
#         Grp2 = cricket.set_intersection(badminton.lst)
#         Ans2 = cricket.set_difference(Grp1,Grp2)
#         print("Students playing cricket or badminton but not both:", end=" ")
#         cricket.display_set(Ans2)
#     elif(choice == 3):
#         Grp1 = football.lst
#         Grp2 = cricket.set_union(badminton.lst)
#         Ans3 = cricket.set_difference(Grp1,Grp2)
#         print("Number of students playing neither cricket nor badminton:", cricket.length(Ans3))
#     elif(choice == 4):
#         Grp1 = cricket.set_intersection(football.lst)
#         Grp2 = badminton.lst
#         Ans4 = cricket.set_difference(Grp1,Grp2)
#         print("Number of students playing cricket and football but not badminton:", cricket.length(Ans4))

#     else:
#         print("Enter correct choice")
#     flag = input("Do you want to continue(y/n):")
#     if (flag == "n"):
#         break




# k=0
# s = 2010
# l=[]
# for i in range(70):
#     l.append((i,sum([i for i in range(i)])))
# print(l)
# for i in range(len(l)):
#     for j in range(len(l)) :
#         if abs(l[i][1]-l[j][1]) == 2010:
#             print(l[i][0],l[j][0])
#             break

# m=0
# n=0
# for i in range(4,64):
#     n+=1
#     m+=i
# print(n)
# print(m)





# def printTribRec(n) :
#     if (n == 0 or n == 1 or n == 2) :
#         return 0
#     elif (n == 3) :
#         return 1
#     else :
#         return (printTribRec(n - 1) +
#                 printTribRec(n - 2) +
#                 printTribRec(n - 3))
         
 
# def printTrib(n) :
#     for i in range(8, n) :
#         print( printTribRec(i) , " ", end = "")
         
 
# # Driver code
# printTrib(60)



















# def Fibonacci(n):
#     if n<0:
#         print("Incorrect input")
#     # First Fibonacci number is 0
#     elif n==0:
#         return 0
#     # Second Fibonacci number is 1
#     elif n==1:
#         return 1
#     else:
#         return Fibonacci(n-1)+Fibonacci(n-2)
 

 

# x=0


# for i in range(1,100):

#     x += (Fibonacci(i)/(10**i))
#     print(x)












# def f(string):
#     l = [int(i) for i in string]
#     x=l
#     x.sort(reverse=True)
#     l.sort()
    
#     y = [str(i) for i in x]
#     z = [str(i) for i in l]
#     k = int("".join(y)) -(int("".join(z)))
#     if k!=0:
#         f(str(k))
#     if k==0:
#         print("reached zero")

# f("1234")














# from math import sqrt 
# def factors(x):
#     # We will store all factors in `result`
#     result = []
#     i = 1
#     # This will loop from 1 to int(sqrt(x))
#     while i*i <= x:
#         # Check if i divides x without leaving a remainder
#         if x % i == 0:
#             result.append(i)
#             # Handle the case explained in the 4th
#             if x//i != i: # In Python, // operator performs integer/floored division
#                 result.append(x//i)
#         i += 1
#     # Return the list of factors of x
#     return result
# n=(2**8)*(3**4)*(5**6)*(7**4)
# x= factors(n)
# perfect_sqaures = [i for i in x if i%(sqrt(i))==0 ]
# print(len(perfect_sqaures))

























# x=[]

# for i in range (99999,999999):

#     l = [int(k) for k in str(i)]
#     if sum(l)==52:
#         x.append(i)
#         print(i)
    

# print(len(x))

















# def happy(n):
#     if n!=1:
#         l = [int(i)*int(i) for i in str(n)]
#         z = sum(l)
#         print(z)
#         happy(z)

#     if n==1:
#         return 1

# print(happy(46242))






















# def f(string):
#     primes = [2,3,5,7,11,13]
#     while True:
#         try :
#             x = string[primes[-1]]
#             break
#         except:
#             primes.pop()
    

#     try :
#         x = int(x)
#     except:
#         x = ord((x))
#     try:
#         y = int(string[2])
#     except:
#         y = ord((string[2]))
#     print(x,y)
#     return True if x-y==4 else False
	
# print(f("252pk8N"),f("19pn04"),f("Kl562640"),f("aBfqpnWj"))






























# def f(n):
#     l=[i for i in str(n)]
#     s = [fact(int(i)) for i in l]
#     if sum(s)==n:
#         return True
#     else:
#         False
	
# print(f(40583),f(40585),f(40857),f(40587))












# def C(x,y):
#     return fact(x)/(fact(x-y)*fact(y))

# print( C(12,3)+C(13,4)+C(14,9)+C(12,10))
# print(C(15,5))










# def f(x):
#     l= [i for i in range(1,x+1) if x%i==0]
#     x =str(len(l))
#     m = [int(i) for i in x]
#     if len(str(sum(m)))==2:
#         return x
#     return "Fail" 

# print(f(6483),f(45500),f(9523),f(45000))






















# import random
# def f(x):

#     for i in x:
#         if int(x[:(int(i)+1)])%(int(i)+1)!=0:
#             return False

#     return True
        
# for i in range(100000):
#     l = ["1","2","3","4","5"]
#     random.shuffle(l)
 
#     y = "".join(l)

#     if f(y):
#         print(y)
#         break
#     print("Fail")

    
    























# n= input()
# j = input().split(" ")
# l = [int(i) for i in j]
# while len(l)>1:
#     print(l)
#     l.sort()
#     if l[-1]-l[-2] not in l:
#         l.append(l[-1]-l[-2])  
#         l.sort()
#     l.pop()
#     print(l)
#     if len(l)>1:
#         l.pop()
#     else:
#         break
# print(l[0])














# from sys import stdin
# def factors(x):
#     result = []
#     i = 1
#     while i*i <= x:
#         if x % i == 0:
#             result.append(i)
#             if x//i != i: 
#                 result.append(x//i)
#         i += 1
    
#     return sum(result)

# x = stdin.readline()
# print(factors(x))



# import itertools
# n = input()
# l = input().split(" ")

# e = [int(i) for i in l if int(i)%2==0]
# all_combinations = []
# for r in range(len(e) + 1):

#     combinations_object = itertools.combinations(e, r)
#     combinations_list = list(combinations_object)
#     all_combinations += combinations_list

# print(len(all_combinations)-1)






























#Q5
# n,m=map(int,input().split(" "))
# def lcm(x,y):
#    n = x if x>y else y
#    while(True):
#        if((n % x == 0) and (n % y == 0)):
#            lcm = n
#            break
#        n += 1

#    return lcm
# def hcf(x,y):
#     n = x if x<y else y 
#     for i in range(1, n+1):
#         if((x % i == 0) and (y % i == 0)):
#             hcf = i 
#     return hcf

# print(hcf(n,m)+lcm(n,m))











































# #Q8
# def SieveOfEratosthenes(n):
#     list=[]
#     prime = [True for i in range(n + 1)]
#     p = 2
#     while (p * p <= n):
#         if (prime[p] == True):
        
#             for i in range(p ** 2, n + 1, p):
#                 prime[i] = False
#         p += 1
#     prime[0]= False
#     prime[1]= False
#     for p in range(n + 1):
#         if prime[p]:
#             list.append(p)

#     return list 
 

# n,m = map(int,(input().split(" ")))

# l= [i for i in SieveOfEratosthenes(m)if n+1<=i<=m]

# print(len(l))





#Q2

# def anagramCheck2(str1,str2):  
#     list1 = list(str1)  
#     list2 = list(str2)  
#     list1.sort()  
#     list2.sort()  
  
#     position = 0  
#     matches = True  
  
#     while position < len(str1) and matches:  
#         if list1[position]==list2[position]:  
#             position = position + 1  
#         else:  
#             matches = False  
  
#     return matches  
# n,m = input().split(" ")  
# print("YES" if anagramCheck2(n,m) else "NO")  





























#Q7
# from sys import stdin
# def primecheck(n)->bool:
#     if n==0 or n==1 :
#         return False
#     for i in  range(2,int(n)):
#         if n%i==0:
#             return False


#     return True

# x = stdin.readline()

# l=[i for i in (str(bin(int(x)))[2:])]
# print(l)
# print(abs(l.count("1")-l.count("0")))
# print("Yes" if primecheck(abs(l.count("1")-l.count("0"))) else "No")
