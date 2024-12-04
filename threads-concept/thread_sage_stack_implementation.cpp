/*
    A condition variable is a synchronization primitive that allows threads to wait until a particular condition is true. 
    It's a way for threads to communicate with each other and coordinate their actions.
*/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

// Node structure for stack
struct Node {
    int data;
    Node* next;
    Node(int data) : data(data), next(nullptr) {}
};

// Stack class
class Stack {
private:
    Node* head;
    std::mutex mtx;
    std::condition_variable cv;

public:
    Stack() : head(nullptr) {}

    void push(int data) {
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Pushing: " << data << std::endl;   
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        cv.notify_all();
    }

    int pop() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this](){ return head != nullptr; });
        Node* temp = head;
        head = head->next;
        int data = temp->data;
        delete temp;
        return data;
    }

    void print() {
        std::lock_guard<std::mutex> lock(mtx);
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

// Function to be executed by each thread
void pushThread(Stack* stack, int data) {
    stack->push(data);
}

void popThread(Stack* stack) {
    int data = stack->pop();
    std::cout << "Popped: " << data << std::endl;
}

int main() {
    Stack stack;
    std::thread t1(pushThread, &stack, 5);
    std::thread t2(pushThread, &stack, 10);
    std::thread t3(pushThread, &stack, 15);

    t1.join();
    t2.join();
    t3.join();

    std::thread t4(popThread, &stack);
    std::thread t5(popThread, &stack);

    t4.join();
    t5.join();

    stack.print();

    return 0;
}
