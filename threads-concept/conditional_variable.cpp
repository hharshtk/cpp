#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void waitingThread(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Thread " << id << " is waiting...\n";
    cv.wait(lock, []{ return ready; }); // wait until ready is true
    /*
    1. The wait() function takes two arguments: a lock object and a predicate function.
    2. lock: This is a std::unique_lock object that represents a lock on a mutex. The wait() function will automatically 
             release the lock while the thread is waiting, and then re-acquire it when the thread is notified.
    3. []{ return ready; }: This is a lambda function that serves as the predicate for the wait() function. 
         The predicate is a function that returns true or false. In this example, the predicate is []{ return ready; }, which checks if the ready variable
    */
    std::cout << "Thread " << id << " is done waiting.\n";
}

int main() {
    std::thread t1(waitingThread, 1);
    std::thread t2(waitingThread, 2);
    std::thread t3(waitingThread, 3);

    std::this_thread::sleep_for(std::chrono::seconds(2)); // simulate some work
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_all(); // notify all waiting threads
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
