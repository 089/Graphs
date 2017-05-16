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

    /**
     * Cache for result of eponymous function.
     */
    bool isRegularCache = false;

    /**
     * Flag. Specifies whether the eponymous function has been called already.
     */
    bool isRegularFlag = false;

    /**
     * Private helper function for hasCycle function.
     * @param i current index.
     * @param visited array contains visited elements.
     * @param stack for recursion.
     * @return true if cycle found else false
     */
    bool hasCycleRec(const int i, bool *visited, bool *stack) const;

    /**
     * Auxiliary method to calculate the power of a matrix.
     *
     * @param squareMatrix  the matrix
     * @param exponent      the exponent
     *
     * @return the result as a matrix
     */
    vector<vector<int>> powerMatrix(vector<vector<int>> squareMatrix, int exponent);

    /**
     * Creates an identity matrix with the given size.
     *
     * @param size  size (rows and columns) of the matrix
     * @return identity matrix
     */
    vector<vector<int>> getIdentityMatrix(int size);

    /**
     * Multiplies two matrices A (l x m) and B (m x n).
     *
     * @param A matrix with l rows and m columns
     * @param B matrix with m rows and n columns
     *
     * @return the result as a matrix
     */
    vector<vector<int>> multiplyMatrix(const vector<vector<int>> &A, const vector<vector<int>> &B);

    /**
     * Adds two matrices A (m x n) and B (m x n).
     *
     * @param A matrix with m rows and n columns
     * @param B matrix with m rows and n columns
     *
     * @return the result as a matrix
     */
    vector<vector<int>> addMatrix(const vector<vector<int>> &A, const vector<vector<int>> &B);

    /**
     * Creates a matrix with zeroized elements.
     *
     * @param rows  number of rows
     * @param cols  number of columns
     *
     * @return a zeroized matrix
     */
    vector<vector<int>> getZeroizedMatrix(int rows, int cols);

    /**
     * Checks whether matrix A (m x n) and B (m x n) are identical.
     *
     * @param A matrix with m rows and n columns
     * @param B matrix with m rows and n columns
     *
     * @return true, if A = B
     */
    bool isSameMatrix(const vector<vector<int>> &A, const vector<vector<int>> &B);

public:
    Graph(vector<vector<int>> adjacencyMatrix);

    bool isSymmetricMatrix(const vector<vector<int>> &adjacencyMatrix) const;

    /**
     * Detect the number of nodes of the given graph.
     * @return number of nodes.
     */
    int getNumberOfNodes() const;

    /**
     * Detect the number of edges of the given graph.
     * @return number of edges.
     */
    int getNumberOfEdges();

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
     * @return true if the edge exists, else if not
     */
    bool hasEdge(const int from, const int to);

    /**
     * Checks, if the graph contains the given path.
     * @param path vector with path nodes.
     * @return true if graph contains the path, else false
     */
    bool hasPath(const vector<int> path) const;

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

    /**
     * Specifies whether the graph is a regular graph
     * (<a href="https://en.wikipedia.org/wiki/Regular_graph">
     * "is a graph where each vertex has the same number of neighbors"
     * </a>).
     *
     * @return  true, if the graph is a regular graph.
     */
    bool isRegular();

    /**
     * Calculates if there is a path from s to t.
     *
     * @param s number of node 1
     * @param t number of node 2
     * @return true, if there is a path from s to t.
     */
    bool hasConnectivity(int s, int t);

    /**
     * Exports the Graph to a dot file.
     * @return The string content for the dot file.
     */
    string exportDot();

    /**
     * Returns true, if both given vertices are neighbours in the graph.
     * The direction is only considered in digraphs.
     *
     * @param from    first vertice
     * @param to      second vertice
     * @return true, if both vertices are neighbours in the graph
     */
    bool areNeighbours(int from, int to);
};
