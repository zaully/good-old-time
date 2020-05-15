#pragma once

#include <vector>
#include <iostream>

struct TreeNode {
    int value;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
    TreeNode(int v): value(v) {}
};

TreeNode *construct(const std::vector<int> &array, size_t root_index, size_t size) {
    if (size == 0 || root_index >= array.size()) {
        return nullptr;
    }
    auto root_value = array[root_index];
    auto node = new TreeNode(root_value);

    size_t i = 0;
    for (; i < size; ++i) {
        if (root_value < array[i + root_index]) {
            break;
        }
    }

    auto right_index = i + root_index;
    node->right = construct(array, right_index, size - i);

    auto left_index = root_index + 1;
    node->left = construct(array, left_index, right_index - left_index);

    return node;
}

TreeNode *construct(const std::vector<int> &array) {
    return construct(array, 0, array.size());
}
