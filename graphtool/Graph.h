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

public:
    Graph(vector<vector<int>> adjacencyMatrix);

    bool isSymmetricMatrix(const vector<vector<int>> &adjacencyMatrix) const;

    /**
     * Detect the number of nodes of the given graph.
     * @return number of nodes.
     */
    int getNumberOfNodes() const;

    /**
     * Export a given file with custom data.
     * @param fileName string file name.
     * @param data string of data.
     */
    void exportFile(const string fileName, const string data) const;

    /**
     * Return the graph in a json-format.
     * @return string json.
     */
    string graphToJson() const;

    const vector<vector<int>> &getAdjacencyMatrix() const;
};


