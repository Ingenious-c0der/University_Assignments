
# Python program to solve N Queen
# Problem using backtracking
 
global N
N = 8
 
def printSolution(board):
    for i in range(N):
        for j in range(N):
            print (board[i][j],end=' ')
        print()
 
 
# A utility function to check if a queen can
# be placed on board[row][col]. Note that this
# function is called when "col" queens are
# already placed in columns from 0 to col -1.
# So we need to check only left side for
# attacking queens
def isSafe(board, row, col):
 
    # Check this row on left side
    for i in range(col):
        if board[row][i] == 1:
            return False
 
    # Check upper diagonal on left side
    for i, j in zip(range(row, -1, -1), range(col, -1, -1)):
        if board[i][j] == 1:
            return False
 
    # Check lower diagonal on left side
    for i, j in zip(range(row, N, 1), range(col, -1, -1)):
        if board[i][j] == 1:
            return False
 
    return True
 
def solveNQUtil(solutions,board, col):
    if col >= N:
        solutions.append(board)
        return True
    for i in range(N):
        if isSafe(board, i, col):
            board[i][col] = 1
            solveNQUtil(solutions,board, col + 1) 
            board[i][col] = 0
 
def solveNQ():
    board = [ 
            [0, 0, 0, 0 , 0, 0, 0, 0],
            [0, 0, 0, 0 , 0, 0, 0, 0],
            [0, 0, 0, 0 , 0, 0, 0, 0],
            [0, 0, 0, 0 , 0, 0, 0, 0],
            [0, 0, 0, 0 , 0, 0, 0, 0],
            [0, 0, 0, 0 , 0, 0, 0, 0],
            [0, 0, 0, 0 , 0, 0, 0, 0],
            [0, 0, 0, 0 , 0, 0, 0, 0],
            ]
    solutions = []
    if solveNQUtil(solutions,board, 0) == False:
        print ("Solution does not exist")
        return False
    print(len(solutions))
    printSolution(board)
    return True
 
# driver program to test above function
solveNQ()