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
            {0, 1, 0, 0}
    };

    Graph *g = new Graph(am1);

    cout << (g->getAdjacencyMatrix().at(0).at(1) == 1 ? "Zeile 1, Spalte 2 ist 1"
                                                           : "Zeile 1, Spalte 2 ist **NICHT** 1") << endl;

    // Number of  nodes
    cout << "Number of nodes: " << g->getNumberOfNodes() << endl;

    // Export for sigma js
    g->exportFile("data.json", g->graphToJson());

    // Has cycle
    cout << "cycle: " << g->hasCycle() << endl;

    // Has edge
    cout << g->hasEdge(0,1) << endl;

    // Has path
    cout << "has path: " << g->hasPath({1,2,1,2,1,0,1,3,1,2,3});

    return 0;
}