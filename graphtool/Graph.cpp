
#include <vector>
#include <stdexcept>
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
 * Returns if the graph is a directed or undirected graph.
 *
 * @return  true, if directed<br>
 *          false, if undirected
 */
bool Graph::isDirected() {

    // Get cached result.
    switch (this->type) {
        case DIRECTED:
            return true;

        case UNDIRECTED:
            return false;

        case UNCHECKED:
            // check if values of the adjacency matrix are set symmetrically ==> undirected graph
            // otherwise diagraph
            for (int row = 0; row < this->getNumberOfNodes(); row++) {
                // check only upper triangle part of matrix
                for (int col = row + 1; col < this->getNumberOfNodes(); col++) {
                    cout << "here" << endl;
                    // values must be the same, otherwise its a digraph
                    if(this->getAdjacencyMatrix()[row][col] != this->getAdjacencyMatrix()[col][row]) {
                        // cache result
                        this->type = DIRECTED;
                        return true;
                    }
                }
            }

            break;
    }

    // cache result
    this->type = UNDIRECTED;
    return false;
}