#include <future>
#include <iostream>
#include <thread>

int asyncTask() {
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return 42;
}

int mainx() {
    // Launch an async task
    std::future<int> ans = std::async(std::launch::async, asyncTask); // Launches an async task and assigns the result to a future. T
    // ans may not be available yet but will be in future
    // std::launch::async :  This is the launch policy for the async task. It specifies that the task should be launched asynchronously, meaning it doesn't block the calling thread.
    // asyncTask: This is the function that represents the async task. It's the function that will be executed asynchronously.
    
    // Do some other work while the task is running
    std::cout << "Doing other work..." << std::endl;

    // Wait for the task to finish and get the result
    int result = ans.get();
    std::cout << "Result: " << result << std::endl;

    return 0;
}




/*
Example: Simulating a Coffee Shop

In this example, we'll simulate a coffee shop with multiple baristas. Each barista will prepare a drink asynchronously, and we'll use std::async and std::future to manage the tasks.
*/

#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <vector>
// Function to prepare a drink
std::string prepareDrink(const std::string& drinkName, int prepTime) {
    std::cout << "Preparing " << drinkName << "..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(prepTime)); // Simulate preparation time
    // std::cout << drinkName << " is ready!" << std::endl;
    return drinkName;
}

int main() {
    // Create a vector to store the futures
    std::vector<std::future<std::string>> futures;

    // Launch multiple tasks to prepare different drinks with different preparation times
    futures.push_back(std::async(std::launch::async, prepareDrink, "Latte", 2));
    futures.push_back(std::async(std::launch::async, prepareDrink, "Cappuccino", 3));
    futures.push_back(std::async(std::launch::async, prepareDrink, "Mocha", 1));

    // Wait for all tasks to complete and retrieve the results
    for (auto& future : futures) {
        std::string drinkName = future.get();
        std::cout << "Drink ready: " << drinkName << std::endl;
    }

    return 0;
}



/*
To fix the issue where whatever drink that is ready first will be printed first. we we can use std::future::wait_for instead of std::future::get to wait for each task to complete without blocking the main thread. Here's an updated example:
*/



#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// Function to prepare a drink
std::string prepareDrink(const std::string& drinkName, int prepTime) {
    std::cout << "Preparing " << drinkName << "..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(prepTime)); // Simulate preparation time
    std::cout << drinkName << " is ready!" << std::endl;
    return drinkName;
}

int main() {
    // Create a vector to store the futures
    std::vector<std::future<std::string>> futures;

    // Launch multiple tasks to prepare different drinks with different preparation times
    futures.push_back(std::async(std::launch::async, prepareDrink, "Latte", 2));
    futures.push_back(std::async(std::launch::async, prepareDrink, "Cappuccino", 3));
    futures.push_back(std::async(std::launch::async, prepareDrink, "Mocha", 1));

    // Wait for all tasks to complete and retrieve the results
    for (auto& future : futures) {
        while (future.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready) {
            std::cout << "." << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::string drinkName = future.get();
        std::cout << "\nDrink ready: " << drinkName << std::endl;
    }

    return 0;
}
