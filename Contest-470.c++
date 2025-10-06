 Q 2 : You are given an integer array nums.

Return the length of the longest subsequence in nums whose bitwise XOR is non-zero. If no such subsequence exists, return 0


In this questions three cases arrives 
1. If all elements are zero return 0 (no subsset)
  2. If XOR  of all element is 0 return n-1 (why because then it means all xor are zero but if we take less than all it will not be zero )
3. Return n ( Total XOR is non-zero)


Code : 
class Solution {
public:
    int longestSubsequence(vector<int>& nums) {
        int n = nums.size();
        int xo =0,r=0;      // xor is predefined variable
        for(auto x:nums) xo^=x,r|=x;   //  this r|=x does the or operator which basically check if all the element are 0 or not like a|a =0 a|b = something but not zero
        if(!r) return 0;   
        if(!xo) return n-1;
        return n ;
    }
};



Q 3: You are given a string s consisting of '(' and ')', and an integer k.

A string is k-balanced if it is exactly k consecutive '(' followed by k consecutive ')', i.e., '(' * k + ')' * k.

For example, if k = 3, k-balanced is "((()))".

You must repeatedly remove all non-overlapping k-balanced substrings from s, and then join the remaining parts. Continue this process until no k-balanced substring exists.

Return the final string after all possible removals.


 STEPS -> 
 1. Compress the value of input string
2. Create a stack of pairs
3. Add each compressed  value to stack one by one 
 3.1 After adding  while(st.size()>2) -> then compress top 2 elements, if they are same symbol merge them then combine the value 
   3.2 If there are differnce and opening followed by closing -> check how many k can be removed to do it, if any element is 0 donot add back, if they are closing followed by opened -> break

 4. Create ans string =""
5. Insert (decompress ) the element of stack ( in reverse order)
6. return ans string 

T.C - > o(N)


 Code -> 
 class Solution {
public:
    string removeSubstring(string s, int k) {
        vector<int> counts; // counts of consecutive '(' or ')'
        char prev = 0;      // initialize with 0, not ""

        // Group consecutive '(' or ')' counts
        for (char x : s) {
            if (!counts.empty() && x == prev)
                counts.back()++;
            else
                counts.push_back(1);
            prev = x;
        }

        stack<pair<int, int>> st;  // {type, count} where type=1 for '(' and -1 for ')'
        int type = (s[0] == '(' ? 1 : -1);

        for (auto x : counts) {
            st.push({type, x});
            type *= -1;  // alternate between '(' and ')'

            while (st.size() >= 2) {
                auto [at, av] = st.top(); st.pop();
                auto [bt, bv] = st.top(); st.pop();

                if (at == bt) { 
                    st.push({at, av + bv}); 
                    continue; 
                }

                if (at != -1) {
                    st.push({bt, bv});
                    st.push({at, av});
                    break;
                }

                int v = min(av, bv) / k;
                av -= k * v;
                bv -= k * v;

                if (bv) st.push({bt, bv});
                if (av) st.push({at, av});
                if (v == 0) break;
            }
        }

        string ans = "";
        while (!st.empty()) {
            auto [type, x] = st.top(); st.pop();
            while (x--) {
                ans.push_back(type == 1 ? '(' : ')');
            }
        }

        reverse(ans.begin(), ans.end());
        return ans;
    }
};

 



