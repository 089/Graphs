
#include <vector>
#include <stdexcept>
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

int Graph::getInDeg(int vertexIndex) {

    if (vertexIndex < 0 || vertexIndex >= this->getNumberOfNodes()) {
        throw invalid_argument("vertex index has to be between 0 and n, but is " + to_string(vertexIndex) + ".");
    }

    // no value cached ==> calculate degree
    if (this->inDeg.empty()) {

        // count edges
        int countIngoingEdges = 0;
        for (int row = 0; row < this->getNumberOfNodes(); row++) {
            // adds ingoing edges
            countIngoingEdges += this->adjacencyMatrix[row][vertexIndex];

            // In undirected graphs loops are counted twice:
            if (row == vertexIndex && !this->isDirected()) {
                countIngoingEdges++;
            }
        }

        // setting cache value
        this->inDeg.resize(this->getNumberOfNodes());
        this->inDeg[vertexIndex] = countIngoingEdges;
    }

    return this->inDeg[vertexIndex];
}

int Graph::getOutDeg(int vertexIndex) {

    if (vertexIndex < 0 || vertexIndex >= this->getNumberOfNodes()) {
        throw invalid_argument("vertex index has to be between 0 and n, but is " + to_string(vertexIndex) + ".");
    }

    // no value cached ==> calculate degree
    if (this->outDeg.empty()) {

        // count edges
        int countOutgoingEdges = 0;
        for (int col = 0; col < this->getNumberOfNodes(); col++) {
            // adds ingoing edges
            countOutgoingEdges += this->adjacencyMatrix[vertexIndex][col];

            // In undirected graphs loops are counted twice:
            if (col == vertexIndex && !this->isDirected()) {
                countOutgoingEdges++;
            }
        }

        // setting cache value
        this->outDeg.resize(this->getNumberOfNodes());
        this->outDeg[vertexIndex] = countOutgoingEdges;
    }

    return this->outDeg[vertexIndex];
}

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
                    // values must be the same, otherwise its a digraph
                    if (this->getAdjacencyMatrix()[row][col] != this->getAdjacencyMatrix()[col][row]) {
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

bool Graph::isFreeOfLoops() {

    if (isFreeOfLoopsFlag) {
        return isFreeOfLoopsCache;
    }

    isFreeOfLoopsFlag = true;

    for (int mainDiagonal = 0; mainDiagonal < this->getNumberOfNodes(); ++mainDiagonal) {
        // check if there is a loop
        if (this->getAdjacencyMatrix()[mainDiagonal][mainDiagonal] > 0) {
            isFreeOfLoopsCache = false;
            return isFreeOfLoopsCache;
        }
    }

    isFreeOfLoopsCache = true;
    return isFreeOfLoopsCache;
}

bool Graph::isMultigraph() {

    if (isMultigraphFlag) {
        return isMultigraphCache;
    }

    isMultigraphFlag = true;

    /*
     * if the adjacency matrix contains a value greater than 1 the matrix
     * has multiple edges and therefore the graph is a multigraph.
     */
    for (int row = 0; row < this->getNumberOfNodes(); ++row) {
        for (int col = 0; col < this->getNumberOfNodes(); ++col) {
            if (this->getAdjacencyMatrix()[row][col] > 1) {
                isMultigraphCache = true;
                return isMultigraphCache;
            }
        }
    }

    isMultigraphCache = false;
    return isMultigraphCache;
}

bool Graph::isSimple() {
    return !this->isDirected() && !isMultigraph() && isFreeOfLoops();
}

bool Graph::isComplete() {

    if (isCompleteFlag) {
        return isCompleteCache;
    }

    isCompleteFlag = true;


    /*
     * the graph is complete if the adjacency matrix has only entries of 1
     * except the main diagonal which must be 0.
     */
    if (!isFreeOfLoops()) {
        isCompleteCache = false;
        return isCompleteCache;
    }

    for (int row = 0; row < this->getNumberOfNodes(); row++) {
        for (int col = 0; col < this->getNumberOfNodes(); col++) {
            // only 1 is allowed now
            if (row != col && this->getAdjacencyMatrix()[row][col] != 1) {
                isCompleteCache = false;
                return isCompleteCache;
            }
        }
    }

    isCompleteCache = true;
    return isCompleteCache;
}