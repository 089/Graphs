#include "gtest/gtest.h"
#include "Graph.h"

TEST(graph_check, test_directed) {
    //this adjancency matrix is directed
    vector<vector<int>> am = {
            {0, 1, 0, 0},
            {1, 0, 1, 0},
            {0, 1, 0, 1},
            {0, 0, 1, 0}
    };
    Graph *g = new Graph(am);
    EXPECT_EQ(g->isDirected(), false);

}

TEST(graph_check, test_not_directed) {
    //this adjancency matrix is directed
    vector<vector<int>> am = {
            {0, 1, 0, 1},
            {1, 0, 1, 0},
            {0, 1, 0, 1},
            {0, 0, 1, 0}
    };
    Graph *g = new Graph(am);
    EXPECT_EQ(g->isDirected(), true);
}

TEST(graph_check, test_nr_edges_1) {
    //this adjancency matrix is directed
    vector<vector<int>> am = {
            {0, 1, 0, 0},
            {1, 0, 1, 0},
            {0, 1, 0, 1},
            {0, 0, 1, 0}
    };
    Graph *g = new Graph(am);
    EXPECT_EQ(g->getNumberOfEdges(), 3);
}

TEST(graph_check, test_nr_edges_2) {
    //this adjancency matrix is not directed
    vector<vector<int>> am = {
            {0, 1, 0, 1},
            {1, 0, 1, 0},
            {0, 1, 0, 1},
            {0, 0, 1, 0}
    };
    Graph *g = new Graph(am);
    EXPECT_EQ(g->getNumberOfEdges(), 7);
}

TEST(graph_check, test_has_cycle_1) {
    //this adjancency matrix has a cycle
    vector<vector<int>> am = {
            {0, 1, 1, 0},
            {1, 0, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
    };
    Graph *g = new Graph(am);
    EXPECT_EQ(g->hasCycle(), true);
}

TEST(graph_check, test_has_cycle_2) {
    //this adjancency matrix has no cycle
    vector<vector<int>> am = {
            {0, 1, 0, 0},
            {1, 0, 1, 0},
            {0, 1, 0, 1},
            {0, 0, 1, 0}
    };
    Graph *g = new Graph(am);
    EXPECT_EQ(g->hasCycle(), true);
}

TEST(graph_check, test_nr_of_nodes) {
    vector<vector<int>> am = {
            {0, 1, 0, 0},
            {1, 0, 1, 0},
            {0, 1, 0, 1},
            {0, 0, 1, 0}
    };
    Graph *g = new Graph(am);
    EXPECT_EQ(g->getNumberOfNodes(), 4);
}

TEST(graph_check, test_regular_1) {
    vector<vector<int>> am = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0},
    };
    Graph *g = new Graph(am);
    EXPECT_EQ(g->isRegular(), true);
}

TEST(graph_check, test_regular_2) {
    vector<vector<int>> am = {
            {0, 1, 1, 0},
            {1, 0, 1, 0},
            {1, 1, 0, 0},
            {1, 1, 0, 0},
    };
    Graph *g = new Graph(am);
    EXPECT_EQ(g->isRegular(), false);
}


TEST(graph_check, test_complete_1) {
    vector<vector<int>> am = {
            {0, 1, 1},
            {1, 0, 1},
            {1, 1, 0},
    };
    Graph *g = new Graph(am);
    EXPECT_EQ(g->isComplete(), true);
}

TEST(graph_check, test_complete_2) {
    vector<vector<int>> am = {
            {0, 1, 1, 0},
            {1, 0, 1, 0},
            {1, 1, 0, 0},
            {1, 1, 0, 0},
    };
    Graph *g = new Graph(am);
    EXPECT_EQ(g->isComplete(), false);
}

TEST(graph_check, test_indegree) {
    vector<vector<int>> am = {
            {0, 1, 1, 0},
            {1, 0, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
    };
    Graph *g = new Graph(am);
    EXPECT_EQ(g->getInDeg(0), 2);
    EXPECT_EQ(g->getInDeg(1), 2);
    EXPECT_EQ(g->getInDeg(2), 2);
    EXPECT_EQ(g->getInDeg(3), 0);
}

TEST(graph_check, test_outdegree) {
    vector<vector<int>> am = {
            {0, 1, 1, 0},
            {1, 0, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
    };
    Graph *g = new Graph(am);
    EXPECT_EQ(g->getOutDeg(0), 2);
    EXPECT_EQ(g->getOutDeg(1), 2);
    EXPECT_EQ(g->getOutDeg(2), 2);
    EXPECT_EQ(g->getOutDeg(3), 0);
}

TEST(graph_check, test_free_of_loops) {
    vector<vector<int>> am = {
            {0, 1, 1, 0},
            {1, 0, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
    };
    Graph *g = new Graph(am);
    EXPECT_TRUE(g->isFreeOfLoops());
}

TEST(graph_check, test_free_of_loops_2) {
    vector<vector<int>> am = {
            {0, 1, 1, 0},
            {1, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
    };
    Graph *g = new Graph(am);
    EXPECT_FALSE(g->isFreeOfLoops());
}