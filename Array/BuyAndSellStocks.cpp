#include <bits/stdc++.h>
using namespace std;

int BuyAndSellStocks(vector<int> &arr) {
    int maxProfit = 0;
    int mini = arr[0];

    for(int num : arr) {
        int cost = num - mini;
        maxProfit = max(maxProfit , cost);
        mini = min(mini , num);
    }
    return maxProfit;
}

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int maxProfit = BuyAndSellStocks(arr);
    cout << maxProfit << endl;
    return 0;
}
