
#include <vector>
#include <stdexcept>
#include <fstream>
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
                edges += "\"source\": \"" + to_string(x) + "\",";
                edges += "\"target\": \"" + to_string(y) + "\",";
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