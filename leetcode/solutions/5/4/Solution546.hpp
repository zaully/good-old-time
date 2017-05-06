#pragma once

#include <vector>
#include <set>

using std::vector;

class Solution {
  public:
    void run() {
        vector<int> question = {1, 2, 3, 2, 1, 1, 1, 2, 3, 2, 1, 1, 1, 2, 3, 2};
        for (auto i = 0; i < 1; i++) {
            auto score = removeBoxes(question);
            printf("%i\n", score);
        }
    }

    int removeBoxes(vector<int> &boxes) {
        auto count = static_cast<int>(boxes.size());
        int scores[100][100][100];
        return calc_best_score(boxes, scores, 0, count - 1, 0);
    }

    int calc_best_score(vector<int> &boxes, int scores[100][100][100], int l,
                        int r, int c) {
        /*
         to calculate general senarios:
         1, 2, 2, 2, 3...4, 2, 5
            ^l(c=0)            ^r
         by moving l, c increases
         1, 2, 2, 2, 3...4, 2, 5
                  ^l(c=2)      ^r
         l = left
         c = consecutive_count
         r = right
         */
        if (l > r) return 0;
        if (scores[l][r][c]) return scores[l][r][c];
        while (l < r && boxes[l] == boxes[l + 1]) {
            l++;
            c++;
        }
        scores[l][r][c] =
                calc_best_score(boxes, scores, l + 1, r, 0) + (c + 1) * (c + 1);

        /*
         1, 2, 2, 2, 3...4, 2, 5
                  ^l(c=2)   ^i ^r
         */
        for (auto i = r; i > l; i--) {
            if (boxes[i] == boxes[l]) {
                scores[l][r][c] = std::max(
                        scores[l][r][c],
                        calc_best_score(boxes, scores, l + 1, i - 1, 0) +
                                calc_best_score(boxes, scores, i, r, c + 1));
            }
        }
        return scores[l][r][c];
    }
};
