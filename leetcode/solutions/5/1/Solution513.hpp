#pragma once

#include <stack>
#include <queue>

#include "../../../predefined/TreeNode.hpp"

class Solution513 {
  public:
    void run() {
        auto root = createTest1();
        printf("%i", findBottomLeftValue(root));
        delete root;
    }
  
    int findBottomLeftValue(TreeNode* root) {
        std::queue<TreeNode *> queue;
        queue.push(root);
        auto result = 0;
        while (!queue.empty()) {
            auto cur = queue.front();
            queue.pop();
            if (cur) {
                result = cur->val;
                queue.push(cur->right);
                queue.push(cur->left);
            }
        }
        return result;
    }
    
    static TreeNode* createTest1() {
        auto root = new TreeNode(2);
        root->left = new TreeNode(1);
        root->right = new TreeNode(3);
        root->left->right = new TreeNode(5);
        root->right->left = new TreeNode(6);
        root->right->right = new TreeNode(7);
        return root;
    }
};
