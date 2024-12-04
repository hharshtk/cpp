#include <iostream>
#include <thread>
#include <mutex>

// Node structure for linked list
struct Node {
    int data;
    Node* next;
    Node(int data) : data(data), next(nullptr) {}
};

// Linked list class
class LinkedList {
    private:
        Node* head;
        std::mutex mtx;

    public:
        LinkedList() : head(nullptr) {}

        void insert(int data) {
            std::lock_guard<std::mutex> lock(mtx);
            Node* newNode = new Node(data);
            if (head == nullptr) {
                head = newNode;
            } else {
                Node* temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
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
void insertThread(LinkedList* list, int data) {
    list->insert(data);
}

int main() {
    LinkedList list;
    std::thread t1(insertThread, &list, 5);
    std::thread t2(insertThread, &list, 10);
    std::thread t3(insertThread, &list, 15);

    t1.join();
    t2.join();
    t3.join();

    list.print();

    return 0;
}
