//
//  Solution1347.hpp
//  leetcode
//
//  Created by Vince Liang on 2020-02-18.
//  Copyright © 2020 crawley. All rights reserved.
//

#pragma once

static auto fast=[]{ios_base::sync_with_stdio(false);cin.tie(nullptr);return 0;}();

class Solution {
public:
    int minSteps(string s, string t) {
        int total[256] = { 0 };
        for (auto i = 0; i < s.size(); i++) {
            total[s[i]]++;
        }
        for (auto i = 0; i < t.size(); i++) {
            total[t[i]]--;
        }
        auto ans = 0;
        for (auto value : total) {
            if (value > 0) {
                ans += value;
            }
        }
        return ans;
    }
};
