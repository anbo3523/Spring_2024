#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void Graph::addVertex(string name){
    vertex* newVertex = new vertex;
    newVertex -> name = name;
    vertices.push_back(newVertex);
   
}

void Graph::addEdge(string v1, string v2){
    vertex* vertex1 = nullptr;
    vertex* vertex2 = nullptr;
    for (auto v : vertices){
        if(v -> name == v1)
            vertex1 = v;
        else if(v -> name == v2)
        vertex2 = v;
    }

    if(vertex1 == nullptr || vertex2 == nullptr)
        return;
    
    adjVertex adj1;
    adj1.v = vertex2;
    vertex1 -> adj.push_back(adj1);
    adjVertex adj2;
    adj2.v = vertex1;
    vertex2 -> adj.push_back(adj2);
}

void Graph::displayEdges(){
    for (auto v : vertices){
        cout << v -> name << " --> ";
        for(auto adj : v -> adj){
            cout << adj.v -> name << " ";
        }
        cout << endl;
    }
}

void Graph::breadthFirstTraverse(string sourceVertex){
    // Find the source vertex
    vertex* source = nullptr;
    for (auto v : vertices) {
        if (v->name == sourceVertex) {
            source = v;
            break;
        }
    }
    // If source vertex not found, return
    if (source == nullptr)
        return;
    
    // Perform BFS traversal
    queue<vertex*> q;
    q.push(source);
    source->visited = true;
    source->distance = 0;

    // Print the starting vertex for BFS traversal
    cout << "Starting vertex (root): " << source->name << "-> ";

    while (!q.empty()) {
        vertex* current = q.front();
        q.pop();

        // Print the name and distance of the current vertex
        if (current != source) {
            cout << current->name;
            if (current->distance != 0) // Print distance if not the source vertex and distance is non-zero
                cout << "(" << current->distance << ") ";
            else
                cout << " ";
        }

        for (auto adj : current->adj) {
            if (!adj.v->visited) {
                adj.v->visited = true;
                adj.v->distance = current->distance + 1;
                q.push(adj.v);
            }
        }
    }

    cout << endl << endl;
    

    // Reset visited flag and distances for next traversal
    for (auto v : vertices) {
        v->visited = false;
        v->distance = 0;
    }
}

/*
string::source : source vertex (starting city)
int::k : distance that you can travel from source city with remaining fuel
*/
vector<string> Graph::findReachableCitiesWithinDistanceK(string source, int k){
 // Find the source vertex
    vertex* sourceVertex = nullptr;
    for (auto v : vertices) {
        if (v->name == source) {
            sourceVertex = v;
            break;
        }
    }

    // If source vertex not found or distance limit is invalid, return empty vector
    if (sourceVertex == nullptr || k < 0)
        return {};

    // Perform BFS traversal to find reachable cities within distance k
    queue<pair<vertex*, int>> q;
    vector<string> reachableCities;
    q.push({sourceVertex, 0});
    sourceVertex->visited = true;

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        // Check if the current vertex is within distance k
        if (current.second == k) {
            reachableCities.push_back(current.first->name);
        } else if (current.second < k) {
            // Traverse adjacent vertices
            for (auto adj : current.first->adj) {
                if (!adj.v->visited) {
                    adj.v->visited = true;
                    q.push({adj.v, current.second + 1});
                }
            }
        }
    }

    // Reset visited flag for next traversal
    for (auto v : vertices) {
        v->visited = false;
    }

    // Reverse the order of reachable cities without using reverse function
    int left = 0;
    int right = reachableCities.size() - 1;
    while (left < right) {
        swap(reachableCities[left], reachableCities[right]);
        left++;
        right--;
    }

    return reachableCities;
}