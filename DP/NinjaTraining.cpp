#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    /*
    ---------------------------------------------------------
    APPROACH 1 : MEMOIZATION (Top-Down Dynamic Programming)
    ---------------------------------------------------------

    INTUITION:

    The ninja has 3 tasks to choose from every day.
    But he cannot perform the same task on two consecutive days.

    So at every day we must decide which task to perform today,
    while remembering which task was performed on the previous day.

    STATE DEFINITION:

        solve(day, lastTask)

    day      -> current day we are solving
    lastTask -> task performed on the previous day

    Base Case:
    If day == 0, we simply choose the maximum task among the tasks
    that are NOT equal to lastTask.

    Transition:

    For the current day we try all 3 tasks:
        if(task != lastTask)

    points = mat[day][task] + solve(day-1, task)

    We take the maximum of all valid tasks.

    Since many states repeat, we store results in dp table.

    TIME COMPLEXITY
    O(N * 4 * 3)

    SPACE COMPLEXITY
    O(N * 4) + recursion stack
    */

    int solve(vector<vector<int>>& mat, int day, int lastTask, vector<vector<int>> &dp) {

        if(day == 0) {
            int maxi = 0;

            for(int task = 0; task < 3; task++) {
                if(task != lastTask) {
                    maxi = max(maxi, mat[0][task]);
                }
            }

            return maxi;
        }

        if(dp[day][lastTask] != -1)
            return dp[day][lastTask];

        int maxi = 0;

        for(int task = 0; task < 3; task++) {

            if(task != lastTask) {

                int merit = mat[day][task] + solve(mat, day-1, task, dp);

                maxi = max(maxi, merit);
            }
        }

        return dp[day][lastTask] = maxi;
    }


    int maximumPointsMemo(vector<vector<int>>& mat) {

        int n = mat.size();

        vector<vector<int>> dp(n, vector<int>(4, -1));

        return solve(mat, n-1, 3, dp);
    }



    /*
    ---------------------------------------------------------
    APPROACH 2 : TABULATION (Bottom-Up Dynamic Programming)
    ---------------------------------------------------------

    INTUITION:

    Instead of solving the problem recursively,
    we build the solution from smaller subproblems.

    We define a DP table:

        dp[day][last]

    day  -> current day
    last -> task performed on the previous day

    Meaning:

        dp[day][last] =
        Maximum points we can get till "day"
        if the previous task was "last".

    BASE INITIALIZATION:

    For day = 0 we compute the best possible task
    while avoiding the task equal to "last".

    TRANSITION:

    For every day and every last task:

        try all tasks
        but skip the one equal to "last"

    merit = mat[day][task] + dp[day-1][task]

    Take maximum.

    FINAL ANSWER:

        dp[n-1][3]

    because "3" means no restriction on the previous task.

    TIME COMPLEXITY
    O(N * 4 * 3)

    SPACE COMPLEXITY
    O(N * 4)
    */

    int maximumPointsTab(vector<vector<int>>& mat) {

        int n = mat.size();

        vector<vector<int>> dp(n, vector<int>(4, 0));

        dp[0][0] = max(mat[0][1], mat[0][2]);
        dp[0][1] = max(mat[0][0], mat[0][2]);
        dp[0][2] = max(mat[0][0], mat[0][1]);
        dp[0][3] = max(mat[0][0], max(mat[0][1], mat[0][2]));

        for(int day = 1; day < n; day++) {

            for(int last = 0; last < 4; last++) {

                dp[day][last] = 0;

                for(int task = 0; task < 3; task++) {

                    if(task != last) {

                        int merit = mat[day][task] + dp[day-1][task];

                        dp[day][last] = max(dp[day][last], merit);
                    }
                }
            }
        }

        return dp[n-1][3];
    }



    /*
    ---------------------------------------------------------
    APPROACH 3 : SPACE OPTIMIZED DP
    ---------------------------------------------------------

    INTUITION:

    If we observe the tabulation solution carefully,
    we see that:

        dp[day] depends only on dp[day-1]

    Therefore storing the entire 2D table is unnecessary.

    We only keep the previous day's result.

    So we use:

        dp[4]

    representing the previous day's state.

    For each new day we compute results into a temporary
    array and then update dp.

    This reduces space complexity from:

        O(N * 4)  →  O(4)

    TIME COMPLEXITY
    O(N * 4 * 3)

    SPACE COMPLEXITY
    O(4)
    */

    int maximumPointsSpace(vector<vector<int>>& mat) {

        int n = mat.size();

        vector<int> dp(4, 0);

        dp[0] = max(mat[0][1], mat[0][2]);
        dp[1] = max(mat[0][0], mat[0][2]);
        dp[2] = max(mat[0][0], mat[0][1]);
        dp[3] = max(mat[0][0], max(mat[0][1], mat[0][2]));

        for(int day = 1; day < n; day++) {

            vector<int> temp(4, 0);

            for(int last = 0; last < 4; last++) {

                for(int task = 0; task < 3; task++) {

                    if(task != last) {

                        int merit = mat[day][task] + dp[task];

                        temp[last] = max(temp[last], merit);
                    }
                }
            }

            dp = temp;
        }

        return dp[3];
    }
};



int main() {

    int n;

    cout << "Enter number of days: ";
    cin >> n;

    vector<vector<int>> mat(n, vector<int>(3));

    cout << "Enter merit points for 3 tasks each day:\n";

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < 3; j++) {
            cin >> mat[i][j];
        }
    }

    Solution obj;

    cout << "\nMaximum Points (Memoization): "
         << obj.maximumPointsMemo(mat) << endl;

    cout << "Maximum Points (Tabulation): "
         << obj.maximumPointsTab(mat) << endl;

    cout << "Maximum Points (Space Optimized): "
         << obj.maximumPointsSpace(mat) << endl;

}