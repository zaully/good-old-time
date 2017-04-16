#pragma once

#include <stack>
#include <vector>

using std::vector;

class Solution486 {
  public:
    void run() {
        vector<int> nums = {1, 5, 2, 1, 5, 2, 1, 5, 2, 1, 5, 2, 1, 5, 2, 1, 5, 2, 1, 5};
        PredictTheWinner(nums);
    }

    bool PredictTheWinner(vector<int> &nums) {
        auto level = 0;
        auto root = new TreeNode(0, 0, level++);
        if (nums.size() > 0) {
            addLayer(root, nums, level, 0, nums.size());
        }
        postorderDfsCalculateScores(root);
        auto win = root->aScore >= root->bScore;
        delete root;
        return win;
    }

  private:
    struct TreeNode {
        int aScore;
        int bScore;
        int level;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int as, int bs, int lvl)
                : aScore(as),
                  bScore(bs),
                  level(lvl),
                  left(nullptr),
                  right(nullptr) {}

        ~TreeNode() {
            if (left) {
                delete left;
                left = nullptr;
            }
            if (right) {
                delete right;
                right = nullptr;
            }
        }
    };
    
    void postorderDfsCalculateScores(TreeNode* root) {
        std::stack<TreeNode*> visitStack;
        TreeNode *lastVisit = nullptr;
        auto cur = root;
        while (!visitStack.empty() || cur) {
            if (cur) {
                visitStack.push(cur);
                cur = cur->left;
            } else {
                auto peek = visitStack.top();
                if (peek->right && lastVisit != peek->right) {
                    cur = peek->right;
                } else {
                    auto leftAScore = peek->left ? peek->left->aScore : 0;
                    auto rightAScore = peek->right ? peek->right->aScore : 0;
                    auto leftBScore = peek->left ? peek->left->bScore : 0;
                    auto rightBScore = peek->right ? peek->right->bScore : 0;
                    if (peek->level % 2 == 0) {
                        peek->aScore += leftAScore > rightAScore ? leftAScore : rightAScore;
                        peek->bScore += leftBScore < rightBScore ? leftBScore : rightBScore;
                    } else {
                        peek->aScore += leftAScore < rightAScore ? leftAScore : rightAScore;
                        peek->bScore += leftBScore > rightBScore ? leftBScore : rightBScore;
                    }
                    
                    lastVisit = peek;
                    visitStack.pop();
                }
            }
        }
    }

    void addLayer(TreeNode *current, const vector<int> &nums, int level,
                  size_t leftBoundary, size_t rightBoundary) {
        auto newNode = [&nums, &level](size_t index){
            int aScore, bScore;
            if (level % 2 == 1) {
                aScore = nums[index];
                bScore = 0;
            } else {
                bScore = nums[index];
                aScore = 0;
            }
            return new TreeNode(aScore, bScore, level);
        };
        if (leftBoundary < rightBoundary) {
            current->left = newNode(leftBoundary);
            addLayer(current->left, nums, level + 1, leftBoundary + 1,
                     rightBoundary);
        }
        if (leftBoundary < rightBoundary - 1) {
            current->right = newNode(rightBoundary - 1);
            addLayer(current->right, nums, level + 1, leftBoundary,
                     rightBoundary - 1);
        }
    };
};
