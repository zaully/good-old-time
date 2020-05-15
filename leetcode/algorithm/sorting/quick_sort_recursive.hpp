#pragma once

#include <vector>

template <class T>
size_t partition_1(std::vector<T> &array, size_t start, size_t end) {
    auto i = start;
    auto j = end;
    auto pivot = array[start];
    while (i < j) {
        while (array[j] >= pivot && i < j) {
            j--;
        }
        array[i] = array[j];
        while (array[i] <= pivot && i < j) {
            i++;
        }
        array[j] = array[i];
    }
    array[i] = pivot;
    return i;
}

/**
 Quick Sort recursive implementation using the first element as pivot

 @param array the array you wanna sort
 @param left starting index
 @param right ending index
 */
template <class Element>
void quick_sort(std::vector<Element> &array, size_t left, size_t right) {
    auto start = left;
    auto end = right;
    if (start < 0) {
        start = 0;
    }
    if (end >= array.size()) {
        end = array.size() - 1;
    }
    auto i = partition_1(array, start, end);
    if (start < end) {
        quick_sort(array, start, i);
        quick_sort(array, i + 1, end);
    }
}
