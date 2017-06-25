#include "gtest/gtest.h"
#include <string>
#include <boost/algorithm/string.hpp>
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
        g->areNeighbours(-1, 3);
        FAIL();
    } catch (const out_of_range &e) {
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
        g->areNeighbours(2, -2);
        FAIL();
    } catch (const out_of_range &e) {
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
        g->areNeighbours(0, 4);
        FAIL();
    } catch (const out_of_range &e) {
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
        g->areNeighbours(4, 0);
        FAIL();
    } catch (const out_of_range &e) {
        cout << e.what() << endl;
        ASSERT_STREQ("from and to have to be in the range. ", e.what());
    }
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

TEST(graph_check, test_constructor_names) {
    vector<vector<int>> am = {
            {0, 1, 1, 0},
            {1, 0, 1, 0},
            {1, 1, 0, 0},
            {1, 1, 0, 0},
    };
    vector<string> nodes = {"test", "node2", "node3", "node4"};
    Graph *g = new Graph(am, nodes);
    string dot = g->exportDot();
    cout << dot << endl;
    EXPECT_NE(dot.find("test -> node2"), string::npos);
    EXPECT_NE(dot.find("test -> node3"), string::npos);
    EXPECT_NE(dot.find("node2 -> test"), string::npos);
    EXPECT_NE(dot.find("node2 -> node3"), string::npos);
    EXPECT_NE(dot.find("node3 -> test"), string::npos);
    EXPECT_NE(dot.find("node3 -> node2"), string::npos);
    EXPECT_NE(dot.find("node4 -> test"), string::npos);
    EXPECT_NE(dot.find("node4 -> node2"), string::npos);
}

TEST(graph_check, test_adjazenzmatrix_string) {
    Graph *g = new Graph("[1 0 1; 1 1 1; 0 0 1]");
    string mat = g->getAdjacencyMatrixString();

    std::vector<std::string> strs;
    boost::split(strs, mat, boost::is_any_of("\n"));

    ASSERT_EQ(strs[0], "1,0,1");
    ASSERT_EQ(strs[1], "1,1,1");
    ASSERT_EQ(strs[2], "0,0,1");
}

TEST(graph_check, test_forest_true) {
    Graph *g = new Graph("[0 1 1; 0 0 0; 0 0 0]");
    bool forest = g->isForest();

    ASSERT_TRUE(forest);
}

TEST(graph_check, test_forest_false) {
    //cycle -> false
    Graph *g = new Graph("[0 1 1; 0 0 0; 1 0 0]");
    bool forest = g->isForest();

    ASSERT_FALSE(forest);
}

TEST(graph_check, test_forest_undirected) {
    //undirected -> false
    Graph *g = new Graph("[0 1 1; 1 0 0; 1 0 0]");
    bool forest = g->isForest();

    ASSERT_FALSE(forest);
}