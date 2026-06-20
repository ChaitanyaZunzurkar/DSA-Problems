#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:

    /*
    =========================================================
    APPROACH 1: Extra Matrix (Brute Force)
    =========================================================

    INTUITION:
    After rotating a matrix by 90° clockwise:
    
    Original Position → New Position
    (i, j) → (j, n-i-1)

    Example:
    1 2 3
    4 5 6
    7 8 9

    After Rotation:
    7 4 1
    8 5 2
    9 6 3

    We create a new matrix and place every element
    in its rotated position.

    Time Complexity: O(N²)
    Space Complexity: O(N²)
    */

    void rotateBrute(vector<vector<int>>& matrix) {
        int n = matrix.size();

        vector<vector<int>> ans(n, vector<int>(n));

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                ans[j][n - i - 1] = matrix[i][j];
            }
        }

        matrix = ans;
    }


    /*
    =========================================================
    APPROACH 2: Store Columns (Better but Extra Space)
    =========================================================

    INTUITION:
    Rotate by taking columns from left → right
    and collecting elements bottom → top.

    Example:
    1 2 3
    4 5 6
    7 8 9

    Column 0 → 7 4 1
    Column 1 → 8 5 2
    Column 2 → 9 6 3

    Build new matrix using these columns.

    Time Complexity: O(N²)
    Space Complexity: O(N²)
    */

    void rotateColumnMethod(vector<vector<int>>& matrix) {

        int n = matrix.size();

        vector<vector<int>> cols;

        for(int col = 0; col < n; col++) {

            vector<int> temp;

            for(int row = n - 1; row >= 0; row--) {
                temp.push_back(matrix[row][col]);
            }

            cols.push_back(temp);
        }

        matrix = cols;
    }


    /*
    =========================================================
    APPROACH 3: Optimal (Transpose + Reverse)
    =========================================================

    INTUITION:

    Rotation = Transpose + Reverse each row

    STEP 1: Transpose
    Convert rows into columns

    1 2 3
    4 5 6
    7 8 9

    ↓

    1 4 7
    2 5 8
    3 6 9

    STEP 2: Reverse every row

    7 4 1
    8 5 2
    9 6 3

    Time Complexity: O(N²)
    Space Complexity: O(1)
    */

    void rotateOptimal(vector<vector<int>>& matrix) {

        int n = matrix.size();

        // Transpose
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // Reverse every row
        for(int i = 0; i < n; i++) {
            reverse(matrix[i].begin(), matrix[i].end());
        }
    }
};


// Function to print matrix
void printMatrix(vector<vector<int>>& matrix) {

    for(auto row : matrix) {
        for(auto val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}


int main() {

    int n;

    cout << "Enter matrix size (N for NxN): ";
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));

    cout << "Enter matrix elements:\n";

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> matrix[i][j];
        }
    }

    Solution obj;

    int choice;

    cout << "\nChoose Rotation Method:\n";
    cout << "1 → Brute Force\n";
    cout << "2 → Column Method\n";
    cout << "3 → Optimal (Transpose + Reverse)\n";

    cin >> choice;

    switch(choice) {

        case 1:
            obj.rotateBrute(matrix);
            break;

        case 2:
            obj.rotateColumnMethod(matrix);
            break;

        case 3:
            obj.rotateOptimal(matrix);
            break;

        default:
            cout << "Invalid Choice\n";
            return 0;
    }

    cout << "\nRotated Matrix:\n";
    printMatrix(matrix);

    return 0;
}