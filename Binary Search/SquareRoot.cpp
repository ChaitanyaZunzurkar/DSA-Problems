#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int floorSqrt(int n) {
        // We want to find the floor value of sqrt(n).
        // Example: n = 10 -> sqrt(10) ≈ 3.16, floor = 3

        int low = 1, high = n;
        int ans = INT_MIN;  

        // Apply Binary Search between 1 and n
        while (low <= high) {
            int mid = low + (high - low) / 2;  // To avoid overflow
            long long square = 1LL * mid * mid;  // Square of mid

            if (square == n) {
                // If perfect square, directly return mid
                return mid;
            } else if (square > n) {
                // If square is too large, move left
                high = mid - 1;
            } else {
                // If square is smaller than n, store answer
                // because this mid could be the floor sqrt
                ans = mid;
                low = mid + 1; // Try to find bigger possible answer
            }
        }

        return ans; // Final floor sqrt
    }
};

int main() {
    int n;
    cout << "Enter a number: ";
    cin >> n;

    Solution obj;
    int result = obj.floorSqrt(n);
    cout << "Floor square root of " << n << " is: " << result << endl;

    return 0;
}
