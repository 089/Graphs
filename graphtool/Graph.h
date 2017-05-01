#pragma once

#include <vector>

using namespace std;

/**
 * Represents a <b>simple</b> or <b>directed</b> graph. Has certain verifiable
 * properties. Its edges are not weighted.
 */
class Graph {

private:
    /**
     * the adjacency matrix
     */   
    vector<vector<int>> adjacencyMatrix;

    /**
     * Possible types of the graph: unchecked, directed or undirected.
     */
    enum Type { UNCHECKED, DIRECTED, UNDIRECTED};

    /**
     * type of the graph ({@see Type).
     */
    Type type = UNCHECKED;

public:
    Graph(vector<vector<int>> adjacencyMatrix);

    bool isSymmetricMatrix(const vector<vector<int>> &adjacencyMatrix) const;

    /**
     * Detect the number of nodes of the given graph.
     * @return number of nodes.
     */
    int getNumberOfNodes() const;

    const vector<vector<int>> &getAdjacencyMatrix() const;

    bool isDirected();
};


