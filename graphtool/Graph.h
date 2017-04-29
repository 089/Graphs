#pragma once

#include <vector>

/**
 * Represents a graph. Has certain verifiable properties.
 */
class Graph {

private:
    std::vector<std::vector<int>> adjacencyMatrix;

public:
    Graph(std::vector<std::vector<int>> adjacencyMatrix);

    bool isSymmetricMatrix(const std::vector<std::vector<int>> &adjacencyMatrix) const;

    const std::vector<std::vector<int>> &getAdjacencyMatrix() const;
};


