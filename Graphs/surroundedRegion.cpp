#include <bits/stdc++.h>
using namespace std;

class Solution {
private: 
    /*
        DFS is used to mark all 'O' cells that are
        connected to the boundary and hence are NOT surrounded.
        
        row, col  -> current cell
        board     -> input matrix
        vis       -> visited matrix to mark safe cells
    */
    void dfs(int row, int col, vector<vector<char>>& board, vector<vector<int>>& vis) {
        int n = board.size();
        int m = board[0].size();

        // Direction vectors: up, right, down, left
        int delrow[] = {-1, 0, 1, 0};
        int delcol[] = {0, 1, 0, -1};

        // Mark current cell as visited (safe)
        vis[row][col] = 1;
        
        // Explore all 4 directions
        for(int i = 0; i < 4; i++) {
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];

            // Check boundaries, unvisited, and only 'O' cells
            if(nrow >= 0 && nrow < n &&
               ncol >= 0 && ncol < m &&
               !vis[nrow][ncol] &&
               board[nrow][ncol] == 'O') {
                
                dfs(nrow, ncol, board, vis);
            }
        }
    }

public:
    /*
        LOGIC / INTUITION:
        -----------------
        1. Any 'O' connected to the boundary CANNOT be surrounded.
        2. Start DFS from all boundary 'O' cells and mark them as safe.
        3. After DFS, any 'O' that is NOT marked safe must be surrounded.
        4. Convert those surrounded 'O' cells into 'X'.
    */
    void solve(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();

        // Visited matrix to track safe 'O' cells
        vector<vector<int>> vis(n, vector<int>(m, 0));

        // Step 1: Traverse first and last column
        for(int i = 0; i < n; i++) {
            if(!vis[i][0] && board[i][0] == 'O')
                dfs(i, 0, board, vis);

            if(!vis[i][m-1] && board[i][m-1] == 'O')
                dfs(i, m-1, board, vis);
        }

        // Step 2: Traverse first and last row
        for(int j = 0; j < m; j++) {
            if(!vis[0][j] && board[0][j] == 'O')
                dfs(0, j, board, vis);

            if(!vis[n-1][j] && board[n-1][j] == 'O')
                dfs(n-1, j, board, vis);
        }

        // Step 3: Flip all unvisited 'O' cells to 'X'
        // These are fully surrounded regions
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(!vis[i][j] && board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
    }
};

int main() {
    int n, m;
    cout << "Enter number of rows and columns:\n";
    cin >> n >> m;

    vector<vector<char>> board(n, vector<char>(m));

    cout << "Enter the board (X or O):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }

    Solution sol;
    sol.solve(board);

    cout << "\nBoard after solving:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}