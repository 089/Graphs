
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

int Graph::getInDeg(int vertexIndex) {

    if (vertexIndex < 0 || vertexIndex >= this->getNumberOfNodes()) {
        throw invalid_argument("vertex index has to be between 0 and n, but is " + to_string(vertexIndex) + ".");
    }

    // no value cached ==> calculate degree
    if (this->inDeg.empty() || this->inDeg[vertexIndex] < 1) {

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
    if (this->outDeg.empty() || this->outDeg[vertexIndex] < 1) {

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

bool Graph::isRegular() {

    if (isRegularFlag) {
        return isRegularCache;
    }

    isRegularFlag = true;

    // get in/out deg of the first vertex
    int inDegOfFirstVertex = this->getInDeg(0);
    int outDegOfFirstVertex = this->getOutDeg(0);

    // all other vertices must have the same deg,
    // otherwise this graph is not regular
    for (int vertex = 1; vertex < this->getNumberOfNodes(); vertex++) {


        // directed graph ==> indeg and outdeg can differ ==> we have to test both
        // undirected graph ==> indeg and outdeg must be the same ==> we only must test one
        // ==> we can use the following commands for both types
        if (this->getInDeg(vertex) != inDegOfFirstVertex || this->getOutDeg(vertex) != outDegOfFirstVertex) {
            isRegularCache = false;
            return isRegularCache;
        }

    }

    isRegularCache = true;
    return isRegularCache;
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
                edges += "\"source\": \"" + to_string(y) + "\",";
                edges += "\"target\": \"" + to_string(x) + "\",";
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

/**
 * Checks the graph if a cycle exists. DFS.
 * @return true if a cycle exists, else false
 */
bool Graph::hasCycle() {

    int nodes = this->getNumberOfNodes();

    // array for the visited nodes
    bool *visited = new bool[nodes];
    // array for the stack
    bool *stack = new bool[nodes];

    // set the default values to the stack and the visited nodes arrays
    for (int i = 0; i < nodes; i++) {
        visited[i] = false;
        stack[i] = false;
    }

    for (int i = 0; i < nodes; i++) {
        if (hasCycleRec(i, visited, stack)) {
            hasCycleCache = true;
            hasCycleFlag = true;
            return true;
        }
    }

    hasCycleFlag = true;
    return false;
}

/**
 * Private helper function for hasCycle function.
 * @param i current index.
 * @param visited array contains visited elements.
 * @param stack for recursion.
 * @return true if cycle found else false
 */
bool Graph::hasCycleRec(const int i, bool *visited, bool *stack) const {

    // check if node was not visited.
    if (!visited[i]) {
        visited[i] = true;
        stack[i] = true;

        // iterate through the given adja matrix row (i)
        for (int x = 0; x < this->getNumberOfNodes(); ++x) {
            if (adjacencyMatrix[x][i] > 0) {
                // if the current node has an edge
                if (!visited[x] && hasCycleRec(x, visited, stack)) {
                    // if node was not visited and there is a existing cycle
                    return true;
                } else if (stack[x]) {
                    // if the stack contains the current node
                    return true;
                }
            }
        }

    }

    // delete node from stack if the node was visited
    stack[i] = false;
    return false;
}

/**
 * Checks if the graph contains the given edge.
 * @param from node number
 * @param to node number
 * @return true if the edge exists, else if not
 */
bool Graph::hasEdge(const int from, const int to) {

    if (isDirected()) {
        return adjacencyMatrix[from][to] > 0;
    } else {
        return adjacencyMatrix[from][to] > 0 && adjacencyMatrix[to][from] > 0;
    }

}

/**
 * Checks, if the graph contains the given path.
 * @param path vector with path nodes.
 * @return true if graph contains the path, else false
 */
bool Graph::hasPath(const vector<int> path) const {

    if (path.size() == 0) {
        throw invalid_argument("The vector must contain at least one value!");
    }

    for (int i = 0; i < path.size(); i++) {
        if (path[i] >= this->getNumberOfNodes()) {
            throw invalid_argument("The vector contains not existing nodes!");
        } else if (i + 1 < path.size() && adjacencyMatrix[path[i]][path[i + 1]] == 0) {
            return false;
        }
    }

    return true;
}
