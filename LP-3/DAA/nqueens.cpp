#include <iostream>
#include <vector>

using namespace std;

// Function to check if a queen can be placed at a given position
bool isSafe(const vector<int>& board, int row, int col) {
    // Check for queens in the same column
    for (int i = 0; i < row; ++i) {
        if (board[i] == col ||             // Same column
            board[i] - i == col - row ||   // Diagonal (left to right)
            board[i] + i == col + row) {   // Diagonal (right to left)
            return false;
        }
    }
    return true;
}

// Function to solve the N-Queens problem using backtracking
void solveNQueens(vector<int>& board, int row, int n) {
    if (row == n) {
        // If all queens are placed successfully, print the board
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i] == j) {
                    cout << "Q ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
        cout << endl;
        return;
    }

    // Try placing a queen in each column of the current row
    for (int col = 0; col < n; ++col) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            solveNQueens(board, row + 1, n);
        }
    }
}

// Wrapper function to initialize the board and start solving
void nQueens(int n) {
    vector<int> board(n, -1); // Initialize the board with -1 (no queens placed yet)
    solveNQueens(board, 0, n); // Start solving from the first row
}

int main() {
    int n;
    cout << "Enter the size of the chessboard (N x N): ";
    cin >> n;

    nQueens(n);

    return 0;
}