#include <bits/stdc++.h>
using namespace std;

void setZeroes_brute1(vector<vector<int>>& matrix) {
    /*
        Intuition:
            - If a cell contains 0, then its entire row and entire column
              must be set to 0.
            - While updating the matrix, we must avoid modifying rows/columns
              immediately, because that could create new zeros and affect
              further decisions.
            - So first, we store the positions (row, column) of all zeros
              found in the original matrix.
            - Then, using those stored positions, we set the corresponding
              rows and columns to 0.
    */

    vector<pair<int, int>> zeros;

    // Step 1: Collect positions of all zero elements
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] == 0) {
                zeros.push_back({i, j});
            }
        }
    }

    // Step 2: Set entire row to zero for each stored zero position
    for (auto &p : zeros) {
        for (int i = 0; i < matrix[0].size(); i++) {
            matrix[p.first][i] = 0;
        }
    }

    // Step 3: Set entire column to zero for each stored zero position
    for (auto &p : zeros) {
        for (int i = 0; i < matrix.size(); i++) {
            matrix[i][p.second] = 0;
        }
    }
}

void setZeroes_brute2(vector<vector<int>>& matrix) {
        /*
            Brute Force Intuition:
            - Traverse every cell of the matrix.
            - Whenever a 0 is found at position (i, j),
              we immediately mark all non-zero elements
              in the same row and column with a special marker.
            - The marker must be a value that does NOT appear
              in the matrix (we use -1 here).
            - After the full traversal, convert all markers to 0.

            Why marker is needed:
            - Directly setting values to 0 will create new zeros
              and wrongly affect further traversal.
        */

    int rows = matrix.size();
    int cols = matrix[0].size();

    // Step 1: Mark rows and columns using a special value
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 0) {

                // Mark entire row
                for (int k = 0; k < cols; k++) {
                    if (matrix[i][k] != 0) {
                        matrix[i][k] = -1;
                    }
                }

                // Mark entire column
                for (int k = 0; k < rows; k++) {
                    if (matrix[k][j] != 0) {
                        matrix[k][j] = -1;
                    }
                }
            }
        }
    }

    // Step 2: Convert all markers to 0
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == -1) {
                matrix[i][j] = 0;
            }
        }
    }
}

/* ===========================
   Driver Code (Example)
   =========================== */
int main() {
    vector<vector<int>> matrix = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };

    setZeroes_brute1(matrix);

    // Print result
    for (auto &row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
