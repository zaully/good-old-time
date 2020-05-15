#pragma once

#include <vector>

using namespace std;

class Solution {
public:
    int maxStudents(vector<vector<char>>& seats) {
        auto m = seats.size();
        auto n = seats[0].size();
        vector<int> availableSeats;
        for (auto i = 0; i < m; i++) {
            auto cur = 0;
            for (auto j = 0; j < n; j++) {
                cur = cur * 2 + (seats[i][j] == '.');
                int avail = seats[i][j] == '.';
                cout << avail;
            }
            cout << endl;
            availableSeats.push_back(cur);
        }
        vector<vector<int>> f(m + 1, vector<int>(1 << n, -1));
        return 0;
    }
};

void run() {
    Solution sol;
    vector<vector<char>> input = {{'#', '.', '#', '#', '.', '#'}, {'.', '#', '#', '#', '#', '.'}, {'#', '.', '#', '#', '.', '#'}};
    sol.maxStudents(input);
}
