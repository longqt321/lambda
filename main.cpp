#include <iostream>
#include "lambda.h"
#include "ndarray.h"

int main(){
    std::cout << "Hello\n";
    std::vector<size_t>sizes{2,2};
    auto a = lambda::ones(sizes);
    auto b = lambda::ones(sizes);
    a = a + b;
    std::cout << (a.dot(b) + 11*a)(0,0);
    
    return 0;
}