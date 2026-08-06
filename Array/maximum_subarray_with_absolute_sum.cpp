class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int n = nums.size();
        int sum = nums[0];
        int maxSum = nums[0];

        for(int i = 1; i < n; i++) {
            sum = max(nums[i], nums[i] + sum);
            maxSum = max(sum, maxSum);
        }

        int minSum = nums[0];
        int nSum = nums[0];

        for(int i = 1; i < n; i++) {
            nSum = min(nums[i], nSum + nums[i]);
            minSum = min(minSum, nSum);
        }

        if(abs(minSum) >= abs(maxSum)) {
            return abs(minSum);
        } 

        return abs(maxSum);
    }
};