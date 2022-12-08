#part one
# def check_line(line):
#     pair_1 ,pair_2 = line.strip().split(",")
#     p1 = list(map(int, pair_1.split("-")))
#     p2 = list(map(int, pair_2.split("-")))
#     if p1[0]<=p2[0] and p1[1]>=p2[1] or p2[0]<=p1[0] and p2[1]>=p1[1]:
#         print(p1,p2)
#         return 1
#     return 0 ; 


#part two 
def check_line(line):
    pair_1 ,pair_2 = line.strip().split(",")
    p1 = list(map(int, pair_1.split("-")))
    p2 = list(map(int, pair_2.split("-")))
    for i in range(p1[0],p1[1]+1):
        if i in range(p2[0],p2[1]+1):
            print(p1,p2)
            return 1
    return 0 


with open("input.txt") as f: 
    lines = f.readlines()
    total = 0 
    for line in lines:
        total += check_line(line)
    print(total)
       
