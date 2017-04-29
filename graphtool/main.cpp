#include <iostream>
#include <vector>
#include "Graph.h"

int main() {

    // Beispiel aus https://de.wikipedia.org/wiki/Adjazenzmatrix oben
    std::vector<std::vector<int>> am1 = {
            {0, 1, 0, 0},
            {1, 0, 1, 1},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
    };

    Graph *g = new Graph(am1);

    std::cout << (g->getAdjacencyMatrix().at(0).at(1) == 1 ? "Zeile 1, Spalte 2 ist 1"
                                                           : "Zeile 1, Spalte 2 ist **NICHT** 1") << std::endl;
    return 0;
}