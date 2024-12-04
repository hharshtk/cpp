#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

// Request queue
std::queue<std::string> requestQueue;
std::mutex mtx;
std::condition_variable cv;

// Worker thread function
void workerThread(int id) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []{ return !requestQueue.empty(); }); // wait until request is available
        std::string request = requestQueue.front();
        requestQueue.pop();
        lock.unlock();

        // Process the request
        std::cout << "Worker " << id << " processing request: " << request << std::endl;
        // Simulate processing time
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

// Request receiver thread function
void requestReceiverThread() {
    int requestId = 1;
    while (true) {
        // Simulate receiving a request
        std::string request = "Request " + std::to_string(requestId);
        std::cout << "Received request: " << request << std::endl;

        // Add request to queue
        std::lock_guard<std::mutex> lock(mtx);
        requestQueue.push(request);
        std::cout << "Added request to queue: " << request << std::endl;
        cv.notify_one(); // notify worker threads

        requestId++;
        std::this_thread::sleep_for(std::chrono::seconds(1)); // simulate receiving requests at a rate of 1 per second
    }
}

// Request queue manager thread function
void requestQueueManagerThread() {
    while (true) {
        // Monitor queue size
        std::lock_guard<std::mutex> lock(mtx);
        if (requestQueue.size() > 5) {
            std::cout << "Queue is full! Notifying worker threads to process requests." << std::endl;
            cv.notify_all(); // notify all worker threads
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    // Create worker threads
    std::thread worker1(workerThread, 1);
    std::thread worker2(workerThread, 2);
    std::thread worker3(workerThread, 3);
    std::thread worker4(workerThread, 4);
    std::thread worker5(workerThread, 5);

    // Create request receiver thread
    std::thread requestReceiver(requestReceiverThread);

    // Create request queue manager thread
    std::thread requestQueueManager(requestQueueManagerThread);

    // Wait for threads to finish
    worker1.join();
    worker2.join();
    worker3.join();
    worker4.join();
    worker5.join();
    requestReceiver.join();
    requestQueueManager.join();

    return 0;
}
