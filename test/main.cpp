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

TEST(graph_check, test_matlab_correct_notation) {

    try {
        // These graphs should not cause an error.
        Graph *a = new Graph("[1 0 1; 1 1 1; 0 0 1]");
        Graph *b = new Graph("  \t [1 0  1;1 \t\t 1 1\t\t\t    ;     0  0  1 ] ");
        Graph *c = new Graph("[1\t0\t1;1\t1\t1;0\t0\t1]");
        Graph *d = new Graph(" [ 1   0   1 ;   1   1   1 ;   0   0   1 ] ");
        Graph *e = new Graph("[1]");

    } catch (const invalid_argument &e) {
        cout << e.what();
        FAIL();
    }

    SUCCEED();
}

TEST(graph_check, test_matlab_wrong_notation_1) {

    try {
        Graph *g = new Graph("[1 0 1; 1 1 1 1; 0 0 1]"); // one column too much
        FAIL();
    } catch (const invalid_argument &e) {
        ASSERT_STREQ("There must be a syntax error, because the number of columns are different.", e.what());
    }
}

TEST(graph_check, test_matlab_wrong_notation_2) {

    try {
        Graph *g = new Graph("[1 0 1 0; 1 1 1 1; 0 0 1 1]"); // is not square
        FAIL();
    } catch (const invalid_argument &e) {
        ASSERT_STREQ("adjacency matrix has to be symmetrical", e.what());
    }
}

TEST(graph_check, test_matlab_wrong_notation_3) {

    try {
        Graph *g = new Graph("[0 1 0; 1 1 1; 0 1 1; 1 1 1]"); // is not square
        FAIL();
    } catch (const invalid_argument &e) {
        ASSERT_STREQ("adjacency matrix has to be symmetrical", e.what());
    }

}

TEST(graph_check, test_matlab_wrong_notation_4) {

    try {
        Graph *g = new Graph("1 0 1; 1 1 1; 0 0 1");
        FAIL();
    } catch (const invalid_argument &e) {
        ASSERT_STREQ("A valid matlab matrix notation must start with '[' and end up with ']'.", e.what());
    }
}

TEST(graph_check, test_matlab_wrong_notation_5) {

    try {
        Graph *g = new Graph("[]");
        FAIL();
    } catch (const invalid_argument &e) {
        ASSERT_STREQ("matrix entries must be and contain at least one integer.", e.what());
    }
}

TEST(graph_check, test_matlab_wrong_notation_6) {

    try {
        Graph *g = new Graph("[ a ]");
        FAIL();
    } catch (const invalid_argument &e) {
        ASSERT_STREQ("matrix entries must be and contain at least one integer.", e.what());
    }
}
