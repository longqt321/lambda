#pragma once
#include <limits>
#include <vector>
#include "ndarray.h"

class lambda{
    public:
        lambda();
        virtual ~lambda();
        static ndarray<double> create(const std::vector<size_t>& dims);
        static ndarray<double> ones(const std::vector<size_t>& dims);
        static ndarray<double> zeros(const std::vector<size_t>& dims);
        constexpr static double E = 2.718281828;
        constexpr static double EULER_GAMMA =  0.577215664;
        constexpr static double PI =  3.141592654;
        constexpr static double INF_FLOAT = std::numeric_limits<double>::infinity();
        constexpr static int INF_INTEGER = std::numeric_limits<int>::infinity();
    private:
};