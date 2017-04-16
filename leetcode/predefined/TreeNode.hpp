#pragma once

#include <queue>
#include <stack>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    
    ~TreeNode() {
        printf("deleting %i\n", val);
        if (left) {
            delete left;
            left = nullptr;
        }
        if (right) {
            delete right;
            right = nullptr;
        }
    }
    
    static void postorderDfsStack(TreeNode* root) {
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
                    // visit peek
                    lastVisit = peek;
                    visitStack.pop();
                }
            }
        }
    }
    
    
    static void inorderDfsStack(TreeNode* root) {
        std::stack<TreeNode*> visitStack;
        auto cur = root;
        while (cur || !visitStack.empty()) {
            while (cur) {
                visitStack.push(cur);
                cur = cur->left;
            }
            cur = visitStack.top();
            visitStack.pop();
            printf("%i\n", cur->val);
            cur = cur->right;
        }
    }
    
    static void bfsQueue(TreeNode* root, bool leftFirst) {
        std::queue<TreeNode *> queue;
        queue.push(root);
        while (!queue.empty()) {
            auto cur = queue.front();
            queue.pop();
            if (cur) {
                printf("%i\n", cur->val);
                if (leftFirst) {
                    queue.push(cur->left);
                    queue.push(cur->right);
                } else {
                    queue.push(cur->right);
                    queue.push(cur->left);
                }
            }
        }
    }
};
