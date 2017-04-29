
#include <vector>
#include <stdexcept>
#include "Graph.h"

Graph::Graph(std::vector<std::vector<int>> adjacencyMatrix) {

    if (isSymmetricMatrix(adjacencyMatrix)) {
        this->adjacencyMatrix = adjacencyMatrix;
    } else {
        throw std::invalid_argument("adjacency matix must be symmetrical");
    };
}

boolean Graph::isSymmetricMatrix(const std::vector<std::vector<int>> &adjacencyMatrix) const {
    int rows = (int) adjacencyMatrix.size();
    int cols = 0;
    for (std::vector<int> row : adjacencyMatrix) {
        if (row.size() > cols) {
            cols = (int) row.size();
        }
    }

    return rows == cols;
}

const std::vector<std::vector<int>> &Graph::getAdjacencyMatrix() const {
    return adjacencyMatrix;
}