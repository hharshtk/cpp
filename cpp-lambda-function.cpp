/*
A lambda function, also known as a closure or anonymous function, is a small, anonymous function that can be defined inline within a larger expression. 
It's a powerful feature in C++ that allows you to create small, one-time use functions without declaring a named function.
*/

/*
Syntax : 
[capture](parameters) -> return-type {
    // function body
}


Let's break it down:
    - [capture]: This is the capture clause, which specifies how the lambda function accesses variables from the surrounding scope.
    - (parameters): This is the parameter list, which specifies the input parameters of the lambda function.
    - -> return-type: This is the return type of the lambda function.
    - { // function body }: This is the body of the lambda function.
*/


#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int x = 10;
    int y = 20;

    // Value capture: [x]
    auto lambda1 = [x](int z, int a) -> int {
        // x = x + 10; 
        // x is a captured variable by value, which means it's a copy of the original x variable. However, this copy is not modifiable because it's implicitly const.
        return x + z + a;
    };
    std::cout << "Lambda 1: " << lambda1(5, 10) << std::endl; // Output: 15

    // Reference capture: [&x]
    auto lambda2 = [&x](int z) -> int {
        x += z;
        return x;
    };
    std::cout << "Lambda 2: " << lambda2(5) << std::endl; // Output: 15
    std::cout << "x: " << x << std::endl; // Output: 15

    // Generalized capture: [=]
    /*
    When you use [=] to capture variables, the lambda function creates copies of the variables in the surrounding scope and uses those copies within the function. This means that any changes made to the variables within the lambda function do not affect the original variables in the surrounding scope.
    */
    auto lambda3 = [=](int z) -> int {
        return x + y + z;
    };
    std::cout << "Lambda 3 Generalized capture by value: " << lambda3(5) << std::endl; // Output: 35

    // Generalized capture: [&]
    /*
    When you use [&] to capture variables, the lambda function captures the variables by reference, which means it can modify the original variables in the surrounding scope
    */
    auto lambda4 = [&](int z) -> int {
        x += z;
        return x + y;
    };
    std::cout << "Lambda 4  Generalized capture with reference: " << lambda4(5) << std::endl; // Output: 40
    std::cout << "x: " << x << std::endl; // Output: 20

    // Mixed capture: [x, &y]
    auto lambda5 = [x, &y](int z) -> int {
        y += z;
        return x + y;
    };
    std::cout << "Lambda 5 with mixed capture: " << lambda5(5) << std::endl; // Output: 35
    std::cout << "y: " << y << std::endl; // Output: 25

    // Lambda function with no capture
    auto lambda6 = [](int z) -> int {
        return z * z;
    };
    std::cout << "Lambda 6 with no capture: " << lambda6(5) << std::endl; // Output: 25

    return 0;
}
