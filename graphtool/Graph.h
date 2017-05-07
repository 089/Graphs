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
     * Cache for result of hasCycle function.
     */
    bool hasCycleCache = false;

    /**
     * Flag. Specifies whether the hasCycle function has been called already.
     */
    bool hasCycleFlag = false;

    /**
     * Cache for result of isDirected function.
     */
    bool isDirectedCache = false;

    /**
     * Flag. Specifies whether the isDirected function has been called already.
     */
    bool isDirectedFlag = false;


    /**
     * Private helper function for hasCycle function.
     * @param i current index.
     * @param visited array contains visited elements.
     * @param stack for recursion.
     * @return true if cycle found else false
     */
    bool hasCycleRec(const int i, bool *visited, bool *stack) const;

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

    /**
     * Checks the graph if a cycle exists. DFS.
     * @return true if a cycle exists, else false
     */
    bool hasCycle();

    /**
     * Checks if the graph contains the given edge.
     * @param from node number
     * @param to node number
     * @return true if the edge exists
     */
    bool hasEdge(const int from, const int to) const;

    const vector<vector<int>> &getAdjacencyMatrix() const;
};


