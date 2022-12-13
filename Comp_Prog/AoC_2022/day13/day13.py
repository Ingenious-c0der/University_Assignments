def parse_line(line):
    main_list = []
    i = 0
    while (i < len(line)):
        if (line[i] == "["):
            i += 1
            RES = parse_line(line[i:])
            main_list.append(RES[1])
            i += RES[0]
        elif (line[i] == ","):
            i += 1
        elif (line[i] == "]"):
            i += 1
            return (i, main_list)
        elif (line[i].isdigit()):
            print(len(line),i ,line)
            end = i 
            while end < len(line) and line[end].isdigit():
                end += 1
            main_list.append(int(line[i:end]))
            i = end+1
    return (i, main_list)


def compare_lists(list_1: list, list_2: list) -> int:
    for x, y in zip(list_1, list_2):
        if (type(x) == type(y) and type(x) == int):
            if (x < y):
                return -1
            if (x > y):
                return 1
        elif isinstance(x, list) or isinstance(y, list):
            # check for integer elements
            if isinstance(x, int):
                x = [x]
            if isinstance(y, int):
                y = [y]

            # recurse deeper and transform element to list
            result = compare_lists(x, y)

            # check whether the result brought anything
            # otherwise we continue
            if result:
                return result
                
    if(len(list_1) < len(list_2)):
        return -1
    elif(len(list_1) > len(list_2)):
        return 1 
    else:
        return 0

with open("input.txt") as f:
    pair_1,  pair_2 = [], []
    flag = 0
    index = 1
    total = 0
    for (line) in f:
        if (line == "\n"):
            continue
        else:
            if (flag == 0):
                pair_1 = parse_line(line.strip("\n")[1:len(line)-2])[1]
                flag = 1
            else:
                pair_2 = parse_line(line.strip("\n")[1:len(line)-2])[1]
                flag = 0
                print(pair_1)
                print(pair_2)
                d = compare_lists(pair_1, pair_2)
                print(d)
                if (d == -1):
                    total += index
                index += 1
print(total)