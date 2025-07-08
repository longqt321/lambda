#include <iostream>
#include "lambda.h"
#include "ndarray.h"

int main(){
    std::cout << "Hello\n";
    std::vector<size_t>sizes{2,2};
    auto a = lambda::create(sizes);
    std::cout << a(1,1);
    
    return 0;
}