#include <bits/stdc++.h>
using namespace std;

/*
INTUITION (VERY IMPORTANT):

We do NOT try to find which 'O' is surrounded.
Instead, we find which 'O' is NOT surrounded.

Key Observation:
- Any 'O' connected to a BORDER 'O' can NEVER be surrounded.
- Only those 'O' which are NOT connected to border 'O' should be flipped to 'X'.

So the plan:
1. Start DFS from all border cells having 'O'
2. Mark all reachable 'O' as SAFE using a temporary marker '#'
3. After that:
   - Remaining 'O'  → surrounded → change to 'X'
   - '#' (safe)     → restore back to 'O'
*/

class Solution {
public:
    int n, m;

    /*
    DFS FUNCTION:
    - Marks all 'O' connected to a border 'O' as safe
    - We change 'O' to '#' to mark it as visited & safe
    */
    void dfs(int i, int j, vector<vector<char>>& board) {
        // Base case: out of bounds OR not 'O'
        if (i < 0 || j < 0 || i >= n || j >= m || board[i][j] != 'O')
            return;

        // Mark current cell as safe
        board[i][j] = '#';

        // Explore all 4 directions
        dfs(i + 1, j, board);
        dfs(i - 1, j, board);
        dfs(i, j + 1, board);
        dfs(i, j - 1, board);
    }

    void solve(vector<vector<char>>& board) {
        n = board.size();
        m = board[0].size();

        /*
        STEP 1: Run DFS from all border cells
        Any 'O' connected to border is NOT surrounded
        */

        // Left and Right borders
        for (int i = 0; i < n; i++) {
            dfs(i, 0, board);
            dfs(i, m - 1, board);
        }

        // Top and Bottom borders
        for (int j = 0; j < m; j++) {
            dfs(0, j, board);
            dfs(n - 1, j, board);
        }

        /*
        STEP 2: Final conversion
        - 'O'  → surrounded → change to 'X'
        - '#'  → safe → restore back to 'O'
        */
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == '#')
                    board[i][j] = 'O';
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