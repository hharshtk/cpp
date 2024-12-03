/*
RAII (Resource Acquisition Is Initialization) is a C++ technique that can help you manage resources and exceptions in a more elegant way.

Instead of using try-catch blocks, you can create a class that acquires a resource in its constructor and releases it in its destructor. 
This way, even if an exception is thrown, the resource will be properly released.
*/
#include <iostream>
#include <thread>
#include <vector>
#include <future>
#include <stdexcept>
#include <algorithm>
class Thread {
public:
    Thread() : thread_(), running_(false) {}

    void start() {
        if (!running_) {
            thread_ = std::thread(&Thread::run, this);
            running_ = true;
        }
    }

    void join() {
        if (running_) {
            thread_.join();
            running_ = false;
        }
    }

    ~Thread() {
        join();
    }

private:
    void run() {
        // Thread code goes here
        std::cout << "Thread is running..." << std::endl;
        // Simulate some work
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Thread finished." << std::endl;
    }

    std::thread thread_;
    bool running_;
};

int main() {
    Thread thread;
    thread.start();
    // Do some other work...
    std::cout << "Main thread is waiting for the thread to finish..." << std::endl;
    return 0;
}