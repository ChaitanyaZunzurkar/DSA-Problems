#include <bits/stdc++.h>
using namespace std;

/*
INTUITION :

- Each rotten orange spreads rot to its 4-directional neighbors in 1 minute.
- Multiple rotten oranges spread simultaneously → this is a classic MULTI-SOURCE BFS.
- We push all initially rotten oranges into the queue with time = 0.
- BFS guarantees the minimum time to reach each fresh orange.
- We track the maximum time taken during BFS.
- After BFS, if any fresh orange is still unrotted, answer = -1.
*/

int orangesRotting(vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    queue<pair<pair<int,int>, int>> q; 
    vector<vector<int>> visited(n, vector<int>(m));

    // Step 1: Push all initially rotten oranges
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            visited[i][j] = grid[i][j];
            if(grid[i][j] == 2) {
                q.push({{i, j}, 0});
            }
        }
    }

    int maxi = 0;

    // Step 2: BFS traversal
    while(!q.empty()) {
        int i = q.front().first.first;
        int j = q.front().first.second;
        int time = q.front().second;
        q.pop();

        maxi = max(maxi, time);

        // left
        if(j - 1 >= 0 && visited[i][j-1] == 1) {
            visited[i][j-1] = 2;
            q.push({{i, j-1}, time + 1});
        }

        // right
        if(j + 1 < m && visited[i][j+1] == 1) {
            visited[i][j+1] = 2;
            q.push({{i, j+1}, time + 1});
        }

        // up
        if(i - 1 >= 0 && visited[i-1][j] == 1) {
            visited[i-1][j] = 2;
            q.push({{i-1, j}, time + 1});
        }

        // down
        if(i + 1 < n && visited[i+1][j] == 1) {
            visited[i+1][j] = 2;
            q.push({{i+1, j}, time + 1});
        }
    }

    // Step 3: Check if any fresh orange remains
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(visited[i][j] == 1) {
                return -1;
            }
        }
    }

    return maxi;
}

// Driver code (for testing)
int main() {
    vector<vector<int>> grid = {
        {2,1,1},
        {1,1,0},
        {0,1,1}
    };

    cout << orangesRotting(grid) << endl;
    return 0;
}
