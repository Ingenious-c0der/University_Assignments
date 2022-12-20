def swap(numbers, indices, index, n):
    value = numbers[index]
    location_of_index = [i for i, x in enumerate(indices) if x == index][0]
    indices.pop(location_of_index)
    insert_at = (location_of_index + value) % (n - 1)
    indices.insert(insert_at, index)
    return value
 
numbers = []
input_lines = open('input.txt').read().splitlines()
for i in range(len(input_lines)):
    line = int(input_lines[i])
    numbers.append(line) # numbers.append(line * 811589153) # for part 2
 
n = len(numbers)
numbers = numbers
indices = [i for i in range(n)]
 
for k in range(1): # for k in range(10): # for part 2
    for i, number in enumerate(numbers):
        swap(numbers, indices, i, n)
 
new_list = [numbers[i] for i in indices]
print(new_list)
index_of_zero = [i for i, x in enumerate(new_list) if x == 0][0]
print(new_list[(1000 + index_of_zero) % n] + new_list[(2000 + index_of_zero) % n]+ new_list[(3000 + index_of_zero) % n])