#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
using namespace std;

// Function to accumulate a range of elements
void accumulateRange(const std::vector<int>& data, int start, int end, int& result) {
    result = std::accumulate(data.begin() + start, data.begin() + end, 0);
}

// Function to accumulate a range of elements in parallel using threads
int parallelAccumulate(const std::vector<int>& data) {
    int numThreads = std::thread::hardware_concurrency();
    int chunkSize = data.size() / numThreads;
    std::vector<int> results(numThreads);
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? data.size() : (i + 1) * chunkSize;
        threads.emplace_back(accumulateRange, std::ref(data), start, end, std::ref(results[i]));
        /*
        push_back vs emplace_back
        push_back takes a copy of the element you want to add to the vector, whereas emplace_back constructs the element in-place,
        directly in the vector's memory
        */
    }

    for (auto& thread : threads) {
        thread.join();
    }

    int finalResult = 0;
    for (int result : results) {
        finalResult += result;
    }

    return finalResult;
}

int main() {
    std::vector<int> data(1000000); // Example data
    for (int i = 0; i < data.size(); ++i) {
        data[i] = i;
    }

    int result = parallelAccumulate(data);

    std::cout << "Result: " << result << std::endl;

    return 0;
}