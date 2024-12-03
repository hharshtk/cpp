#include <iostream>
#include <thread>

void worker() {
    std::cout << "Worker thread started." << std::endl;
    // Simulate some work
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Worker thread finished." << std::endl;
}

int main() {
    std::thread t(worker);
    t.detach(); // Detach the thread
    /*
    1. detach is a member function of the std::thread class that allows a thread to execute independently of the parent thread.
    2. When you call detach on a thread, it becomes detached from the parent thread, and the parent thread can no longer wait
       for the detached thread to finish using join.
    3. 
    */

    std::cout << "Main thread continues..." << std::endl;
    // Main thread can exit without waiting for the worker thread
    std::this_thread::sleep_for(std::chrono::seconds(3));   // To see 'Worker thread finished.' message
    return 0;
}

/*
Output:
Main thread continues...
Worker thread started.

----
Worker thread finished. is not getting printed because 
1. When the main thread exits, the program terminates, and any remaining threads are also terminated.
2. he worker thread is still running when the main thread exits, so it doesn't get a chance to finish and print its final message.
3. To see the "Worker thread finished." message, you can add a small delay to the main thread to give the worker thread a chance to finish.
4. With this the main thread waits for 3 seconds before exiting, giving the worker thread enough time to finish and print its final message.
*/

/*

#############################################################################################
                                    Join Vs Detach
#############################################################################################
Use join when:

1. You need to wait for the thread to finish: 
   If the main thread needs to wait for the worker thread to complete its task before proceeding, use join. This ensures that the main thread doesn't exit before the worker thread finishes.
2. You need to handle the thread's return value: 
   If the worker thread returns a value, you can use join to retrieve that value.
3. You want to ensure thread cleanup: 
   When a thread is joined, its resources are properly cleaned up, including any allocated memory.


Use detach when:

1. You don't care when the thread finishes: 
   If the main thread doesn't need to wait for the worker thread to complete its task, use detach. This allows the main thread to continue executing without blocking.
2. You want the thread to run independently: 
   If the worker thread needs to run independently of the main thread, use detach. This allows the thread to continue running even if the main thread exits.
3. You're using a thread pool or a long-running thread: 
   In cases where you have a pool of threads or a thread that runs for an extended period, detach can be useful to allow the threads to run independently.


In general, if you're unsure whether to use join or detach, ask yourself:

1. Do I need to wait for the thread to finish? (Use join)
2. Do I need to handle the thread's return value? (Use join)
3. Do I want the thread to run independently? (Use detach)

Remember, if you don't call either join or detach on a thread, the program's behavior is undefined when the thread exits. Always make sure to call one of these functions to ensure proper thread management.
*/