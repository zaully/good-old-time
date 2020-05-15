#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:

    bool isMatch(string s, string p) {
        auto m = s.size();
        auto n = p.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
        dp[0][0] = 1;
        return search(s, p, dp, m, n) == 1;
    }

    int search(string &s, string &p, vector<vector<int>> &dp, size_t i, size_t j) {
        if (dp[i][j] >= 0) {
            return dp[i][j];
        }
        if (i == 0) {
            if (j == 1) {
                dp[i][j] = 0;
            } else if (p[j - 1] == '*') {
                dp[i][j] = search(s, p, dp, i, j - 2);
            }
            return dp[i][j];
        }
        if (j == 0) {
            dp[i][j] = 0;
            return 0;
        }
        auto sPos = i - 1;
        auto pPos = j - 1;
        auto target = s[sPos];
        if (p[pPos] == '*') {
            if (pPos < 1 || p[pPos - 1] == '*') {
                dp[i][j] = 0;
                return 0;
            } 

            auto pat = p[pPos - 1];
            if (pat == '.' || pat == target) {
                if (i > 0) {
                    auto res = search(s, p, dp, i - 1, j);
                    if (res == 1) {
                        dp[i][j] = 1;
                    }
                }

                if (i > 0 && j > 1) {
                    auto res = search(s, p, dp, i - 1, j - 2);
                    if (res == 1) {
                        dp[i][j] = 1;
                    }
                }
            }
            if (j > 1) {
                auto res = search(s, p, dp, i, j - 2);
                if (res == 1) {
                    dp[i][j] = 1;
                }
            }
        } else if (target == p[pPos] || p[pPos] == '.') {
            if (i > 0 && j > 0) {
                dp[i][j] = search(s, p, dp, i - 1, j - 1);
            }
        }
        if (dp[i][j] < 0) {
            dp[i][j] = 0;
        }
        return dp[i][j];
    }

    void run() {
        vector<string> inputs = {
            "aab", "c*a*b",
            "mississippi", "mis*is*p*.",
            "ab", ".*",
            "aa", "a",
            "aa", "a*",
            "abcd", ".*",
        };
        for (auto i = 0; i < inputs.size(); i += 2) {
            auto ans = isMatch(inputs[i], inputs[i + 1]);
            cout << "answer: " << ans << endl;
        }
    }
};
