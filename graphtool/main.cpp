#include <iostream>
#include <vector>
#include "Graph.h"

using namespace std;

int main() {

    // Beispiel aus https://de.wikipedia.org/wiki/Adjazenzmatrix oben
    vector<vector<int>> am1 = {
            {0, 1, 0, 0},
            {1, 0, 1, 1},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
    };

    Graph *g = new Graph(am1);

    cout << (g->getAdjacencyMatrix().at(0).at(1) == 1 ? "Zeile 1, Spalte 2 ist 1"
                                                           : "Zeile 1, Spalte 2 ist **NICHT** 1") << endl;

    // Number of  nodes
    cout << "Number of nodes: " << g->getNumberOfNodes() << endl;

    return 0;
}