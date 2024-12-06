#include <iostream>
#include <string>

// Define a struct called Person
struct Person {
    // Public members by default
    int age;
    std::string name;
    float height;

    // Member function to display person's details
    void displayDetails() {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Age: " << age << std::endl;
        std::cout << "Height: " << height << std::endl;
    }
};

// Define another struct called Address
struct Address {
    std::string street;
    std::string city;
    std::string state;
    std::string zip;
};

// Define a struct called Employee that has a Person and an Address
struct Employee {
    Person person;
    Address address;

    // Member function to display employee's details
    void displayDetails() {
        std::cout << "Employee Details:" << std::endl;
        person.displayDetails();
        std::cout << "Address:" << std::endl;
        std::cout << "Street: " << address.street << std::endl;
        std::cout << "City: " << address.city << std::endl;
        std::cout << "State: " << address.state << std::endl;
        std::cout << "Zip: " << address.zip << std::endl;
    }
};

int main() {
    // Create an instance of Person
    Person person;
    person.age = 30;
    person.name = "John Doe";
    person.height = 1.75;

    // Display person's details
    std::cout << "Person Details:" << std::endl;
    person.displayDetails();

    // Create an instance of Address
    Address address;
    address.street = "123 Main St";
    address.city = "Anytown";
    address.state = "CA";
    address.zip = "12345";

    // Create an instance of Employee
    Employee employee;
    employee.person = person;
    employee.address = address;

    // Display employee's details
    employee.displayDetails();

    // Access members of Employee using dot operator
    std::cout << "Employee's Name: " << employee.person.name << std::endl;
    std::cout << "Employee's Street: " << employee.address.street << std::endl;

    return 0;
}