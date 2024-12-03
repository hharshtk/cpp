/*
In C++, templates are a feature that allows for generic programming, enabling the creation of reusable code that can work with different data types.
Templates are essentially a way to parameterize types, allowing you to write code that can be instantiated with different types


Why are templates useful?
Templates are useful for several reasons:

1. Generic programming:
   Templates enable you to write code that can work with different data types, reducing code duplication and increasing code reusability.
2. Type safety:
   Templates ensure type safety by allowing the compiler to check the types of variables at compile-time, preventing type-related errors at runtime.
3. Performance:
   Templates can improve performance by avoiding the overhead of dynamic casting and runtime type checking.


Example : 
Suppose you want to implement a stack data structure that can work with different data types. Without templates, you would need to write separate implementations for each data type. With templates, you can write a single implementation that can be instantiated with different types.
*/

#include <iostream>

/*
Let's consider a simple example of a function that adds two values together. Without templates, you would have to write separate functions for each data type:
*/
int addInts(int a, int b) {
    return a + b;
}

float addFloats(float a, float b) {
    return a + b;
}

double addDoubles(double a, double b) {
    return a + b;
}

//////////////////////////    With template ///////////////////
/*
With templates, you can write a single function that works with any data type:
*/
// Template function to add two values
template <typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    // Example usage with integers
    int result1 = add(5, 10);
    std::cout << "Result (int): " << result1 << std::endl;

    // Example usage with floats
    float result2 = add(3.14f, 2.71f);
    std::cout << "Result (float): " << result2 << std::endl;

    // Example usage with doubles
    double result3 = add(3.14, 2.71);
    std::cout << "Result (double): " << result3 << std::endl;

    // Example usage with custom type (complex numbers)
    struct Complex {
        double real;
        double imag;
    };

    Complex result4 = {add(3.14, 2.71), add(1.23, 4.56)};
    std::cout << "Result (complex): " << result4.real << " + " << result4.imag << "i" << std::endl;

    // Example usage with strings (using std::string)
    std::string result5 = add(std::string("Hello"), std::string("World"));
    std::cout << "Result (string): " << result5 << std::endl;

    return 0;
}

/*
Result (int): 15
Result (float): 5.85
Result (double): 5.85
Result (complex): 5.85 + 5.79i
Result (string): HelloWorld
*/

/*

Benefits of Templates

This code demonstrates the benefits of using templates:

1. Code reuse:
   The add function is written only once, but can be used with multiple data types, including integers, floats, doubles, complex numbers, and strings.
2. Type safety:
   The compiler checks the types of the arguments at compile-time, preventing type-related errors at runtime.
3. Flexibility:
   The add function can be used with a wide range of data types, including custom types like complex numbers.
4. Efficiency:
   The compiler generates optimized code for each data type, eliminating the need for runtime type checking or casting.

*/