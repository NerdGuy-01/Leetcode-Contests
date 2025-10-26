Q 1 : You are given a string s of length n consisting of lowercase English letters.

You must perform exactly one operation by choosing any integer k such that 1 <= k <= n and either:

reverse the first k characters of s, or
reverse the last k characters of s.
Return the lexicographically smallest string that can be obtained after exactly one such operation.

A string a is lexicographically smaller than a string b if, at the first position where they differ, a has a letter that appears earlier in the alphabet than the corresponding letter in b. If the first min(a.length, b.length) characters are the same, then the shorter string is considered lexicographically smaller.

 // my code which is ofcourse wrong 
  class Solution {
public:
    string lexSmallest(string s) {
        string result  = "";
        int n = s.length();
        int k = n;
        int freq[26] = {0};
        for(char ch:s) freq[ch-'0']++;
        int i =0;
        while(k>=0 && i<n){
            string temp  = s.substr(0,k);
            reverse(temp.begin(),temp.end());
            if(temp[i-'0'] < s[i-'0']){
                result.push_back(temp[i]);
            }
            i++;
            k--;
        }
        return result ;
    }
};

// right code 
class Solution {
public:
    string lexSmallest(string s) {
        int n = s.size();
        string ans = s;

        // Try reversing first k characters
        for (int k = 1; k <= n; k++) {
            string temp = s;
            reverse(temp.begin(), temp.begin() + k);
            ans = min(ans, temp);
        }

        // Try reversing last k characters
        for (int k = 1; k <= n; k++) {
            string temp = s;
            reverse(temp.end() - k, temp.end());
            ans = min(ans, temp);
        }

        return ans;
    }
};


Q :2 You are given two positive integers num and sum.

A positive integer n is good if it satisfies both of the following:

The number of digits in n is exactly num.
The sum of digits in n is exactly sum.
The score of a good integer n is the sum of the squares of digits in n.

Return a string denoting the good integer n that achieves the maximum score. If there are multiple possible integers, return the maximum ​​​​​​​one. If no such integer exists, return an empty string.

 // code 
class Solution {
public:
    string maxSumOfSquares(int num, int sum) {
        // Impossible case: sum too small or too large
        if (sum < 1 || sum > 9 * num) return "";

        string result = "";
        for (int i = 0; i < num; i++) {
            // Try digits from 9 to 0 for max score
            for (int d = 9; d >= 0; d--) {
                int remaining = sum - d;
                int remainingDigits = num - i - 1;

                // Check if remaining digits can fill up the rest
                if (remaining >= 0 && remaining <= 9 * remainingDigits) {
                    result.push_back('0' + d);
                    sum -= d;
                    break;
                }
            }
        }

        if (sum != 0) return "";  // not possible to form
        return result;
    }
};
