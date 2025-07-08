#include "lambda.h"
#include <iostream>

lambda::lambda(){
    std::cout << "Constructor\n";
}

ndarray<double> lambda::create(const std::vector<size_t>& dims){
    return ndarray<double>(dims);
}