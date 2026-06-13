#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    // 1. BRUTE FORCE: O((N*M)*(N+M)) Time | O(1) Space
    // Intuition: Traverse the matrix; every time a 0 is found, scan its row and column
    // and mark non-zero elements as -1. Finally, replace all -1s with 0s.
    void setZeroesBrute(vector<vector<int>> &matrix)
    {
        int n = matrix.size(), m = matrix[0].size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (matrix[i][j] == 0)
                {
                    for (int k = 0; k < m; k++)
                        if (matrix[i][k] != 0)
                            matrix[i][k] = -1;
                    for (int k = 0; k < n; k++)
                        if (matrix[k][j] != 0)
                            matrix[k][j] = -1;
                }
            }
        }
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                if (matrix[i][j] == -1)
                    matrix[i][j] = 0;
    }

    // 2. BETTER SOLUTION: O(N*M) Time | O(N+M) Space
    // Intuition: Create two helper arrays to track which rows and columns contain zeros.
    // Fill the matrix based on these flags in a second pass.
    void setZeroesBetter(vector<vector<int>> &matrix)
    {
        int n = matrix.size(), m = matrix[0].size();
        vector<int> row(n, 0), col(m, 0);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (matrix[i][j] == 0)
                {
                    row[i] = 1;
                    col[j] = 1;
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (row[i] || col[j])
                    matrix[i][j] = 0;
            }
        }
    }

    // 3. OPTIMAL SOLUTION: O(N*M) Time | O(1) Space
    // Intuition: Use the first row and column as "markers" to save memory.
    // Use boolean flags to preserve the state of the first row and column.
    void setZeroesOptimal(vector<vector<int>> &matrix)
    {
        int n = matrix.size(), m = matrix[0].size();
        bool firstRowZero = false, firstColZero = false;

        for (int j = 0; j < m; j++)
            if (matrix[0][j] == 0)
                firstRowZero = true;
        for (int i = 0; i < n; i++)
            if (matrix[i][0] == 0)
                firstColZero = true;

        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < m; j++)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }
        for (int i = 1; i < n; i++)
        {
            for (int j = 1; j < m; j++)
            {
                if (matrix[0][j] == 0 || matrix[i][0] == 0)
                    matrix[i][j] = 0;
            }
        }
        if (firstRowZero)
            for (int j = 0; j < m; j++)
                matrix[0][j] = 0;
        if (firstColZero)
            for (int i = 0; i < n; i++)
                matrix[i][0] = 0;
    }
};

int main()
{
    int n, m;
    cout << "Enter dimensions (rows cols): ";
    cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int>(m));
    cout << "Enter matrix elements:" << endl;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> matrix[i][j];

    Solution sol;
    sol.setZeroesOptimal(matrix); // Using optimal approach

    cout << "Processed Matrix:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            cout << matrix[i][j] << " ";
        cout << endl;
    }
    return 0;
}