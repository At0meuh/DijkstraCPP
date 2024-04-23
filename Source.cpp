#include "Node.h"

// Structure to handle the outputs of Dijkstra's algorithm
struct DijkstraOriginsOutputs {
    unordered_map<Node*, int> distances;  // Map to store distances from start node to each node
    unordered_map<Node*, Node*> origins;  // Map to store origins of each node on the shortest paths
};

// Function to perform Dijkstra's algorithm and return the distances and origins
DijkstraOriginsOutputs dijkstraOrigins(vector<Node*> graph, Node* start) {
    cout << "Dijkstra is Starting..." << endl << endl;
    string coutOutput = "";
    // Initialization
    const int infinity = 2147483647;
    unordered_map<Node*, int> distances;  // Map to store distances from start node to each node
    unordered_map<Node*, int> visited;    // Map to store visited nodes and their distances from start node
    unordered_map<Node*, Node*> origins;   // Map to store origins of each node on the shortest paths
    int modified_distance = -1;            // Variable to track modified distances
    Node* closest_node = start;          // Variable to track the closest node in each iteration

    // Set distance from every node except start to infinity in map called visited
    for (Node* node : graph) {
        visited[node] = infinity;
    }
    visited[start] = 0;

    // Initialize origins map with nullptr for each node
    for (Node* node : graph) {
        origins[node] = nullptr;
    }

    // Start Dijkstra's algorithm
    while (!visited.empty()) {
        int min_distance = infinity;
        for (pair<Node*, int> node : visited) {  // Iterate over visited nodes to find closest node
            if (node.second < min_distance) {
                min_distance = node.second;
                closest_node = node.first;
            }
        }

        for (pair<Node*, int> neighbor : closest_node->getNeighbors()) {  // Iterate over neighbors of closest_node
            if (distances.count(neighbor.first) == 0) {  // Check if neighbor has not been visited yet
                modified_distance = visited[neighbor.first];
                visited[neighbor.first] = min(visited[neighbor.first], visited[closest_node] + neighbor.second);  // Update distance if shorter path found
                if (modified_distance != visited[neighbor.first]) {  // Update origin if distance was modified
                    origins[neighbor.first] = closest_node;
                }
            }
        }
        distances[closest_node] = visited[closest_node];  // Update distances map with final distances
        visited.erase(closest_node);  // Remove closest_node from visited map
    }

    // Create an instance of DijkstraOriginsOutputs struct and assign distances and origins
    DijkstraOriginsOutputs output;
    output.distances = distances;
    output.origins = origins;

    return output;
}

// Function to reconstruct the path using Dijkstra's origins and print the path
vector<Node*> dijkstraPath(vector<Node*> graph, Node* start, Node* end) {
    // Call dijkstraOrigins to get distances and origins
    DijkstraOriginsOutputs dijkstraOriginsOutput = dijkstraOrigins(graph, start);

    // Reconstruct the path from end to start node
    vector<Node*> path;
    unordered_map<Node*, Node*> visited_origins = dijkstraOriginsOutput.origins;
    Node* current_node = end;
    while (current_node != nullptr) {
        path.emplace_back(current_node);  // Add current node to the path
        current_node = visited_origins[current_node];  // Move to the next node using the origins map
    }
    reverse(path.begin(), path.end());  // Reverse the path to obtain the correct order

    // Print the path with node names and distances
    cout << "Shortest Path: ";
    for (Node* node : path) {
        cout << node->getName() << " (" << dijkstraOriginsOutput.distances[node] << ") -> ";  // Print the name of each node in the path with its distance
    }
    cout << "End" << endl;  // Indicate the end of the path


    return path;  // Return the path vector
}

int main() {
    // Create graph nodes
    Node A("A");
    Node B("B");
    Node C("C");
    Node D("D");
    Node E("E");
    Node F("F");
    Node G("G");
    Node H("H");
    Node I("I");
    Node J("J");

    // Add neighbors for each node with the weight of each edge
    A.addNeighbor(&B, 85);
    A.addNeighbor(&C, 217);
    A.addNeighbor(&E, 173);

    B.addNeighbor(&F, 80);

    C.addNeighbor(&G, 186);
    C.addNeighbor(&H, 103);

    D.addNeighbor(&H, 183);

    E.addNeighbor(&J, 502);

    F.addNeighbor(&I, 250);

    H.addNeighbor(&J, 167);

    I.addNeighbor(&J, 84);

    // Add each node to the graph vector
    vector<Node*>  graph = { &A, &B, &C, &D, &E, &F, &G, &H, &I, &J };

    // Call dijkstraPath function to find and print the shortest path from start to end node
    dijkstraPath(graph, &A, &J);

    return 0;
}
