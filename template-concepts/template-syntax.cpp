#include <iostream>

// ****************************************
// Template function with type parameter
// ****************************************
/*
1. template <typename T>: This is the template parameter declaration. 
2. typename is a keyword that indicates that T is a type parameter. T is the name of the type parameter.
3. T max(T a, T b): This is the template function definition. max is the name of the function, and it takes two parameters of type T.
4. return (a > b) ? a : b;: This is the function body. It returns the maximum of a and b.

This template function can be used with any type that supports comparison using the > operator. For example, you can use it with int, double, char, etc
*/
template <typename T> 
T max(T a, T b) { 
    return (a > b) ? a : b; 
}


// Template function with non-type parameter
template <int N> 
void printN() { 
    for (int i = 0; i < N; i++) { 
        std::cout << "Hello" << std::endl;
    }
}

// Template function with multiple type parameters
template <typename T, typename U> 
void printPair(T a, U b) { 
    std::cout << "Pair: " << a << ", " << b << std::endl; 
}

// Template function with default template argument
template <typename T = int>  
T identity(T a) { 
    return a; 
}

// Template class with type parameter
template <typename T> 
class Container { // Template class definition
public:
    T value; // Member variable
    Container(T val) : value(val) {} // Constructor
};

// Template class with non-type parameter
template <int N> 
class Array { // Template class definition
public:
    int data[N]; // Member variable
    Array() { // Constructor
        for (int i = 0; i < N; i++) {
            data[i] = i;
        }
    }
};
/*

*/


int main() {
    
    int result1 = max(5, 10); // max<int>(5, 10)
    std::cout << "Max: " << result1 << std::endl;

    
    printN<5>(); // printN<5>()

    
    printPair(5, "hello"); // printPair<int, const char*>(5, "hello")

     
    int result2 = identity(5); // identity<int>(5)
    std::cout << "Identity: " << result2 << std::endl;

    // Template class instantiation
    Container<int> c(5); // Container<int> c(5)
    std::cout << "Container value: " << c.value << std::endl;

    // Template class instantiation
    Array<5> a; // Array<5> a
    for (int i = 0; i < 5; i++) {
        std::cout << "Array value: " << a.data[i] << std::endl;
    }

    return 0;
}




