#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

// Function to perform BFS traversal
void bfs(int start, const vector<vector<int>>& graph) {
    int total_nodes = graph.size();
    unordered_set<int> visited;
    queue<int> q;

    q.push(start);
    visited.insert(start);
    while(!q.empty()){
        int node = q.front();
        q.pop();

        cout << node << " " ;
        for(auto neighbor:graph[node]){
            if(visited.find(neighbor) == visited.end()){
                q.push(neighbor);
                visited.insert(neighbor);
            }
        }

    }
}

int main() {
    // Define the graph as an adjacency list
    vector<vector<int>> graph = {
        {1, 2},  // Node 0 is connected to nodes 1 and 2
        {0, 3},  // Node 1 is connected to nodes 0 and 3
        {0, 4},  // Node 2 is connected to nodes 0 and 4
        {1},     // Node 3 is connected to node 1
        {2}      // Node 4 is connected to node 2
    };

    // Perform BFS traversal starting from node 0
    bfs(0, graph);

    return 0;
}