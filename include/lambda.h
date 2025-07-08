#pragma once
#include <limits>
#include <vector>
#include "ndarray.h"

class lambda{
    public:
        static ndarray<double> create(const std::vector<size_t>& dims);
        lambda();
        constexpr static double E = 2.718281828;
        constexpr static double EULER_GAMMA =  0.577215664;
        constexpr static double PI =  3.141592654;
        constexpr static double INF_FLOAT = std::numeric_limits<double>::infinity();
        constexpr static int INF_INTEGER = std::numeric_limits<int>::infinity();
    private:
};