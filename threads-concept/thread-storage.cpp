#include <iostream>
#include <thread>

thread_local int tls_var = 0;

void thread_func() {
    tls_var = 10; // set thread-local variable
    std::cout << "Thread " << std::this_thread::get_id() << ": tls_var = " << tls_var << std::endl;
}

int main() {
    std::thread t1(thread_func);
    std::thread t2(thread_func);

    t1.join();
    t2.join();

    return 0;
}
