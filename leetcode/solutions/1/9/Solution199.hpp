#pragma once

#include <vector>

#include "TreeNode.hpp"

using std::vector;

class Solution199 {
  public:
    void run() {
        auto root = new TreeNode(1);
        root->left = new TreeNode(2);
        root->right = new TreeNode(3);
        root->left->right = new TreeNode(5);
        rightSideView(root);
        delete root;
    }

    vector<int> rightSideView(TreeNode* root) {
        /*
         postorder guarantees the right-most elements will be accessed last
         
         this solution maintains an array or roughly O(logn) size for the answer
         and a level int so that we know what level the current element is at
         */
        auto curLevel = 0;
        auto resultArray = std::vector<int>(1);
        std::stack<TreeNode*> visitStack;
        TreeNode* lastVisit = nullptr;
        auto cur = root;
        while (!visitStack.empty() || cur) {
            if (cur) {
                visitStack.push(cur);
                cur = cur->left;
                curLevel++;
                if (curLevel >= resultArray.size()) {
                    resultArray.push_back(0);
                }
            } else {
                auto peek = visitStack.top();
                if (peek->right && lastVisit != peek->right) {
                    cur = peek->right;
                } else {
                    // visit peek
                    lastVisit = peek;
                    visitStack.pop();
                    curLevel--;
                    resultArray[curLevel] = peek->val;
                }
            }
        }
        resultArray.erase(resultArray.end() - 1);
        return resultArray;
    }
};
