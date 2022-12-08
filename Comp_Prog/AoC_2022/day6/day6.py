
def check_all_unique(data_chars:list):
    unique = set()
    for char in data_chars:
        unique.add(char)
    return len(unique) == len(data_chars)


with open ("input.txt", "r") as f:
    data = f.readlines()[0]
    temp_list = [i for i in data[0:14]]
    count = 14 # 4 is the number of characters in the first group
    for i in data[14:]:
        if(check_all_unique(temp_list)):
            print(count)
            break 
        else:
            del temp_list[0]
            temp_list.append(i)
            count += 1


