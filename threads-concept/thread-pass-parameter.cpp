#include<iostream>
#include<thread>
#include <functional>

using namespace std;
void func(int id, string name){
    cout << "Thread " << id << " started with name: " << name << endl;
    // Simulate some work
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Thread " << id << " finished" << endl;

}

int mainx(){
    thread t1(func, 1,"thread 1");
    thread t2(func, 2, "thread 2");

    t1.join();
    t2.join();
    return 0;
}



// ****************************************
// To change the value mid execution
// ****************************************

/*
To modify the parameters mid-execution, we can use reference_wrapper to pass the parameters by reference. Here's an example:
*/

// Function to be executed by the thread
void threadFunction(reference_wrapper<int> id, reference_wrapper<string> name) {
    // To print the string in std::reference_wrapper<std::string> name, you can use the get() method to access the underlying string object.
    cout << "Thread started with id: " << id << " and name: " << name.get() << endl;
    // Simulate some work
    this_thread::sleep_for(chrono::seconds(2));
    // Modify the parameters
    id.get() = 10;
    name.get() = "New Thread";
    cout << "Thread modified id: " << id << " and name: " << name.get() << endl;
    // Simulate some more work
    this_thread::sleep_for(chrono::seconds(2));
    cout << "Thread finished" << endl;
}


int main(){
    int id = 1;
    string name = "Thread 1";
    cout << name << endl ;
    // return 0;
    
    // Create a thread and pass parameters to the thread function
    thread t(threadFunction, ref(id), ref(name));
    // thread t(threadFunction, ref(id), ref(name));

    // Wait for 3 seconds and then print the modified values
    this_thread::sleep_for(chrono::seconds(3));
    cout << "Main thread: id = " << id << ", name = " << name << endl;

    // Wait for the thread to finish
    t.join();

    return 0;

}