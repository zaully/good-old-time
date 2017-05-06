//
//  main.cpp
//  leetcode
//
//  Created by Vince Liang on 2017-04-15.
//  Copyright © 2017 crawley. All rights reserved.
//

#include <iostream>
#include <chrono>

#include "Solution71.hpp"

int main(int argc, const char * argv[]) {
    
    using namespace std::chrono;
    milliseconds ms1 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    Solution answer;
    answer.run();
    milliseconds ms2 = duration_cast< milliseconds >(system_clock::now().time_since_epoch());
    std::cout << "Time spent: " << ms2.count() - ms1.count() << std::endl;
    return 0;
}
