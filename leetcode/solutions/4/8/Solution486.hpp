#pragma once

#include <vector>

using std::vector;

class Solution486 {
  public:
    void run() {
        vector<int> nums = {1, 5, 2};
        PredictTheWinner(nums);
    }

    bool PredictTheWinner(vector<int> &nums) {
        /*
         * use DP to calculate every sub-segment until the whole array
         * 1. initialize an N-object array to store balance. balance will be the
         * differences between player A and B
         *
         * 2. calculate 1 element, then 2, 3... until reaches the whole array
         *
         * 3. when calculate subSolution[i] in iteration #j
         *    3a. player A will aim for higher balance while B aims for lower
         *    3b. every subSolution[i] is calculated by last subSolution[i],
         * subSolution[i + 1] and nums[i] and nums[i + nums.size() -
         * calculateSize], where nums provide the new elements from both ends
         *
         * 4. when calculateSize reaches 0, subSolution[0] is the best possible
         * balance for A.
         */
        
        auto calculateSize = nums.size();
        
        // 1.
        vector<int> subSolutions(calculateSize);
        
        while (calculateSize > 0) {
        
            // 3a.
            auto pickHigher = calculateSize % 2 == 1;
            
            // 2.
            for (auto i = 0; i < calculateSize; i++) {
                if (subSolutions.size() == calculateSize) {
                    subSolutions[i] = pickHigher ? nums[i] : -nums[i];
                } else {
                    // 3b.
                    auto score1 = pickHigher ? nums[i] : -nums[i];
                    auto score2 = nums[i + nums.size() - calculateSize];
                    score2 = pickHigher ? score2 : -score2;
                    score1 += subSolutions[i + 1];
                    score2 += subSolutions[i];
                    subSolutions[i] =
                            (pickHigher ? score1 < score2 : score1 > score2)
                                    ? score2
                                    : score1;
                }
            }
            // 2.
            calculateSize--;
        }
        
        // 4.
        return subSolutions.size() <= 0 || subSolutions[0] >= 0;
    }
};
