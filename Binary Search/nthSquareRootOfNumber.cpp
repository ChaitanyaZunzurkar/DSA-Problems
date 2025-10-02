#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    // Function to compute mid^n safely
    long long power(long long mid, int n, int m) {
        long long result = 1;

        // Binary exponentiation (O(log n))
        while (n > 0) {
            if (n % 2 == 1) {
                result = result * mid;
                if (result > m) return m + 1; // Overflow check
                n--;
            } else {
                mid = mid * mid;
                if (mid > m) return m + 1; // Overflow check
                n = n / 2;
            }
        }

        return result;
    }

    // Function to find integer nth root of m
    int nthRoot(int n, int m) {
        int low = 1, high = m;

        while (low <= high) {
            long long mid = low + (high - low) / 2;

            long long res = power(mid, n, m); // Compute mid^n safely

            if (res == m) {
                return mid; // Found exact nth root
            } else if (res < m) {
                low = mid + 1; // Try bigger mid
            } else {
                high = mid - 1; // Try smaller mid
            }
        }

        return -1; // No exact integer nth root exists
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
