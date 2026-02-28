#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    /*
        INTUITION:
        ----------
        We want to count how many connected components of '1's exist in the grid.
        Each connected component is one island.

        We use BFS to traverse all cells of an island starting from one land cell.
        While traversing, we mark cells as visited so that they are not counted again.

        Only 4-directional movement is allowed:
        - Up
        - Right
        - Down
        - Left
    */

    void bfs(vector<vector<char>> &grid,
             vector<vector<int>> &vis,
             queue<pair<int,int>> &q) {

        int n = grid.size();
        int m = grid[0].size();

        // Directions: up, right, down, left
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        // Standard BFS
        while (!q.empty()) {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();

            // Explore all 4 neighbors
            for (int i = 0; i < 4; i++) {
                int nrow = row + dx[i];
                int ncol = col + dy[i];

                /*
                    Check:
                    1. New cell is inside grid boundaries
                    2. Cell is land ('1')
                    3. Cell is not visited yet
                */
                if (nrow >= 0 && nrow < n &&
                    ncol >= 0 && ncol < m &&
                    grid[nrow][ncol] == '1' &&
                    vis[nrow][ncol] == 0) {

                    // Mark visited and push into queue
                    vis[nrow][ncol] = 1;
                    q.push({nrow, ncol});
                }
            }
        }
    }

public:
    /*
        APPROACH:
        ---------
        1. Traverse the entire grid.
        2. Whenever we find an unvisited land cell ('1'):
           - It means we found a new island.
           - Increment island count.
           - Start BFS from that cell to mark the whole island visited.
        3. Return the total island count.
    */
    int numIslands(vector<vector<char>>& grid) {

        int n = grid.size();
        int m = grid[0].size();

        vector<vector<int>> vis(n, vector<int>(m, 0));
        queue<pair<int,int>> q;

        int count = 0;

        // Traverse each cell of the grid
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                // If land cell and not visited, it's a new island
                if (grid[i][j] == '1' && vis[i][j] == 0) {
                    count++;              // New island found
                    vis[i][j] = 1;        // Mark starting cell visited
                    q.push({i, j});       // Start BFS
                    bfs(grid, vis, q);
                }
            }
        }

        return count;
    }
};

int main() {
    /*
        INPUT FORMAT:
        -------------
        n m
        grid (n rows, m columns, characters '0' or '1')

        Example:
        4 5
        1 1 0 0 0
        1 1 0 0 0
        0 0 1 0 0
        0 0 0 1 1
    */

    int n, m;
    cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    Solution sol;
    cout << sol.numIslands(grid) << endl;

    return 0;
}