#include <iostream>
#include "lambda.h"

int main(){
    std::cout << "Hello\n";
    lambda *a = new lambda();
    a->matrix();
    delete a;
    return 0;
}