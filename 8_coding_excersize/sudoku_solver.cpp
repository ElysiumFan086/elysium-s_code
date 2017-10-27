bool isValid(vector<vector<char>>& board, int i, int j) {
    for(int col = 0; col < 9; ++col) {
        if(col != j && board[i][j]  == board[i][col])
            return false;
    }
    
    for(int row = 0; row < 9; ++row) {
        if(row != i && board[i][j] == board[row][j])
            return false;
    }
    
    for(int row = i / 3 * 3; row < i / 3 * 3 + 3; ++row) {
        for(int col = j / 3 * 3; col < j / 3 * 3 + 3; ++col) {
            if(row != i && col != j && board[row][col] == board[i][j])
                return false;
        }
    }
    
    return true;
}

bool solverSudokuDFS(vector<vector<char>>& board, int i, int j) {
    if(i == 9)  return true;    // Finished all elments testing in a row
    // If finished the last element in a row, testing the next row from its first element
    if(j >= 9)  return solverSudokuDFS(board, i + 1, 0);
    
    if(board[i][j] == '.') {
        for(int k = 1; k <= 9; ++k) {
            board[i][j] = (char)('0' + k);
            if(isValid(board, i, j)) {
                if(solverSudokuDFS(board, i, j + 1))  return true;
            }
            board[i][j] = '.';
        }
    }
    else {
        return solverSudokuDFS(board, i, j + 1);
    }
    
    return false;
}

void solveSudoku(vector<vector<char>>& board) {
    if(board.empty() || board.size() != 9 || board[0].size() != 9)  return;
    
    solverSudokuDFS(board, 0, 0);
}