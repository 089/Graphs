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

TEST(graph_check, test_are_neighbours_1) {
    vector<vector<int>> am = {
            {0, 1, 1, 0},
            {1, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
    };
    Graph *g = new Graph(am);
    EXPECT_FALSE(g->areNeighbours(0, 0));
    EXPECT_FALSE(g->areNeighbours(0, 3));
    EXPECT_FALSE(g->areNeighbours(1, 3));
    EXPECT_FALSE(g->areNeighbours(2, 2));
    EXPECT_FALSE(g->areNeighbours(2, 3));
    EXPECT_FALSE(g->areNeighbours(3, 0));
    EXPECT_FALSE(g->areNeighbours(3, 1));
    EXPECT_FALSE(g->areNeighbours(3, 2));
    EXPECT_FALSE(g->areNeighbours(3, 3));

    EXPECT_TRUE(g->areNeighbours(0, 1));
    EXPECT_TRUE(g->areNeighbours(0, 2));
    EXPECT_TRUE(g->areNeighbours(1, 0));
    EXPECT_TRUE(g->areNeighbours(1, 1));
    EXPECT_TRUE(g->areNeighbours(1, 2));
    EXPECT_TRUE(g->areNeighbours(2, 0));
    EXPECT_TRUE(g->areNeighbours(2, 1));
}

TEST(graph_check, test_are_neighbours_directed) {
    vector<vector<int>> am = {
            {0, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0},
    };
    Graph *g = new Graph(am);
    EXPECT_FALSE(g->areNeighbours(0, 0));
    EXPECT_FALSE(g->areNeighbours(1, 0));
    EXPECT_FALSE(g->areNeighbours(2, 0));
    EXPECT_FALSE(g->areNeighbours(3, 0));

    EXPECT_TRUE(g->areNeighbours(0, 1));
    EXPECT_TRUE(g->areNeighbours(0, 2));
    EXPECT_TRUE(g->areNeighbours(0, 3));
}

TEST(graph_check, test_are_neighbours_undirected) {
    vector<vector<int>> am = {
            {0, 1, 1, 1},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
    };
    Graph *g = new Graph(am);
    EXPECT_TRUE(g->areNeighbours(1, 0));
    EXPECT_TRUE(g->areNeighbours(2, 0));
    EXPECT_TRUE(g->areNeighbours(3, 0));

    EXPECT_TRUE(g->areNeighbours(0, 1));
    EXPECT_TRUE(g->areNeighbours(0, 2));
    EXPECT_TRUE(g->areNeighbours(0, 3));
}

TEST(graph_check, test_are_neighbours_range_1) {
    vector<vector<int>> am = {
            {0, 1, 1, 1},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
    };
    Graph *g = new Graph(am);

    // throw out_of_range("from/to must be in [0, " + getNumberOfNodes() + string("[."));
    try {
        g->areNeighbours(-1,3);
        FAIL();
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
        ASSERT_STREQ("from and to have to be in the range. ", e.what());
    }
}

TEST(graph_check, test_are_neighbours_range_2) {
    vector<vector<int>> am = {
            {0, 1, 1, 1},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
    };
    Graph *g = new Graph(am);

    // throw out_of_range("from/to must be in [0, " + getNumberOfNodes() + string("[."));
    try {
        g->areNeighbours(2,-2);
        FAIL();
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
        ASSERT_STREQ("from and to have to be in the range. ", e.what());
    }
}

TEST(graph_check, test_are_neighbours_range_3) {
    vector<vector<int>> am = {
            {0, 1, 1, 1},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
    };
    Graph *g = new Graph(am);

    // throw out_of_range("from/to must be in [0, " + getNumberOfNodes() + string("[."));
    try {
        g->areNeighbours(0,4);
        FAIL();
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
        ASSERT_STREQ("from and to have to be in the range. ", e.what());
    }
}

TEST(graph_check, test_are_neighbours_range_4) {
    vector<vector<int>> am = {
            {0, 1, 1, 1},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
            {1, 0, 0, 0},
    };
    Graph *g = new Graph(am);

    // throw out_of_range("from/to must be in [0, " + getNumberOfNodes() + string("[."));
    try {
        g->areNeighbours(4,0);
        FAIL();
    } catch (const out_of_range& e) {
        cout << e.what() << endl;
        ASSERT_STREQ("from and to have to be in the range. ", e.what());
    }
}
