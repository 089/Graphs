#pragma once

#include <vector>

using namespace std;

/**
 * Represents a graph. Has certain verifiable properties.
 */
class Graph {

private:
    vector<vector<int>> adjacencyMatrix;

public:
    Graph(vector<vector<int>> adjacencyMatrix);

    bool isSymmetricMatrix(const vector<vector<int>> &adjacencyMatrix) const;

    /**
     * Detect the number of nodes of the given graph.
     * @return number of nodes.
     */
    int getNumberOfNodes() const;

    const vector<vector<int>> &getAdjacencyMatrix() const;
};


