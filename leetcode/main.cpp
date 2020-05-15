
#include <iostream>
#include <chrono>

#include "Solution10.hpp"

int main(int argc, const char * argv[]) {

    // #pragma GCC optimise ("Ofast")
    // static auto fast=[]{ios_base::sync_with_stdio(false);cin.tie(nullptr);return 0;}();
    using namespace std::chrono;
    milliseconds ms1 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

    Solution s;
    s.run();

    milliseconds ms2 = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    std::cout << "Time spent: " << ms2.count() - ms1.count() << std::endl;
}
