
#include <vector>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include "Graph.h"

Graph::Graph(vector<vector<int>> adjacencyMatrix) {

    if (isSymmetricMatrix(adjacencyMatrix)) {
        this->adjacencyMatrix = adjacencyMatrix;
    } else {
        throw invalid_argument("adjacency matrix has to be symmetrical");
    };
}

bool Graph::isSymmetricMatrix(const vector<vector<int>> &adjacencyMatrix) const {
    int rows = (int) adjacencyMatrix.size();
    int cols = 0;
    for (vector<int> row : adjacencyMatrix) {
        if (row.size() > cols) {
            cols = (int) row.size();
        }
    }

    return rows == cols;
}

const vector<vector<int>> &Graph::getAdjacencyMatrix() const {
    return adjacencyMatrix;
}

/**
 * Detect the number of nodes of the given graph.
 * @return number of nodes.
 */
int Graph::getNumberOfNodes() const {
    return this->adjacencyMatrix.size();
}

/**
 * Transform the graph to json-format.
 * @return string json.
 */
string Graph::graphToJson() const {

    int size = this->adjacencyMatrix.size();

    string nodes = "\"nodes\": [";

    // parse json nodes
    for (int i = 0; i < size; i++) {
        nodes += "{ ";
        nodes += "\"id\": \"" + to_string(i) + "\",";
        nodes += "\"label\": \"" + to_string(i) + "\",";
        nodes += "\"x\": \"" + to_string(rand() % 10) + "\",";
        nodes += "\"y\": \"" + to_string(rand() % 10) + "\",";
        nodes += "\"size\": \"" + to_string(1) + "\"";

        if (i < (size - 1)) {
            nodes += "},";
        } else {
            nodes += "}";
        }
    }

    nodes += "]";

    string edges = "\"edges\": [";
    int y = 0;
    int id = 0;

    string edgeType = "arrow";

    // parse json edges
    for (vector<int> row : adjacencyMatrix) {

        // column
        for (int x = 0; x < row.size(); x++) {

            // if there is a connection between two nodes.
            if (row[x] == 1) {

                if (id == 0) {
                    // first element
                    edges += "{ ";
                } else {
                    edges += ", { ";
                }

                // set properties
                edges += "\"id\": \"" + to_string(id) + "\",";
                edges += "\"source\": \"" + to_string(y) + "\",";
                edges += "\"target\": \"" + to_string(x) + "\",";
                edges += "\"type\": \"" + edgeType + "\",";
                edges += "\"size\": \"" + to_string(1) + "\"";

                edges += "}";

                id++;
            }
        }
        y++;
    }

    edges += "]";

    return "{ " + nodes + ", " + edges + " }";
}

/**
 * Export a given file with custom data.
 * @param fileName string file name.
 * @param data string of data.
 */
void Graph::exportFile(const string fileName, const string data) const {
    ofstream file;
    file.open(fileName);
    file << data;
    file.close();
}

/**
 * Checks the graph if a cycle exists. DFS.
 * @return true if a cycle exists, else false
 */
bool Graph::hasCycle() {

    int nodes = this->getNumberOfNodes();

    // array for the visited nodes
    bool *visited = new bool[nodes];
    // array for the stack
    bool *stack = new bool[nodes];

    // set the default values to the stack and the visited nodes arrays
    for (int i = 0; i < nodes; i++) {
        visited[i] = false;
        stack[i] = false;
    }

    for (int i = 0; i < nodes; i++) {
        if (hasCycleRec(i, visited, stack)) {
            hasCycleCache = true;
            hasCycleFlag = true;
            return true;
        }
    }

    hasCycleFlag = true;
    return false;
}

/**
 * Private helper function for hasCycle function.
 * @param i current index.
 * @param visited array contains visited elements.
 * @param stack for recursion.
 * @return true if cycle found else false
 */
bool Graph::hasCycleRec(const int i, bool *visited, bool *stack) const {

    // check if node was not visited.
    if (!visited[i]) {
        visited[i] = true;
        stack[i] = true;

        // iterate through the given adja matrix row (i)
        for (int x = 0; x < this->getNumberOfNodes(); ++x) {
            if (adjacencyMatrix[x][i] > 0) {
                // if the current node has an edge
                if (!visited[x] && hasCycleRec(x, visited, stack)) {
                    // if node was not visited and there is a existing cycle
                    return true;
                } else if (stack[x]) {
                    // if the stack contains the current node
                    return true;
                }
            }
        }

    }

    // delete node from stack if the node was visited
    stack[i] = false;
    return false;
}

/**
 * Checks if the graph contains the given edge.
 * @param from node number
 * @param to node number
 * @return true if the edge exists, else if not
 */
bool Graph::hasEdge(const int from, const int to) const {
    if (!isDirectedFlag) {
        // isDirectedCache = isDirected();
    }

    if (isDirectedCache) {
        return adjacencyMatrix[from][to] > 0;
    } else {
        return adjacencyMatrix[from][to] > 0 && adjacencyMatrix[to][from] > 0;
    }

}

/**
 * Checks, if the graph contains the given path.
 * @param path vector with path nodes.
 * @return true if graph contains the path, else false
 */
bool Graph::hasPath(const vector<int> path) const {

    if (path.size() == 0) {
        throw invalid_argument("The vector must contain at least one value!");
    }

    for (int i = 0; i < path.size(); i++) {
        if (path[i] >= this->getNumberOfNodes()) {
            throw invalid_argument("The vector contains not existing nodes!");
        } else if (i + 1 < path.size() && adjacencyMatrix[path[i]][path[i + 1]] == 0) {
            return false;
        }
    }

    return true;
}
