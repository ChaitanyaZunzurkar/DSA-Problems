#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    // Function to find the integer nth root of m
    int nthRoot(int n, int m) {
        int low = 1;
        int high = m;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            long long res = 1;
            for (int i = 0; i < n; i++) {
                res *= mid;
            }

            if (res == m) {
                return mid;  // Perfect nth root found
            } else if (res < m) {
                low = mid + 1;  // Try a larger mid
            } else {
                high = mid - 1; // Try a smaller mid
            }
        }

        return -1; // If no integer nth root exists
    }
};

int main() {
    int n, m;
    cout << "Enter n and m: ";
    cin >> n >> m;

    Solution obj;
    int result = obj.nthRoot(n, m);
    if (result != -1)
        cout << "The integer " << n << "-th root of " << m << " is: " << result << endl;
    else
        cout << m << " does not have an integer " << n << "-th root." << endl;

    return 0;
}
