def subsetSum(start,currentSum,targetSum, setl,subset:list)->list:
    result = []
    if currentSum == targetSum:
        result.append(subset[:])
        return result
    for i in range(start,len(setl)):
        currentSum+=setl[i]
        subset.append(setl[i])
        result+= subsetSum(i+1,currentSum,targetSum,setl,subset)
        currentSum -=  subset.pop()
    return result

x = [13,43,44,20,18,14,15,16,9,8,6,4,4,3,2,1]
target = 51
print(subsetSum(0,0,target,x,[]))

