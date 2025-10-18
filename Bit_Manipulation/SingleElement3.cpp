#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    vector<int> twoOddNum(vector<int>& arr) {
        int n = arr.size();

        // 🧠 Intuition:
        // In the given array, every number appears an even number of times
        // except TWO numbers which appear an odd number of times.
        // Example: [4, 2, 4, 5, 2, 3, 3, 1]
        // Odd occurring numbers are: 5 and 1

        // Step 1️⃣: XOR all elements
        // Why? Because numbers appearing even number of times will cancel out
        // (x ^ x = 0), leaving XOR = (odd1 ^ odd2)
        int XOR = arr[0];
        for (int i = 1; i < n; i++) {
            XOR ^= arr[i];
        }

        // After XOR, we now have XOR = num1 ^ num2
        // Example: XOR = 5 ^ 1 = 4  (in binary: 101 ^ 001 = 100)

        // Step 2️⃣: Find the rightmost set bit in XOR
        // This bit differs between num1 and num2 (i.e., one has 1, the other has 0)
        // We'll use this bit to divide numbers into two groups.
        int rightMostSetBit = ((XOR & (XOR - 1)) ^ XOR);

        // Step 3️⃣: Divide numbers into two groups and XOR separately
        // Group 1: Numbers where this bit is SET
        // Group 2: Numbers where this bit is NOT set
        //
        // Numbers that are same will again cancel out within their group,
        // and each group will finally contain one of the odd occurring numbers.
        int num1 = 0;
        int num2 = 0;
        for (int i = 0; i < n; i++) {
            if ((rightMostSetBit & arr[i]) != 0) {
                num1 ^= arr[i];
            } else {
                num2 ^= arr[i];
            }
        }

        // Step 4️⃣: Return result in decreasing order
        if (num1 > num2) {
            return {num1, num2};
        }
        return {num2, num1};
    }
};

int main() {
    // 🔹 INPUT FORMAT:
    // First line: an integer n (size of array)
    // Second line: n space-separated integers (array elements)
    //
    // Example:
    // Input:
    // 8
    // 4 2 4 5 2 3 3 1
    //
    // Output:
    // Numbers with odd occurrences: 5 1

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    Solution obj;
    vector<int> ans = obj.twoOddNum(arr);

    cout << "Numbers with odd occurrences: ";
    for (int x : ans) cout << x << " ";
    cout << endl;

    return 0;
}
