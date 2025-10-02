#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Brute Force Approach
    // --------------------
    // Intuition:
    // Koko can eat at a speed between 1 and max(piles).
    // If her speed is too small, she won't finish in h hours.
    // If her speed is very large, she can finish easily.
    // Brute force just tries every possible speed from 1 to max(piles)
    // and returns the first speed where she can finish within h hours.
    int minEatingSpeedBruteForce(vector<int>& piles, int h) {
        int maxi = *max_element(piles.begin(), piles.end());
        int n = piles.size();

        if (n == h) return maxi; // must eat one pile per hour

        for (int speed = 1; speed <= maxi; speed++) {
            long long totalHours = 0;
            for (int i = 0; i < n; i++) {
                // Hours needed for pile[i] = ceil(pile[i] / speed)
                totalHours += ceil((double)piles[i] / speed);
            }
            if (totalHours <= h) return speed; // Found minimum speed
        }

        return -1; // Should not happen for valid inputs
    }

    // Optimized Approach (Binary Search)
    // ----------------------------------
    // Intuition:
    // Instead of checking every speed, notice that:
    // - If a certain speed works (finishes within h hours),
    //   then any speed greater than it will also work.
    // - If a certain speed does not work, then any smaller
    //   speed will also not work.
    // This forms a "search space" pattern that can be solved
    // with Binary Search over possible speeds.
    int minEatingSpeedOptimized(vector<int>& piles, int h) {
        int maxi = *max_element(piles.begin(), piles.end());
        int low = 1, high = maxi;
        int result = maxi; // Initialize with maximum possible speed

        while (low <= high) {
            int mid = low + (high - low) / 2;
            long long totalHours = 0;

            // Calculate total hours needed if Koko eats at speed = mid
            for (int i = 0; i < piles.size(); i++) {
                totalHours += ceil((double)piles[i] / mid);
            }

            if (totalHours <= h) {
                // Speed works → try smaller to minimize it
                result = mid;
                high = mid - 1;
            } else {
                // Speed too slow → increase it
                low = mid + 1;
            }
        }

        return result;
    }
};

int main() {
    int n, h;
    cout << "Enter number of piles: ";
    cin >> n;

    vector<int> piles(n);
    cout << "Enter bananas in each pile: ";
    for (int i = 0; i < n; i++) {
        cin >> piles[i];
    }

    cout << "Enter number of hours (h): ";
    cin >> h;

    Solution obj;

    // Using Optimized Approach
    int ans = obj.minEatingSpeedOptimized(piles, h);
    cout << "Minimum eating speed (Optimized): " << ans << endl;

    // Optional: Using Brute Force Approach (for learning/debugging small inputs)
    // int ansBF = obj.minEatingSpeedBruteForce(piles, h);
    // cout << "Minimum eating speed (Brute Force): " << ansBF << endl;

    return 0;
}

