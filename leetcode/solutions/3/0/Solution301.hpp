
#pragma once

#include <map>
#include <queue>
#include <string>
#include <vector>

using std::map;
using std::queue;
using std::string;
using std::tuple;
using std::vector;

class Solution {
  public:
    void run() {
        removeInvalidParentheses(
                "((((((a)a)a)a)a)a)a)a)a)a)a)a)a)a)(a(a(a(a(a(a(a(a))))");
    }

    vector<string> removeInvalidParentheses(string s) {
        vector<tuple<size_t, size_t>> rightSections;
        queue<map<size_t, size_t>> rightRemovePlans;
        queue<size_t> rightThresholds;
        queue<size_t> rightRemovedCount;

        size_t shouldRemove = 0;
        long long balance = 0;

        for (size_t i = 0; i < s.length(); i++) {
            auto c = s[i];
            if (c == '(') {
                balance++;
            } else if (c == ')') {
                balance--;
                trackParenthese(rightSections, i);
                if (balance < 0) {
                    balance++;
                    shouldRemove++;
                    calculationPlan(rightSections, shouldRemove,
                                    rightRemovePlans, rightThresholds,
                                    rightRemovedCount);
                }
            }
        }

        vector<tuple<size_t, size_t>> leftSections;
        queue<map<size_t, size_t>> leftRemovePlans;
        queue<size_t> leftThresholds;
        queue<size_t> leftRemovedCount;

        shouldRemove = 0;
        balance = 0;

        for (size_t index = s.length(); index > 0; index--) {
            auto i = s.length() - index;
            auto c = s[index - 1];
            if (c == ')') {
                balance++;
            } else if (c == '(') {
                balance--;
                trackParenthese(leftSections, i);
                if (balance < 0) {
                    balance++;
                    shouldRemove++;
                    calculationPlan(leftSections, shouldRemove, leftRemovePlans,
                                    leftThresholds, leftRemovedCount);
                }
            }
        }

        auto leftPlanList = convertPlanToVector(leftRemovePlans);
        auto rightPlanList = convertPlanToVector(rightRemovePlans);

        return composeResults(s, leftPlanList, rightPlanList);
    }

    void trackParenthese(vector<tuple<size_t, size_t>> &p, size_t i) {
        auto continous = false;
        if (p.size() > 0) {
            auto lastSegment = p.back();
            auto length = std::get<1>(lastSegment);
            if (std::get<0>(lastSegment) + length == i) {
                std::get<1>(p.back()) = length + 1;
                continous = true;
            }
        }
        if (!continous) {
            p.push_back(std::make_tuple(i, 1));
        }
    }


    void calculationPlan(const vector<tuple<size_t, size_t>> &sections,
                         size_t shouldRemove,
                         queue<map<size_t, size_t>> &removePlans,
                         queue<size_t> &thresholds,
                         queue<size_t> &removedCount) {
        while (!removePlans.empty()) {
            auto removed = removedCount.front();
            if (shouldRemove > removed) {
                auto plan = removePlans.front();
                auto threshold = thresholds.front();

                for (const auto &section : sections) {
                    auto position = std::get<0>(section);
                    auto number = std::get<1>(section);
                    if (position >= threshold) {
                        auto newPosition = plan.find(position) == plan.end();
                        if (plan.find(position) == plan.end() ||
                            plan.at(position) < number) {
                            auto newPlan = plan;
                            newPlan[position] =
                                    (newPosition ? 0 : newPlan[position]) + 1;
                            removePlans.push(newPlan);
                            thresholds.push(position);
                            removedCount.push(shouldRemove);
                        }
                    }
                }
                removePlans.pop();
                thresholds.pop();
                removedCount.pop();
            } else {
                break;
            }
        }
        if (removePlans.empty()) {
            for (const auto &section : sections) {
                auto position = std::get<0>(section);
                removePlans.push({{position, 1}});
                thresholds.push(position);
                removedCount.push(shouldRemove);
            }
        }
    }

    vector<map<size_t, size_t>> convertPlanToVector(
            queue<map<size_t, size_t>> &from) {
        vector<map<size_t, size_t>> planList;
        while (!from.empty()) {
            planList.emplace_back(std::move(from.front()));
            from.pop();
        }
        return planList;
    }

    vector<string> composeResults(string input,
                                  vector<map<size_t, size_t>> &leftPlanList,
                                  vector<map<size_t, size_t>> &rightPlanList) {
        vector<string> results;

        auto length = input.length();

        if (leftPlanList.empty()) {
            leftPlanList.emplace_back(map<size_t, size_t>());
        }

        if (rightPlanList.empty()) {
            rightPlanList.emplace_back(map<size_t, size_t>());
        }

        for (const auto &rightPlan : rightPlanList) {
            for (const auto &leftPlan : leftPlanList) {
                auto plan = rightPlan;
                for (const auto &pair : leftPlan) {
                    auto rightOrderIndex = length - pair.first - pair.second;
                    plan.insert({rightOrderIndex, pair.second});
                }
                auto planResult = input;
                for (auto iter = plan.rbegin(); iter != plan.rend(); iter++) {
                    planResult.erase(iter->first, iter->second);
                }
                results.emplace_back(std::move(planResult));
            }
        }
        return results;
    }
};
