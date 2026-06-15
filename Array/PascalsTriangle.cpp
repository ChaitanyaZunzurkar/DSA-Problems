#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * Intuition:
     * Each row in Pascal's Triangle represents the binomial coefficients C(n, k).
     * Instead of calculating factorials (which can overflow easily), we calculate 
     * each element based on the previous one.
     * * Formula: C(n, k) = C(n, k-1) * (n - k + 1) / k
     * Where n is the row index and k is the column index.
     */
    vector<int> generateRow(int row) {
        vector<int> ansRow;
        ansRow.push_back(1); // The first element is always 1
        long long ans = 1;

        // Calculate subsequent elements in the row
        for (int col = 1; col < row; col++) {
            // Using the formula: ans = ans * (row - col) / col
            // Note: row here acts as the 'n' (nCr)
            ans = ans * (row - col);
            ans = ans / col;

            ansRow.push_back((int)ans);
        }

        return ansRow;
    }

    // Generates the full triangle up to numRows
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ans;
        for (int i = 1; i <= numRows; i++) {
            ans.push_back(generateRow(i));
        }
        return ans;
    }
};

int main() {
    int n;
    cout << "Enter the number of rows for Pascal's Triangle: ";
    cin >> n;

    if (n <= 0) {
        cout << "Please enter a positive integer." << endl;
        return 0;
    }

    Solution sol;
    vector<vector<int>> triangle = sol.generate(n);

    // Print the triangle
    cout << "\nPascal's Triangle (" << n << " rows):" << endl;
    for (int i = 0; i < triangle.size(); i++) {
        // Adding spacing for a triangular visual effect
        for (int j = 0; j < n - i - 1; j++) cout << " ";
        
        for (int val : triangle[i]) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}