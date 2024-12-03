#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <stdexcept>
#include <algorithm>
void threadFunction(int id) {
    try {
        // Simulating some work
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Thread " << id << " finished" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Thread " << id << " exception: " << e.what() << std::endl;
    }
}

int main() {
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.push_back(std::thread(threadFunction, i));
    }

    try {
        std::for_each(threads.begin(), threads.end(), [](std::thread& t) {
            t.join();
        });
    } catch (const std::exception& e) {
        std::cerr << "Exception during join: " << e.what() << std::endl;
    }

    return 0;
}