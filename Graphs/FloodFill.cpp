#include <bits/stdc++.h>
using namespace std;

/*
Intuition:
----------
Flood Fill means:
1. Start from (sr, sc)
2. Change its color to `newColor`
3. Then move in 4 directions (up, down, left, right)
4. If a neighboring cell has the SAME ORIGINAL color,
   then it should also be colored and explored further

Why BFS?
--------
BFS is natural here because:
- We start from a source
- We expand level by level to all connected cells
- Queue helps us process neighbors cleanly

Key idea:
---------
We DO NOT compare with updated colors.
We compare with the original starting color.
*/

vector<vector<int>> floodFill_BFS(
    vector<vector<int>> &image,
    int sr,
    int sc,
    int newColor
) {
    int n = image.size();
    int m = image[0].size();

    // Original color at the starting cell
    int startColor = image[sr][sc];

    // If the color is already same, no need to do anything
    if (startColor == newColor) {
        return image;
    }

    queue<pair<int, int>> q;
    q.push({sr, sc});

    // Change the starting cell color
    image[sr][sc] = newColor;

    // Direction arrays for left, right, up, down
    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // Explore all 4 directions
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            // Check bounds
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {

                // If the neighbor has the original color
                if (image[nx][ny] == startColor) {
                    image[nx][ny] = newColor;
                    q.push({nx, ny});
                }
            }
        }
    }

    return image;
}

int main() {
    int n, m;
    cout << "Enter number of rows and columns: ";
    cin >> n >> m;

    vector<vector<int>> image(n, vector<int>(m));
    cout << "Enter the image matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> image[i][j];
        }
    }

    int sr, sc, color;
    cout << "Enter starting row, starting column and new color: ";
    cin >> sr >> sc >> color;

    vector<vector<int>> result = floodFill_BFS(image, sr, sc, color);

    cout << "\nFlood filled image:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << result[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
