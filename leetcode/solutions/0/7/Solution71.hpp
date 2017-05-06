#pragma once

#include <string>
#include <vector>

class Solution {
public:
    void run() {
        printf("%s\n", simplifyPath("/home").c_str());
    }
    
    std::string simplifyPath(std::string path) {
        std::vector<std::string> result;
        std::string path_unit = "";
        auto append = [&](){
            if (path_unit == "..") {
                if (result.size() > 0) {
                    result.pop_back();
                }
            } else if (path_unit != "." && !path_unit.empty()) {
                result.push_back(path_unit);
            }
            path_unit.clear();
        };
        for (auto i = 1; i < path.size(); i++) {
            auto ch = path[i];
            switch (ch) {
                case '/':
                    append();
                    break;
                default:
                    path_unit += ch;
                    break;
            }
        }
        if (!path_unit.empty()) {
            append();
        }
        std::string ret = "";
        for (const auto &r : result) {
            ret += "/" + r;
        }
        return path.empty() ? "" : ret.empty() ? "/" : ret;
    }
};
