#include "lambda.h"
#include <iostream>

lambda::lambda(){
    std::cout << "Constructor\n";
}

ndarray<double> lambda::create(const std::vector<size_t>& dims){
    return ndarray<double>(dims);
}

lambda::~lambda(){
}

ndarray<double> lambda::ones(const std::vector<size_t>& dims){
    ndarray<double> result(dims);
    for (size_t i = 0; i < result.n_elements; ++i) {
        result.data[i] = 1.0;
    }
    return result;
}