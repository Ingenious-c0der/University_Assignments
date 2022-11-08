
A = [1,3,5,2,4]
B = [1,4,2,9]
C =  [1,2,8,4]

def solve(N,M,A,B,C):
    total_coins_per_hero = [ ]
    for i in range(N):
        total_coins_per_hero.append(0)
    for i in range(N):
        for j in range(M):
            if A[i] >= B[j]:
                total_coins_per_hero[i] += C[j]
    return total_coins_per_hero

print(solve(5,4,A,B,C))
