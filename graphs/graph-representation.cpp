/*
Graph Representation

There are several ways to represent a graph in computer science, each with its own strengths and weaknesses. Here are some common graph representations:

1. Adjacency Matrix: An adjacency matrix is a matrix where the entry at row i and column j represents the weight of the edge between node i and node j. If there is no edge between the nodes, the entry is typically 0.
Example:

int adjacencyMatrix[4][4] = {
  {0, 1, 1, 0},
  {1, 0, 0, 1},
  {1, 0, 0, 1},
  {0, 1, 1, 0}
};

2. Adjacency List: An adjacency list is a collection of lists, where each list represents a node and contains its neighboring nodes.
Example:

std::vector<std::list<int>> adjacencyList = {
  {1, 2}, // node 0 is connected to nodes 1 and 2
  {0, 3}, // node 1 is connected to nodes 0 and 3
  {0, 3}, // node 2 is connected to nodes 0 and 3
  {1, 2}  // node 3 is connected to nodes 1 and 2
};


3. Edge List: An edge list is a collection of edges, where each edge is represented by a pair of nodes.
Example:

std::vector<std::pair<int, int>> edgeList = {
  {0, 1},
  {0, 2},
  {1, 3},
  {2, 3}
};

*/
#include <iostream>
#include <vector>
#include <list>
#include <utility>

// Define a struct to represent an edge
struct Edge {
    int node1;
    int node2;
};

// Define a class to represent a graph
class Graph {
private:
    // Adjacency matrix representation
    std::vector<std::vector<int>> adjacencyMatrix;

    // Adjacency list representation
    std::vector<std::list<int>> adjacencyList;

    // Edge list representation
    std::vector<Edge> edgeList;
public:
    // Constructor to initialize the graph
    Graph(int numNodes) {
        // Initialize the adjacency matrix
        adjacencyMatrix.resize(numNodes);
        for (int i = 0; i < numNodes; i++) {
            adjacencyMatrix[i].resize(numNodes, 0);
        }

        // Initialize the adjacency list
        adjacencyList.resize(numNodes);

        // Initialize the edge list
        edgeList.clear();
    }

    // Add an edge to the graph
    void addEdge(int node1, int node2) {
        // Add the edge to the adjacency matrix
        adjacencyMatrix[node1][node2] = 1;
        adjacencyMatrix[node2][node1] = 1; // for undirected graph

        // Add the edge to the adjacency list
        adjacencyList[node1].push_back(node2);
        adjacencyList[node2].push_back(node1); // for undirected graph

        // Add the edge to the edge list
        edgeList.push_back({node1, node2});
    }

    // Print the adjacency matrix
    void printAdjacencyMatrix() {
        std::cout << "Adjacency Matrix:" << std::endl;
        for (int i = 0; i < adjacencyMatrix.size(); i++) {
            for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
                std::cout << adjacencyMatrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    // Print the adjacency list has a bug
    // void printAdjacencyList() {
    //     std::cout << "Adjacency List:" << std::endl;
    //     for (int i = 0; i < adjacencyList.size(); i++) {
    //         std::cout << "Node " << i << " is connected to: ";
    //         for (int j = 0; j < adjacencyList[i].size(); j++) {
    //             std::cout << adjacencyList[i][j] << " ";
    //         }
    //         std::cout << std::endl;
    //     }
    // }


    // Print the adjacency list
    void printAdjacencyList() {
        std::cout << "Adjacency List:" << std::endl;
        for (int i = 0; i < adjacencyList.size(); i++) {
            std::cout << "Node " << i << " is connected to: ";
            for (auto& neighbor : adjacencyList[i]) {
                std::cout << neighbor << " ";
            }
            std::cout << std::endl;
        }
    }

    // Print the edge list
    void printEdgeList() {
        std::cout << "Edge List:" << std::endl;
        for (int i = 0; i < edgeList.size(); i++) {
            std::cout << "Edge (" << edgeList[i].node1 << ", " << edgeList[i].node2 << ")" << std::endl;
        }
    }


};

int main() {
    // Create a graph with 4 nodes
    Graph graph(4);

    // Add edges to the graph
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);

    // Print the adjacency matrix
    graph.printAdjacencyMatrix();

    // Print the adjacency list
    graph.printAdjacencyList();

    // Print the edge list
    graph.printEdgeList();

    return 0;
}