#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
private:
    int V;  // nodes in the graph
    vector<vector<int>> adjList;

public:
    Graph(int v) : V(v), adjList(v) {}

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void dfs(int start) {
        // DFS iterative
        stack<int> stack;
        vector<bool> visited(V, false);

        stack.push(start);
        visited[start] = true;

        while (!stack.empty()) {
            int curr = stack.top();
            stack.pop();

            cout << curr << " ";

            for (int neighbor : adjList[curr]) {
                if (!visited[neighbor]) {
                    stack.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
    }

    void dfsRecursive(int start, vector<bool>& visited) {
        visited[start] = true;
        cout << start << " ";

        for (int neighbor : adjList[start]) {
            if (!visited[neighbor]) {
                dfsRecursive(neighbor, visited);
            }
        }
    }

    void dfsRecursiveWrapper(int start) {
        vector<bool> visited(V, false);
        dfsRecursive(start, visited);
    }
};

int main() {
    Graph graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);

    cout << "Iterative DFS: ";
    graph.dfs(0);
    cout << endl;

    cout << "Recursive DFS: ";
    graph.dfsRecursiveWrapper(0);
    cout << endl;

    return 0;
}