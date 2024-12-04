/*
Invariant
In programming, an invariant is a condition or property that remains unchanged throughout the execution of a program or a specific section of code. 
In other words, it's a statement that is always true, regardless of the input or the state of the program.

Example:
A stack data structure invariant: "The stack is never empty when popping an element."

Mutex
A mutex (short for "mutual exclusion") is a synchronization primitive that allows only one thread to access a shared resource at a time. 
It's a lock that prevents other threads from entering a critical section of code while one thread is already executing it.

Why do we need Mutexes?
In multithreaded programming, multiple threads may try to access shared resources simultaneously, leading to:

    - Data corruption
    - Race conditions
    - Deadlocks

Mutexes help prevent these issues by ensuring that only one thread can access the shared resource at a time.

How do Mutexes work?
Here's a high-level overview:
    1. A thread tries to acquire the mutex lock before entering the critical section.
    2. If the mutex is available (unlocked), the thread acquires the lock and enters the critical section.
    3. While the thread is in the critical section, other threads trying to acquire the mutex lock will be blocked until the lock is released.
    4. When the thread finishes executing the critical section, it releases the mutex lock, allowing other threads to acquire it.

Best Practices
    1. Always lock the mutex before accessing shared resources.
    2. Release the mutex lock as soon as you're done with the shared resource.
    3. Avoid deadlocks by locking mutexes in a consistent order.
*/



#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx_1; // mutex for protecting shared resource
int sharedResource_1 = 0;

void incrementResource_1() {
    for (int i = 0; i < 100000; ++i) {
        mtx_1.lock(); // acquire mutex lock
        sharedResource_1++;
        mtx_1.unlock(); // release mutex lock
    }
}

int main_1() {
    std::thread t1(incrementResource_1);
    std::thread t2(incrementResource_1);

    t1.join();
    t2.join();

    std::cout << "Final value of shared resource: " << sharedResource_1 << std::endl;

    return 0;
}



/*
If an exception is thrown between mtx.lock() and mtx.unlock(), the mutex will remain locked, leading to a deadlock.

To address this, we can use std::lock_guard, which automatically unlocks the mutex when it goes out of scope:


*******************   Lock Guards in C++ *******************
Lock guards are a type of RAII (Resource Acquisition Is Initialization) idiom in C++ that automatically manage the locking and unlocking of mutexes. 
They ensure that mutexes are properly unlocked when they go out of scope, preventing deadlocks and other synchronization issues.

std::lock_guard is a simple lock guard that locks a mutex when it's constructed and unlocks it when it's destroyed. It's a non-copyable, non-movable class that's designed to be used as a local variable.

*/

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx_2; // mutex for protecting shared resource
int sharedResource_2 = 0;

void incrementResource_2() {
    for (int i = 0; i < 100000; ++i) {
        std::lock_guard<std::mutex> lock(mtx_2); // acquire mutex lock
        sharedResource_2++;
    }
}

int mainx2() {
    std::thread t1(incrementResource_2);
    std::thread t2(incrementResource_2);

    t1.join();
    t2.join();

    std::cout << "Final value of shared resource: " << sharedResource_2 << std::endl;

    return 0;
}

/*
Using std::unique_lock for More Flexibility
std::unique_lock provides more flexibility than std::lock_guard, as it allows you to manually unlock the mutex before it goes out of scope:
*/

#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx_3; // mutex for protecting shared resource
int sharedResource_3 = 0;

void incrementResource_3() {
    for (int i = 0; i < 100000; ++i) {
        std::unique_lock<std::mutex> lock(mtx_3); // acquire mutex lock
        sharedResource_3++;
        lock.unlock(); // manually unlock mutex
    }
}

int main() {
    std::thread t1(incrementResource_3);
    std::thread t2(incrementResource_3);

    t1.join();
    t2.join();

    std::cout << "Final value of shared resource: " << sharedResource_3 << std::endl;

    return 0;
}


/*
Key differences between std::lock_guard and std::unique_lock
    1. Unlocking: 
        std::lock_guard automatically unlocks the mutex when it's destroyed, while std::unique_lock requires manual unlocking using the unlock() method.
    2. Move semantics: 
        std::unique_lock is movable, while std::lock_guard is not.
    3. Flexibility: 
        std::unique_lock provides more flexibility in terms of locking and unlocking, while std::lock_guard is simpler and more straightforward.

When to use each
    1. Use std::lock_guard when you need a simple, automatic lock that's released when it goes out of scope.
    2. Use std::unique_lock when you need more control over the locking and unlocking process, or when you need to transfer ownership of the lock to another thread or function.

Best practices
    1. Always use lock guards to manage mutexes, rather than manual locking and unlocking.
    2. Choose the right lock guard for your use case: std::lock_guard for simple, automatic locking, and std::unique_lock for more complex scenarios.
    3. Avoid using std::lock_guard with recursive mutexes, as it can lead to deadlocks.



*/
