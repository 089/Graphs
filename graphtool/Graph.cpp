
#include <vector>
#include <stdexcept>
#include <fstream>
#include <algorithm>
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
    return (int) this->adjacencyMatrix.size();
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
            if (adjacencyMatrix[row][vertexIndex] > 0 && row == vertexIndex && !this->isDirected()) {
                countIngoingEdges++;
            }
        }

        // setting cache value
        this->inDeg.resize((unsigned long) this->getNumberOfNodes());
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
            if (adjacencyMatrix[vertexIndex][col] > 0 && col == vertexIndex && !this->isDirected()) {
                countOutgoingEdges++;
            }
        }

        // setting cache value
        this->outDeg.resize((unsigned long) this->getNumberOfNodes());
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

    int size = (int) this->adjacencyMatrix.size();

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

    if (hasCycleFlag) {
        return hasCycleCache;
    }

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
    hasCycleCache = false;
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

bool Graph::hasConnectivity(int s, int t) {

    if (s < 0 || s > getNumberOfNodes() - 1) {
        throw invalid_argument("invalid s");
    } else if (t < 0 || t > getNumberOfNodes() - 1) {
        throw invalid_argument("invalid t");
    }

    // there is a direct connection form s to t
    if (getAdjacencyMatrix()[s][t] > 0) {
        return true;
    }

    // loops are not allowed if adjacency matrix has none there
    if (s == t && getAdjacencyMatrix()[s][t] == 0) {
        return false;
    }

    // there is no direct connection from s to t
    // test if there are any connections using idea from
    // https://de.wikipedia.org/wiki/Adjazenzmatrix#Pfadl.C3.A4nge_in_Graphen_berechnen
    // we skip identity (A^0) and original adjacency matrix (A^1) ==> start at k = 2
    for (int k = 2; k < getNumberOfNodes(); ++k) {

        vector<vector<int>> tmp = powerMatrix(getAdjacencyMatrix(), k);

        if (tmp[s][t] > 0) {
            return true;
        }
    }

    return false;
}

bool Graph::isSameMatrix(const vector<vector<int>> &A, const vector<vector<int>> &B) {

    if (A.size() != B.size() || A[0].size() != B[0].size()) {
        return false;
    }

    // rows of A
    for (int i = 0; i < A.size(); i++) {
        // cols of A
        for (int j = 0; j < A[0].size(); j++) {
            if (A[i][j] != B[i][j]) {
                return false;
            }
        }
    }

    return true;
}

vector<vector<int>> Graph::getZeroizedMatrix(int rows, int cols) {

    // initialize an empty square matrix
    vector<vector<int>> resultMatrix = vector<vector<int>>((unsigned long) rows);

    // only diagonal is 1
    for (int diagonal = 0; diagonal < rows; diagonal++) {
        // set row to 0
        resultMatrix[diagonal] = vector<int>((unsigned long) cols, 0);
    }

    return resultMatrix;
}

vector<vector<int>> Graph::getIdentityMatrix(int size) {

    // initialize an empty square matrix
    vector<vector<int>> resultMatrix = getZeroizedMatrix(size, size);

    // set diagonal to 1
    for (int diagonal = 0; diagonal < size; diagonal++) {
        resultMatrix[diagonal][diagonal] = 1;
    }

    return resultMatrix;
}

vector<vector<int>> Graph::powerMatrix(vector<vector<int>> squareMatrix, int exponent) {

    // initialize an empty square matrix
    vector<vector<int>> resultMatrix;

    if (exponent < 0) {
        throw invalid_argument("not implemented yet");

    } else if (exponent == 0) {
        resultMatrix = getIdentityMatrix((int) squareMatrix.size());

    } else if (exponent == 1) {
        return squareMatrix;

    } else {
        resultMatrix = getIdentityMatrix((int) squareMatrix.size());

        for (int multiplyIndex = 0; multiplyIndex < exponent; multiplyIndex++) {
            resultMatrix = multiplyMatrix(resultMatrix, squareMatrix);
        }
    }

    return resultMatrix;
}

vector<vector<int>> Graph::multiplyMatrix(const vector<vector<int>> &A, const vector<vector<int>> &B) {
    // rows of A
    int l = (int) A.size();

    // cols of A MUST BE rows of B
    int m = (int) A[0].size();
    if (A[0].size() != B.size()) {
        throw invalid_argument("Matrix A must have as much rows as B columns. ");
    }

    // cols of B
    int n = (int) B[0].size();

    vector<vector<int>> C = getZeroizedMatrix(l, n);

    // multiply matrix c_{ij} = \sum_{j=1}^{m} a_{ij} \cdot \b_{jk}
    // loop over rows of C
    for (int i = 0; i < l; i++) {
        // loop over columns of C
        for (int k = 0; k < n; k++) {
            // loop over columns of A/rows of B
            for (int j = 0; j < m; j++) {
                C[i][k] = C[i][k] + A[i][j] * B[j][k];
            }
        }
    }

    return C;
}

vector<vector<int>> Graph::addMatrix(const vector<vector<int>> &A, const vector<vector<int>> &B) {

    if (A.size() != B.size() || A[0].size() != B[0].size()) {
        throw invalid_argument("Matrix A and B must have the same size (rows and columns). ");
    }

    // rows of A
    int m = (int) A.size();

    // cols of A MUST BE rows of B
    int n = (int) A[0].size();

    vector<vector<int>> C = getZeroizedMatrix(m, n);

    // add matrix
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

int Graph::getNumberOfEdges() {
    if (adjacencyMatrix.size() <= 0) {
        return 0;
    }
    int count = 0;
    long end = adjacencyMatrix.size();
    for (long i = 0; i < end; i++) {
        for (long j = 0; j < end; j++) {
            if (adjacencyMatrix[i][j]) {
                count++;
            }
        }
    }
    if (!isDirected()) {
        count /= 2;
    }
    return count;
}

string Graph::exportDot() {
    string data = "";
    if (isDirected()) { data += "digraph {\n"; } else { data += "graph {\n"; }

    //create nodes - in case one node has no edges
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        data += to_string(i) + "\n";
    }

    for (int x = 0; x < adjacencyMatrix.size(); x++) {
        if (!isDirected()) {
            for (long y = 0; y <= x; y++) {
                if (adjacencyMatrix[x][y] > 0) {
                    data += "\t" + to_string(x);
                    data += " -- ";
                    data += to_string(y);
                }
            }
        } else {
            for (int y = 0; y < adjacencyMatrix.size(); y++) {
                if (adjacencyMatrix[x][y] > 0) {
                    data += "\t" + to_string(x);
                    data += " -> ";
                    data += to_string(y);
                }
            }
        }
    }
    data += "\n}\n";
    return data;
}

bool Graph::isSimplePath(vector<int> path) const {

    if (!hasPath(path))
        throw invalid_argument("the given path is not part of the graph!");

    // sort the vector
    sort(path.begin(), path.end());

    // find duplicates
    for (int i = 0; i < path.size() - 1; i++) {
        if (path[i] == path[i+1]) {
            return false;
        }
    }
    return true;
}


