#include <bits/stdc++.h>
using namespace std;

int maxScore(vector<int>& cardPoints, int k) {

    int n = cardPoints.size();
    int lsum = 0;

    // STEP 1:
    // Take the first k cards from the left side
    // This assumes we initially select all k cards from the left
    for(int i = 0; i < k; i++) {
        lsum += cardPoints[i];
    }

    int maxSum = lsum;
    int rsum = 0;
    int rindex = n - 1;

    /*
       STEP 2:
       We will gradually replace cards taken from the left
       by taking cards from the right.

       What we do:

       1) Remove the rightmost taken card from left side.
       2) Add one new card picked from right side.
       3) Update max possible score at each step.

       This tries all valid combinations of picking
       i cards from left and k-i cards from right.
    */
    for(int i = k - 1; i >= 0; i--) {
        lsum = lsum - cardPoints[i];   // remove last chosen left card
        rsum = rsum + cardPoints[rindex]; // include one card from right
        rindex = rindex - 1;

        maxSum = max(maxSum, lsum + rsum);
    }

    return maxSum;
}

int main() {

    int n, k;
    cin >> n >> k;

    vector<int> cardPoints(n);

    // reading input
    for(int i = 0; i < n; i++) {
        cin >> cardPoints[i];
    }

    cout << maxScore(cardPoints, k);
    
    return 0;
}
