#include <bits/stdc++.h>
using namespace std;

/*
INTUITION:

We need to find the distance of each cell containing 1
from the nearest 0.

Instead of:
For every 1 → searching nearest 0 (very slow)

We reverse thinking:

Start BFS from ALL 0s at once (Multi-source BFS).

Why?
Because BFS always gives shortest distance
in an unweighted graph.

Grid = graph
Each cell = node
4 directions = edges

Distance spreads like waves:

Level 0 → all 0s
Level 1 → neighbors of 0
Level 2 → neighbors of level 1
and so on...

The first time we reach a cell = shortest distance.
*/

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {

    int n = mat.size();
    int m = mat[0].size();

    // Queue stores: {{row, col}, distance}
    queue<pair<pair<int, int>, int>> q;

    // This matrix will store final distances
    vector<vector<int>> visited(n, vector<int>(m, 0));

    // Step 1: Push all 0s into queue
    // These are our starting points (distance = 0)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 0) {
                q.push({{i, j}, 0});
                visited[i][j] = 0;
            }
        }
    }

    // Step 2: BFS traversal
    while (!q.empty()) {

        int i = q.front().first.first;
        int j = q.front().first.second;
        int k = q.front().second; // current distance
        q.pop();

        // LEFT
        if (j - 1 >= 0 && visited[i][j - 1] == 0 && mat[i][j - 1] == 1) {
            visited[i][j - 1] = k + 1;
            q.push({{i, j - 1}, k + 1});
        }

        // RIGHT
        if (j + 1 < m && visited[i][j + 1] == 0 && mat[i][j + 1] == 1) {
            visited[i][j + 1] = k + 1;
            q.push({{i, j + 1}, k + 1});
        }

        // UP
        if (i - 1 >= 0 && visited[i - 1][j] == 0 && mat[i - 1][j] == 1) {
            visited[i - 1][j] = k + 1;
            q.push({{i - 1, j}, k + 1});
        }

        // DOWN
        if (i + 1 < n && visited[i + 1][j] == 0 && mat[i + 1][j] == 1) {
            visited[i + 1][j] = k + 1;
            q.push({{i + 1, j}, k + 1});
        }
    }

    return visited;
}

int main() {

    int n, m;
    cout << "Enter number of rows and columns: ";
    cin >> n >> m;

    vector<vector<int>> mat(n, vector<int>(m));

    cout << "Enter matrix values (0 or 1):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mat[i][j];
        }
    }

    vector<vector<int>> result = updateMatrix(mat);

    cout << "\nDistance Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
