#pragma once

#include <vector>

using std::vector;

class Solution238 {
  public:
    void run() {
        vector<int> example = {2, 3, 4, 5};
        auto test = productExceptSelf(example);
        for (const auto &item : test) {
            printf("%i ", item);
        }
        printf("\n");
    }
    
    vector<int> productExceptSelf(vector<int>& nums) {
        /* 
         * without division, O(n) time, O(1) space
         * 1. use the result array for temp storage
         * 2. calculate productFromEnd(stored in result) 
         * 3. use productFromStart and productFromEnd to calculate current value
         * 4. calculate productFromStart while putting final values to result
         * 5. beware of index
         */
        
        // 1.
        auto result = nums;
        
        // 2.
        for (auto i = nums.size() - 2; i > 0; i--) {
            result[i] *= result[i + 1];
        }
        
        auto productFromStart = 1;
        for (auto i = 0; i < nums.size(); i++) {
            if (i < nums.size() - 1) {
                // 3.
                result[i] = productFromStart * result[i + 1];
                // 4.
                productFromStart *= nums[i];
            } else {
                // 5.
                result[i] = productFromStart;
            }
        }
        return result;
    }
};
