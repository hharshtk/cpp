// Include the necessary header files
#include <iostream>
#include <thread>

// Define a function that will be executed by the thread
void printNumbers() {
    // Print numbers from 0 to 9
    for (int i = 0; i < 10; i++) {
        // Use std::cout to print the numbers
        std::cout << "Thread 1: " << i << std::endl;
    }
}

// Define another function that will be executed by another thread
void printLetters() {
    // Print letters from A to J
    for (char c = 'A'; c <= 'J'; c++) {
        // Use std::cout to print the letters
        std::cout << "Thread 2: " << c << std::endl;
    }
}

// The main function where the program starts execution
int main() {
    // Create a thread that will execute the printNumbers function
    std::thread thread1(printNumbers);

    // Create another thread that will execute the printLetters function
    std::thread thread2(printLetters);

    // Wait for thread1 to finish execution using join()
    // This will block the main thread until thread1 finishes
    thread1.join();

    // Wait for thread2 to finish execution using join()
    // This will block the main thread until thread2 finishes
    thread2.join();

    // Thread join order
    // If you change the order of the join calls, it will not affect the overall behavior of the program. The join calls are used to wait for the threads to finish executing, and the order in which you call join on the threads does not matter.

    // In other words, whether you call thread1.join() before thread2.join() or vice versa, the program will still wait for both threads to finish executing before continuing.

    // Return 0 to indicate successful execution
    return 0;
}

/*
********************************************************************************************************************************
                                                Thread Execution Lifecycle                                                            
********************************************************************************************************************************

A thread starts to execute as soon as it is created, but it may not immediately start executing due to various reasons such as:

1. Thread creation overhead: 
   When a thread is created, the operating system needs to perform some overhead tasks such as allocating memory for the thread's stack, initializing the thread's context, and scheduling the thread.
2. Thread scheduling: 
   The operating system's scheduler decides when to schedule the thread for execution. The scheduler may delay the thread's execution due to various reasons such as other threads having higher priority, the thread being in a waiting state, or the system being busy with other tasks.
3. Context switching: 
   When a thread is scheduled for execution, the operating system needs to perform a context switch, which involves saving the current thread's state and restoring the new thread's state. This process can take some time.

In general, a thread starts to execute at the following stages:

1. Thread creation: 
   When a thread is created using the std::thread constructor, the thread is created in a suspended state. The thread does not start executing immediately.
2 Thread scheduling: 
  When the thread is scheduled for execution by the operating system's scheduler, the thread starts executing. This can happen immediately after thread creation or after some delay due to various reasons.
3. Thread execution: 
  Once the thread starts executing, it runs until it completes its task or is interrupted by the operating system.

In terms of the program's execution flow, a thread starts to execute after the std::thread constructor returns. The std::thread constructor creates a new thread and returns immediately, without waiting for the thread to start executing.

#include <iostream>
#include <thread>

void threadFunction() {
    std::cout << "Thread is executing..." << std::endl;
}

int main() {
    std::cout << "Creating thread..." << std::endl;
    std::thread thread(threadFunction);
    std::cout << "Thread created..." << std::endl;

    return 0;
}



In this example, the output will be:

Creating thread...
Thread created...
Thread is executing...

The thread starts executing after the std::thread constructor returns, which is after the "Thread created..." message is printed.





********************************************************************************************************************************
                                                Thread Join Operation                                                         
********************************************************************************************************************************

The join() operation is used to wait for a thread to finish executing. When a thread is created using the std::thread constructor, it is created in a suspended state. The thread does not start executing immediately. Instead, it is scheduled for execution by the operating system's scheduler.

The join() operation blocks the calling thread until the specified thread finishes executing. 
This means that the calling thread will not continue until the specified thread has completed its task.

Here are some reasons why the join() operation is necessary:

1. Synchronization: 
   The join() operation allows you to synchronize the execution of threads. By calling join() on a thread, you ensure that the calling thread waits until the specified thread has finished executing before continuing. This can be useful in scenarios where the calling thread needs to rely on the completion of the thread.
2 .Resource management: 
   When a thread finishes executing, its resources are automatically released by the operating system. However, if you don't use join() to wait for the thread to finish, the calling thread may terminate before the thread has a chance to release its resources. This can lead to resource leaks and undefined behavior.
3. Error handling:
   The join() operation can also be used for error handling. If a thread encounters an exception or an error, the join() operation can be used to wait for the thread to finish executing and then handle the error in the calling thread.

*/


