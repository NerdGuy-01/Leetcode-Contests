 1. You are given a string s consisting of lowercase English letters.

The frequency group for a value k is the set of characters that appear exactly k times in s.

The majority frequency group is the frequency group that contains the largest number of distinct characters.

Return a string containing all characters in the majority frequency group, in any order. If two or more frequency groups tie for that largest size, pick the group whose frequency k is larger.



   // Solution  Tc and SC are O(N);
   class Solution {
public:
    string majorityFrequencyGroup(string s) {
        int freq[26] = {0};
        for(char ch:s) freq[ch - 'a']++;
        int unique[101] = {}; int majority = 1; // An array unique tracks the count of counts. unique[k] will store how many different characters appear exactly $k$ times. For example, if both 'a' and 'c' appear 5 times, then unique[5] will be 2.
        for(int i =0 ;i<26 ; i++){
            if(freq[i]==0) continue;
            if(++unique[freq[i]]>unique[majority] || unique[freq[i]]==unique[majority] && freq[i]>majority)  majority =  freq[i];
        }
        string res = "";
        for(int i  = 0; i<26 ; i++){
            if(freq[i]==majority) res.push_back((char)i + 'a');
        }
        return res;
    }
};


Q 2 : You are climbing a staircase with n + 1 steps, numbered from 0 to n.

You are also given a 1-indexed integer array costs of length n, where costs[i] is the cost of step i.

From step i, you can jump only to step i + 1, i + 2, or i + 3. The cost of jumping from step i to step j is defined as: costs[j] + (j - i)2 // square

You start from step 0 with cost = 0.

Return the minimum total cost to reach step n.

// Solution 
// 1 Index means Array start from 1 
class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        vector<int> dp(n+1, INT_MAX);
        dp[0]=0;
        for (int i=1; i<=n; ++i) {
            for (int j=1; j<=3 && j<=i; ++j) {
                dp[i]=min(dp[i], dp[i-j]+costs[i-1]+j*j);
            }
        }
        return dp[n];
    }
};
