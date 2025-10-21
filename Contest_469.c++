
1. Questions ->
  You are given a positive integer n.

A positive integer is a base-10 component if it is the product of a single digit from 1 to 9 and a non-negative power of 10. For example, 500, 30, and 7 are base-10 components, while 537, 102, and 11 are not.

Express n as a sum of only base-10 components, using the fewest base-10 components possible.

Return an array containing these base-10 components in descending order.

  // Solution
  class Solution {
public:
    vector<int> decimalRepresentation(int n) {
        vector<int>result;
        int power  = 0;
        while(n!=0){
            int digit = n%10;
            if(digit!=0){
                int component = digit * pow(10,power);
                result.push_back(component);
            }
            n/=10;
            power++;
        }
          sort(result.rbegin(), result.rend()); // to convert in descending order
    return result;
    }
};

2. Question ->
  You are given an integer array nums.

Split the array into exactly two subarrays, left and right, such that left is strictly increasing and right is strictly decreasing.

Return the minimum possible absolute difference between the sums of left and right. If no valid split exists, return -1.

  // Soutions -> I tried to use binary search but it went in vain

  // less optimized 
  #include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long splitArray(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return -1;

        vector<long long> prefix(n);
        prefix[0] = nums[0];
        for (int i = 1; i < n; i++)
            prefix[i] = prefix[i - 1] + nums[i];

        vector<bool> inc(n, false), dec(n, false);

        // Increasing prefix
        inc[0] = true;
        for (int i = 1; i < n; i++) {
            if (nums[i] > nums[i - 1] && inc[i - 1])
                inc[i] = true;
        }

        // Decreasing suffix
        dec[n - 1] = true;
        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] > nums[i + 1] && dec[i + 1])
                dec[i] = true;
        }

        long long ans = LLONG_MAX;
        bool valid = false;

        // Try all split points
        for (int i = 0; i < n - 1; i++) {
            if (inc[i] && dec[i + 1]) {
                long long leftSum = prefix[i];
                long long rightSum = prefix[n - 1] - prefix[i];
                ans = min(ans, abs(leftSum - rightSum));
                valid = true;
            }
        }

        return valid ? ans : -1;
    }
};


// more optimized 
class Solution {
public:
    long long splitArray(vector<int>& nums) {
        int n = nums.size();
        vector<bool> split(n, false);
        split[n-1] = true;

        // Build decreasing suffix
        for(int i = n-2; i >= 0; i--){
            if(nums[i] > nums[i+1]) split[i] = true;
            else break;
        }

        long long sum = accumulate(nums.begin(), nums.end(), 0LL);
        long long ans = 1e18, psum = 0;

        for(int i = 0; i < n-1; i++){
            psum += nums[i]; // left sum
            if(i > 0 && nums[i] <= nums[i-1]) break; // left not strictly increasing
            if(!split[i+1]) continue; // right not strictly decreasing

            ans = min(ans, abs(sum - 2*psum));
        }

        return ans == 1e18 ? -1 : ans;
    }
};
