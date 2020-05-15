//
//  quick_sort_iterative.hpp
//  leetcode
//
//  Created by Vince Liang on 2020-04-01.
//  Copyright © 2020 crawley. All rights reserved.
//

#pragma once

#include <stack>
#include <vector>
#include "quick_sort_recursive.hpp"

template <class T>
void q_sort(std::vector<T> &array, size_t start, size_t end) {
    auto i = start < 0 ? 0 : start;
    auto j = end >= array.size() ? array.size() - 1 : end;
    if (i > j) {
        std::swap(i, j);
    }
    std::stack<size_t> range;
    range.push(j);
    range.push(i);
    while (!range.empty()) {
        auto left = range.top();
        range.pop();
        auto right = range.top();
        range.pop();
        if (left >= right) {
            continue;
        }
        auto mid = partition_1(array, left, right);
        range.push(mid);
        range.push(left);
        range.push(right);
        range.push(mid + 1);
    }
}

template <class T>
void q_sort(std::vector<T> &array) {
    q_sort(array, 0, array.size() - 1);
}
