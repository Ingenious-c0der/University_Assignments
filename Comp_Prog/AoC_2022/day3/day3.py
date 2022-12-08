alpha_array = [chr(i) for i in range(ord('a'), ord('z')+1)] + [chr(i) for i in range(ord('A'), ord('Z')+1)]
def process(p_list:list):
    for i in p_list[0]:
        if i in p_list[1] and i in p_list[2]:
            print(i , alpha_array.index(i) + 1)
            return alpha_array.index(i) + 1
with open("input.txt") as f:
    count = 0 ; 
    process_list = []
    total = 0
    for line in f: 
        process_list.append(line.strip())
        count  = (count+1) %3 
        if count == 0:
            total +=  process(process_list)
            process_list = []
    print(total)
            

