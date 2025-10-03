#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Intuition (Brute Force):
    // -------------------------
    // We try each possible day from minimum bloom day to maximum bloom day.
    // For each day, we check if at least m bouquets of size k can be made.
    // This works but is very slow because the day range can go up to 1e9.
    // Time Complexity: O((maxi - mini) * n) → not feasible for large inputs.
    int bruteForce(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();
        long long M = m, K = k;
        if (n < M * K) return -1;

        int mini = INT_MAX, maxi = INT_MIN;
        for (int day : bloomDay) {
            mini = min(mini, day);
            maxi = max(maxi, day);
        }

        int result = INT_MAX;
        for (int d = mini; d <= maxi; d++) {
            int count = 0, numOfBouquet = 0;
            for (int j = 0; j < n; j++) {
                if (bloomDay[j] <= d) {
                    count++;
                } else {
                    numOfBouquet += (count / k);
                    count = 0;
                }
            }
            numOfBouquet += (count / k);
            if (numOfBouquet >= m) {
                result = min(result, d);
            }
        }
        return (result == INT_MAX ? -1 : result);
    }

    // Intuition (Optimized with Binary Search):
    // ----------------------------------------
    // Instead of trying every day, we use binary search on the "answer".
    // Each candidate day 'mid' is checked: can we make at least m bouquets
    // by this day? If yes, try smaller days (move left), else try bigger days.
    // This reduces the search space from 1e9 days to log(1e9) ≈ 30 checks.
    // Each check takes O(n). Much faster.
    // Time Complexity: O(n * log(maxi - mini))
    int minDays(vector<int>& bloomDay, int m, int k) {
        int n = bloomDay.size();
        long long M = m, K = k;
        if (n < M * K) return -1;

        int mini = INT_MAX, maxi = INT_MIN;
        for (int day : bloomDay) {
            mini = min(mini, day);
            maxi = max(maxi, day);
        }

        int low = mini, high = maxi, result = -1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            int count = 0, numOfBouquet = 0;
            for (int j = 0; j < n; j++) {
                if (bloomDay[j] <= mid) {
                    count++;
                } else {
                    numOfBouquet += (count / k);
                    count = 0;
                }
            }
            numOfBouquet += (count / k);

            if (numOfBouquet >= m) {
                result = mid;
                high = mid - 1; // Try to find smaller day
            } else {
                low = mid + 1;
            }
        }
        return result;
    }
};

int main() {
    int n, m, k;
    cout << "Enter number of flowers: ";
    cin >> n;

    vector<int> bloomDay(n);
    cout << "Enter bloom days of flowers: ";
    for (int i = 0; i < n; i++) {
        cin >> bloomDay[i];
    }

    cout << "Enter number of bouquets (m): ";
    cin >> m;
    cout << "Enter flowers per bouquet (k): ";
    cin >> k;

    Solution sol;

    // Use optimized approach
    int ans = sol.minDays(bloomDay, m, k);
    cout << "Minimum days required (Optimized): " << ans << endl;

    // Keep brute force for revision/future reference
    // Uncomment if you want to test brute force
    // int ansBrute = sol.bruteForce(bloomDay, m, k);
    // cout << "Minimum days required (Brute Force): " << ansBrute << endl;

    return 0;
}

