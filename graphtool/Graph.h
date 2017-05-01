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
    enum Type {
        UNCHECKED, DIRECTED, UNDIRECTED
    };

    /**
     * type of the graph ({@see Type).
     */
    Type type = UNCHECKED;

    /**
     * Contains the <b>ingoing</b> degrees of the individual vertices.
     */
    vector<int> inDeg;

    /**
     * Contains the <b>outgoing</b> degrees of the individual vertices.
     */
    vector<int> outDeg;

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

    /**
     * Returns indegree indeg(v). Therefore it counts the ingoing edges.
     * In undirected graphs loops are counted twice.
     *
     * @param vertexIndex   the index of the vertex v
     * @return indegree indeg(v)
     */
    int getInDeg(int vertexIndex);

    /**
     * Returns outdegree outdeg(v). Therefore it counts the outgoing edges.
     * In undirected graphs loops are counted twice.
     *
     * @param vertexIndex   the index of the vertex v
     * @return outdegree outdeg(v)
     */
    int getOutDeg(int vertexIndex);
};


