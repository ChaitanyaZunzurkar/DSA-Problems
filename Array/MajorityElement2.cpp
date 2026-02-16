#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter size of array: ";
    cin >> n;

    vector<int> nums(n);
    cout << "Enter array elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }

    // ================= INTUITION =================
    // For an array of size n:
    // There can be AT MOST 2 elements that appear more than floor(n/3) times.
    //
    // Why?
    // If there were 3 such elements, each appearing more than n/3 times,
    // their total count would exceed n → impossible.
    //
    // So we try to find 2 possible candidates using a voting mechanism.
    // Similar elements increase votes, different elements cancel votes.
    // =============================================

    int candidate1 = 0, candidate2 = 0;
    int count1 = 0, count2 = 0;

    // -------- First Pass: Find potential candidates --------
    for (int num : nums) {
        if (num == candidate1) {
            count1++;
        } 
        else if (num == candidate2) {
            count2++;
        } 
        else if (count1 == 0) {
            candidate1 = num;
            count1 = 1;
        } 
        else if (count2 == 0) {
            candidate2 = num;
            count2 = 1;
        } 
        else {
            // Different element cancels out one vote from both candidates
            count1--;
            count2--;
        }
    }

    // -------- Second Pass: Verify actual frequencies --------
    count1 = 0;
    count2 = 0;

    for (int num : nums) {
        if (num == candidate1) count1++;
        else if (num == candidate2) count2++;
    }

    // -------- Output the result --------
    cout << "Majority elements (> n/3 times): ";

    bool found = false;
    if (count1 > n / 3) {
        cout << candidate1 << " ";
        found = true;
    }
    if (count2 > n / 3) {
        cout << candidate2 << " ";
        found = true;
    }

    if (!found) {
        cout << "None";
    }

    cout << endl;
    return 0;
}
