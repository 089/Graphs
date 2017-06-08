#include <iostream>
#include <vector>
#include "Graph.h"

using namespace std;

int main() {

    // Beispiel aus https://de.wikipedia.org/wiki/Adjazenzmatrix oben
    vector<vector<int>> am1 = {
            {0, 1, 1, 0, 0},
            {1, 0, 1, 1, 0},
            {1, 1, 0, 0, 0},
            {0, 1, 0, 0, 1},
            {0, 0, 0, 1, 0}
    };

    vector<vector<int>> am2 = {
            {0, 1, 0, 0},
            {1, 0, 1, 0},
            {0, 0, 0, 1},
            {0, 0, 1, 0}
    };

    Graph *g = new Graph(am2);

    cout << "Adjacency Matrix: " << endl;
    cout << g->getAdjacencyMatrixString() << endl;

    Graph *h = new Graph(" [1  0 1  ; 1    1\t   1  ; 0 0 1   ]    ");

    cout << h->exportDot();

/*    cout << (g->getAdjacencyMatrix().at(0).at(1) == 1 ? "Zeile 1, Spalte 2 ist 1"
                                                      : "Zeile 1, Spalte 2 ist **NICHT** 1") << endl;

    // Number of  nodes
    cout << "Number of nodes: " << g->getNumberOfNodes() << endl;

    Graph *g2 = new Graph(am1);
    cout << "Number of edges: " << g->getNumberOfEdges() << ", " << g2->getNumberOfEdges() << endl;
    // Export for sigma js
    g->exportFile("../website/data/data.json", g->graphToJson());

    // Has cycle
    cout << "cycle: " << g->hasCycle() << endl;

    // Has edge
    cout << g->hasEdge(0, 1) << endl;

    // Has path
    cout << "has path: " << g->hasPath({1, 2, 1, 2, 1, 0, 1, 3, 1, 2, 3}) << endl;

    cout << "has conncetivity: " << g->hasConnectivity(0, 2) << endl;

    cout << "Erreichbarkeiten in Graph G: " << endl;
    for (int i = 0; i < g->getNumberOfNodes(); i++) {
        for (int j = 0; j < g->getNumberOfNodes(); j++) {

            cout << "hasConncetivity(" << i + 1 << ", " << j + 1 << "): " << g->hasConnectivity(i, j) << endl;
        }
    }

    //can be opened by calling this - requires graphviz & imagemagick
    //dot -Tpng dotfile.dot > Graph.png && display Graph.png
    g2->exportFile("/tmp/dotfile.dot", g2->exportDot());
*/
    return 0;
}