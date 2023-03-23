#include<iostream>
#include<vector>



void printBoard(std::vector<std::vector<int>> &board)
{
    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board[0].size(); j++)
        {
            if(board[i][j] == 2)
            {
                std::cout << "Q ";
            }
            else
            {
                std::cout << board[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

void revertBoard(std::vector<std::vector<int>> &board , std::vector<std::vector<int>> &queenPos)
{
    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board[0].size(); j++)
        {
            board[i][j] = 0;
        }
    }
    for(int i = 0; i < queenPos.size(); i++)
    {
        updateBoard(board,queenPos[i][0],queenPos[i][1]);
    }
}


void updateBoard(std::vector<std::vector<int>> &board, int row , int col)
{

    for(int i = 0; i < board.size(); i++)
    {
        board[row][i] = 1;
        board[i][col] = 1;
    }
    
    int r = row;
    int c = col;
    //right lower diagonal 
    while(r >= 0 && c >= 0 && r < board.size() && c < board.size())
    {
        board[r][c] = 1;
        r++;
        c++;
    }
    r = row;
    c = col;
    //left lower diagonal
    while(r >= 0 && c >= 0 && r < board.size() && c < board.size())
    {
        board[r][c] = 1;
        r++;
        c--;
    }
    r = row;
    c = col;
    //right upper diagonal
    while(r >= 0 && c >= 0 && r < board.size() && c < board.size())
    {
        board[r][c] = 1;
        r--;
        c++;
    }
    r = row;
    c = col;
    //left upper diagonal
    while(r >= 0 && c >= 0 && r < board.size() && c < board.size())
    {
        board[r][c] = 1;
        r--;
        c--;
    }
    board[row][col] = 2;


}
bool canPlace(std::vector<std::vector<int>> &board, int row, int col)
{
    return board[row][col] == 1 || board[row][col] == 2 ; 
}
bool hasNoSpace(std::vector<std::vector<int>> &board)
{
    for(int i = 0; i < board.size(); i++)
    {
        for(int j = 0; j < board[0].size(); j++)
        {
            if(board[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

void solveQns(std::vector<std::vector<int>> & board, int nQueens)
{               
   while(nQueens > 0)
   {



   }
   return; 

}



int main()
{
    int nQueens = 4 ;
    std::vector<std::vector<int>>  board (nQueens,std::vector<int>(nQueens));
    std::vector<std::vector<int>>  queenPos(nQueens,std::vector<int>(2));
    return 0;
}