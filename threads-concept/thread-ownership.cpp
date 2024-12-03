#include <thread>
#include <iostream>

void myThreadFunction() {
  std::cout << "Thread is running..." << std::endl;

  // Simulate some work
  std::this_thread::sleep_for(std::chrono::seconds(5));

  std::cout << "Thread has finished..." << std::endl;
}

int main() {
  std::thread thread1(myThreadFunction);

  // Transfer ownership of the thread to thread2
  std::thread thread2 = std::move(thread1);

  // thread1 is no longer valid
  if (thread1.joinable()) {
    std::cout << "Error: thread1 is still joinable!" << std::endl;
  }

  // Wait for thread2 to finish
  if (thread2.joinable()) {
    thread2.join();
  } else {
    std::cout << "Error: thread2 is not joinable!" << std::endl;
  }

  return 0;
}


/*
Here are the important points for thread ownership in C++ in brief:

std::thread object owns the thread.
Thread ownership is transferable using std::move.
A thread can only be owned by one std::thread object.
Detached threads are not joinable.
Joining a thread blocks the calling thread.
Can't join a thread that's already finished.
std::move invalidates the original std::thread object.
Check if a thread is joinable using joinable()
*/