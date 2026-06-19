#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
====================================================
APPROACH 1 : BRUTE FORCE
====================================================

INTUITION:
Try every possible buying day.
For each buy day, check all future selling days.
Compute profit = sell - buy.

Example:
[7,1,5,3,6,4]

Buy at 1
Sell at 5 → Profit = 4
Sell at 6 → Profit = 5 ← maximum

Time: O(N²)
Space: O(1)
*/

int bruteForce(vector<int>& prices) {
    int n = prices.size();
    int maxProfit = 0;

    for (int buy = 0; buy < n; buy++) {

        // Check all future sell days
        for (int sell = buy + 1; sell < n; sell++) {

            int profit = prices[sell] - prices[buy];

            maxProfit = max(maxProfit, profit);
        }
    }

    return maxProfit;
}


/*
====================================================
APPROACH 2 : OPTIMAL (TRACK MINIMUM PRICE)
====================================================

INTUITION:
We don't need to check all pairs.

Keep:
minPrice → lowest stock seen till now

At every day:
profit = currentPrice - minPrice

Update answer.

Example:
[7,1,5,3,6,4]

Day 1:
min=7

Day 2:
min=1

Day 3:
profit=5-1=4

Day 5:
profit=6-1=5

Answer = 5

Time: O(N)
Space: O(1)
*/

int optimal(vector<int>& prices) {

    int minPrice = INT_MAX;
    int maxProfit = 0;

    for (int price : prices) {

        // Update lowest buy price
        minPrice = min(minPrice, price);

        // Profit if sold today
        int profit = price - minPrice;

        maxProfit = max(maxProfit, profit);
    }

    return maxProfit;
}


/*
====================================================
APPROACH 3 : DP STYLE (STATE TRANSITION)
====================================================

INTUITION:

Think in 2 states:

buy → best buying opportunity
sell → maximum profit

Transition:

buy = min(buy, currentPrice)

sell = max(
        previousProfit,
        currentPrice - buy
      )

This is logically same as optimal.

Time: O(N)
Space: O(1)
*/

int dpApproach(vector<int>& prices) {

    int buy = INT_MAX;
    int sell = 0;

    for (int price : prices) {

        // Best buying price
        buy = min(buy, price);

        // Best profit
        sell = max(sell, price - buy);
    }

    return sell;
}


/*
====================================================
APPROACH 4 : KADANE'S ALGORITHM
====================================================

INTUITION:

Convert prices into daily changes.

Example:

Prices:
[7,1,5,3,6,4]

Differences:
[-6,+4,-2,+3,-2]

Now question becomes:
Find maximum sum subarray.

Kadane:
If sum becomes negative → reset.

Time: O(N)
Space: O(1)
*/

int kadane(vector<int>& prices) {

    int currentProfit = 0;
    int bestProfit = 0;

    for (int i = 1; i < prices.size(); i++) {

        // Daily profit change
        currentProfit += prices[i] - prices[i - 1];

        // Reset if negative
        if (currentProfit < 0)
            currentProfit = 0;

        bestProfit = max(bestProfit, currentProfit);
    }

    return bestProfit;
}


/*
====================================================
MAIN FUNCTION
====================================================
*/

int main() {

    int n;

    cout << "Enter number of days: ";
    cin >> n;

    vector<int> prices(n);

    cout << "Enter stock prices:\n";

    for (int i = 0; i < n; i++) {
        cin >> prices[i];
    }

    cout << "\n===== RESULTS =====\n";

    cout << "Brute Force Profit : "
         << bruteForce(prices) << endl;

    cout << "Optimal Profit     : "
         << optimal(prices) << endl;

    cout << "DP Style Profit    : "
         << dpApproach(prices) << endl;

    cout << "Kadane Profit      : "
         << kadane(prices) << endl;

    return 0;
}