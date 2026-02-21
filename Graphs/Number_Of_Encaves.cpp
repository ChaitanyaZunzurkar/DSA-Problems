#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    /*
        INTUITION (DFS FUNCTION):
        -------------------------
        - If a land cell (1) is connected to the boundary,
          then it can never be an enclave.
        - This DFS marks all such land cells as visited.
        - Later, we will ignore these visited cells while counting enclaves.
    */
    void dfs(int row, int col, vector<vector<int>>& grid, vector<vector<int>>& vis) {
        int n = grid.size();
        int m = grid[0].size();

        // Possible movements: up, right, down, left
        int delrow[] = {-1, 0, 1, 0};
        int delcol[] = {0, 1, 0, -1};

        // Mark the current land cell as visited (not an enclave)
        vis[row][col] = 1;

        // Try moving in all 4 directions
        for(int i = 0; i < 4; i++) {
            int nrow = row + delrow[i];
            int ncol = col + delcol[i];

            /*
                INTUITION:
                - Stay inside the grid
                - Visit only unvisited land cells (1)
                - Continue DFS to mark all boundary-connected land
            */
            if(nrow >= 0 && nrow < n &&
               ncol >= 0 && ncol < m &&
               !vis[nrow][ncol] &&
               grid[nrow][ncol] == 1) {

                dfs(nrow, ncol, grid, vis);
            }
        }
    }

public:
    /*
        INTUITION (MAIN LOGIC):
        ----------------------
        - Enclave = land cell (1) that CANNOT reach the boundary.
        - Any land connected to the boundary is NOT an enclave.
        
        STEPS:
        1. Start DFS from all boundary land cells.
        2. Mark all land cells connected to boundary as visited.
        3. Count the remaining unvisited land cells.
    */
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        // Visited matrix to mark boundary-connected land cells
        vector<vector<int>> vis(n, vector<int>(m, 0));

        /*
            STEP 1:
            --------
            Traverse first and last columns.
            Any land found here is connected to boundary,
            so it cannot be an enclave.
        */
        for(int i = 0; i < n; i++) {
            if(!vis[i][0] && grid[i][0] == 1)
                dfs(i, 0, grid, vis);

            if(!vis[i][m-1] && grid[i][m-1] == 1)
                dfs(i, m-1, grid, vis);
        }

        /*
            STEP 2:
            --------
            Traverse first and last rows for the same reason.
        */
        for(int j = 0; j < m; j++) {
            if(!vis[0][j] && grid[0][j] == 1)
                dfs(0, j, grid, vis);

            if(!vis[n-1][j] && grid[n-1][j] == 1)
                dfs(n-1, j, grid, vis);
        }

        /*
            STEP 3:
            --------
            Count all land cells that were NOT visited.
            These cells are completely surrounded by water,
            hence they are enclaves.
        */
        int count = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(!vis[i][j] && grid[i][j] == 1) {
                    count++;
                }
            }
        }

        return count;
    }
};

int main() {
    int n, m;
    cout << "Enter number of rows and columns: ";
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));

    cout << "Enter grid (0 = water, 1 = land):\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    Solution obj;
    cout << "Number of enclaves: " << obj.numEnclaves(grid) << endl;

    return 0;
}