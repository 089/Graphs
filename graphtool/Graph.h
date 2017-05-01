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

    /**
     * Cache for result of eponymous function.
     */
    bool isFreeOfLoopsCache = false;

    /**
     * Flag. Specifies whether the eponymous function has been called already.
     */
    bool isFreeOfLoopsFlag = false;

    /**
     * Cache for result of eponymous function.
     */
    bool isMultigraphCache = false;

    /**
     * Flag. Specifies whether the eponymous function has been called already.
     */
    bool isMultigraphFlag = false;

    /**
     * Cache for result of eponymous function.
     */
    bool isCompleteCache = false;

    /**
     * Flag. Specifies whether the eponymous function has been called already.
     */
    bool isCompleteFlag = false;

public:
    Graph(vector<vector<int>> adjacencyMatrix);

    bool isSymmetricMatrix(const vector<vector<int>> &adjacencyMatrix) const;

    /**
     * Detect the number of nodes of the given graph.
     * @return number of nodes.
     */
    int getNumberOfNodes() const;

    const vector<vector<int>> &getAdjacencyMatrix() const;

    /**
     * Returns if the graph is a directed or undirected graph.
     *
     * @return  true, if directed<br>
     *          false, if undirected
     */
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

    /**
     * Specifies whether the graph is free of loops.
     * Loops are edges from and to the same vertex.
     *
     * @return true, if there are no loops in the graph.
     */
    bool isFreeOfLoops();

    /**
     * Specifies whether the graph is a multigraph (has multiple edges/has
     * <a href="https://en.wikipedia.org/wiki/Graph_(discrete_mathematics)#Multigraph">
     * "two or more edged that connect the same two vertices"</a>)
     *
     * @return true, if it is a multigraph
     */
    bool isMultigraph();

    /**
     * Specifies whether the graph is a simple graph (undirected, no multiple
     * edges, no loops) or not.
     *
     * @return  true, if the graph is a simple graph.
     */
    bool isSimple();

    /**
     * Specifies whether the graph is a complete graph (simple graph
     * <a href="https://en.wikipedia.org/wiki/Complete_graph">"in which every
     * pair of distinct vertices is connected by a unique edge."</a>).
     * Checks only undirected graphs! A complete graph is also called K_n.
     *
     * @return  true, if the graph is a complete graph.
     */
    bool isComplete();
};


