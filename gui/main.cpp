#include <iostream>
#include <vector>
#include "Graph.h"

using namespace std;

int main() {

    // Beispiel aus https://de.wikipedia.org/wiki/Adjazenzmatrix oben
    vector<vector<int>> am1 = {
            {0, 1, 0, 0},
            {1, 0, 0, 1},
            {0, 0, 0, 0},
            {0, 1, 0, 0}
    };

    vector<vector<int>> am2 = {
            {0, 1, 0, 0},
            {1, 0, 1, 0},
            {0, 0, 0, 1},
            {0, 0, 1, 0}
    };

    Graph *g = new Graph(am2);

    cout << "Graph G: " << endl;
    cout << "################################" << endl;

    for (int i = 0; i < g->getNumberOfNodes(); i++) {
        for (int j = 0; j < g->getNumberOfNodes(); j++) {

            cout << "hasConncetivity("<<i+1<<", "<<j+1<<"): " << g->hasConnectivity(i, j) << endl;
        }
    }
    //cout << "hasConncetivity(3, 0): " << g->hasConnectivity(3, 0) << endl;


/*
    cout << "A^0";
    g->coutMatrix(g->matrixPower(am1, 0));

    cout << "A^1";
    g->coutMatrix(g->matrixPower(am1, 1));

    cout << "A^2";
    g->coutMatrix(g->powerMatrix(am1, 2));
    g->coutMatrix(am1);

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
    cout << "has path: " << g->hasPath({1,2,1,2,1,0,1,3,1,2,3}) << endl;

    cout << "has conncetivity: " << g->hasConnectivity(0, 2) << endl;
*/

    return 0;
}