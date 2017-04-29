#pragma once

#include <vector>
#include <jmorecfg.h>

/**
 * Represents a graph. Has certain verifiable properties.
 */
class Graph {

private:
    std::vector<std::vector<int>> adjacencyMatrix;

public:
    Graph(std::vector<std::vector<int>> adjacencyMatrix);

    boolean isSymmetricMatrix(const std::vector<std::vector<int>> &adjacencyMatrix) const;

    const std::vector<std::vector<int>> &getAdjacencyMatrix() const;
};


