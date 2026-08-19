#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {

    // INTUITION:
    // 1. Sort all intervals based on their starting point.
    //    Example: [1,3], [2,6], [8,10], [9,12]
    //
    // 2. After sorting, we only need to compare the current
    //    interval with the last interval in our answer.
    //
    // 3. If current interval starts BEFORE or AT the end of
    //    the last interval, they overlap.
    //    Example: [1,3] and [2,6]
    //    Since 2 <= 3, they overlap.
    //
    // 4. Merge them by extending the ending point:
    //    [1,3] + [2,6] -> [1,6]
    //
    // 5. If current interval starts AFTER the end of the
    //    last interval, there is no overlap.
    //    So simply add it to the answer.

    if (intervals.empty()) {
        return {};
    }

    // Step 1: Sort intervals by starting point
    sort(intervals.begin(), intervals.end());

    vector<vector<int>> ans;

    // Add the first interval
    ans.push_back(intervals[0]);

    // Step 2: Process remaining intervals
    for (int i = 1; i < intervals.size(); i++) {

        // Current interval
        int currentStart = intervals[i][0];
        int currentEnd = intervals[i][1];

        // Last interval already present in answer
        int lastStart = ans.back()[0];
        int lastEnd = ans.back()[1];

        // Overlapping intervals
        if (currentStart <= lastEnd) {

            // Extend the end of the last interval
            // Example:
            // [1,6] and [4,8] -> [1,8]
            ans.back()[1] = max(lastEnd, currentEnd);
        }

        // Non-overlapping intervals
        else {

            // Simply add the current interval
            ans.push_back(intervals[i]);
        }
    }

    return ans;
}

int main() {

    vector<vector<int>> intervals = {
        {1, 3},
        {2, 6},
        {8, 10},
        {9, 12}
    };

    vector<vector<int>> result = mergeIntervals(intervals);

    cout << "Merged Intervals:" << endl;

    for (auto interval : result) {
        cout << "[" << interval[0] << ", " << interval[1] << "] ";
    }

    return 0;
}