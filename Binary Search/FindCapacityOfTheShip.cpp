#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to find the minimum capacity of the ship
    int shipWithinDays(vector<int>& weights, int days) {
        int sum = 0;         // Total sum of weights (max possible capacity)
        int n = weights.size();
        int result = INT_MAX; // To store the minimum valid capacity
        int maxi = INT_MIN;   // Maximum single weight (min possible capacity)

        // Calculate total sum and maximum weight
        for(int i = 0; i < n; i++) {
            sum += weights[i];
            maxi = max(maxi, weights[i]);
        }

        // Binary search between maximum weight and total sum
        int low = maxi;  // Minimum capacity must be at least the heaviest package
        int high = sum;  // Maximum capacity can be sum of all weights

        while (low <= high) {
            int mid = low + (high - low) / 2;  // Current capacity to test
            int numOfDays = 1;                 // Start with 1 day
            int load = 0;                      

            // Simulate loading weights with current capacity
            for(int j = 0; j < n; j++) {
                if(load + weights[j] > mid) {
                    // Need an extra day if adding this weight exceeds capacity
                    numOfDays += 1;
                    load = 0;
                }
                load += weights[j];
            }

            // If we can ship within given days, try smaller capacity
            if(numOfDays <= days) {
                result = mid;
                high = mid - 1;
            } else {
                // Otherwise, increase capacity
                low = mid + 1;
            }
        }

        return result;
    }
};

int main() {
    int n, days;
    cout << "Enter number of packages: ";
    cin >> n;
    vector<int> weights(n);
    
    cout << "Enter weights of the packages: ";
    for(int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    cout << "Enter number of days to ship: ";
    cin >> days;

    Solution sol;
    int minCapacity = sol.shipWithinDays(weights, days);

    cout << "Minimum ship capacity required: " << minCapacity << endl;
    return 0;
}
