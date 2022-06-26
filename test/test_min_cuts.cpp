
#include <gtest/gtest.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>

#include "min_cut_randomized_contraction.hpp"

TEST(TestMinCuts, SimpleTest0) {
  // A simple connected two node graph with a single edge
  Adjacency_List graph;
  graph.add_node(0);
  graph.add_node(1);
  graph.add_edge(0, 1);

  static constexpr size_t expected_min_cut_edges{1};
  size_t                  measured_min_cut_edges = min_cut_randomized_contraction(graph);
  ASSERT_EQ(measured_min_cut_edges, expected_min_cut_edges);
}

TEST(TestMinCuts, SimpleTest1) {
  // A simple connected three node graph with a three edges (triangle)
  Adjacency_List graph;
  graph.add_node(0);
  graph.add_node(1);
  graph.add_node(2);
  graph.add_edge(0, 1);
  graph.add_edge(1, 2);
  graph.add_edge(2, 0);

  static constexpr size_t expected_min_cut_edges{2};
  size_t                  measured_min_cut_edges = min_cut_randomized_contraction(graph);
  ASSERT_EQ(measured_min_cut_edges, expected_min_cut_edges);
}

TEST(TestMinCuts, SimpleTest2) {
  // A simple connected four node graph with a four edges (square)
  Adjacency_List graph;
  graph.add_node(0);
  graph.add_node(1);
  graph.add_node(2);
  graph.add_node(3);
  graph.add_edge(0, 1);
  graph.add_edge(1, 2);
  graph.add_edge(2, 3);
  graph.add_edge(3, 0);

  static constexpr size_t expected_min_cut_edges{2};
  size_t                  measured_min_cut_edges = min_cut_randomized_contraction(graph);
  ASSERT_EQ(measured_min_cut_edges, expected_min_cut_edges);
}

TEST(TestMinCuts, SimpleTest3) {
  // A simple connected four node graph with a four edges (square)
  Adjacency_List graph;
  graph.add_node(0);
  graph.add_node(1);
  graph.add_node(2);
  graph.add_node(3);
  graph.add_edge(0, 1);
  graph.add_edge(1, 2);
  graph.add_edge(2, 3);
  graph.add_edge(3, 0);

  static constexpr size_t expected_min_cut_edges{2};
  size_t                  overall_measured_min_cut_edges{std::numeric_limits<std::size_t>::max()};
  static const size_t     max_loop{graph.number_of_nodes() * graph.number_of_nodes() *
                               static_cast<std::size_t>(std::log2(graph.number_of_nodes()))};
  for (uint32_t trial_index = 0; trial_index < max_loop; ++trial_index) {
    size_t trial_min_cut_edges = min_cut_randomized_contraction(graph);
    if (trial_min_cut_edges < overall_measured_min_cut_edges) {
      overall_measured_min_cut_edges = trial_min_cut_edges;
    }
  }
  ASSERT_EQ(overall_measured_min_cut_edges, expected_min_cut_edges);
}

TEST(TestMinCuts, SimpleTest4) {
  // A slightly more complex connected four node graph with a five edges (square with diaganol through it)
  Adjacency_List graph;
  graph.add_node(0);
  graph.add_node(1);
  graph.add_node(2);
  graph.add_node(3);
  graph.add_edge(0, 1);
  graph.add_edge(1, 2);
  graph.add_edge(2, 3);
  graph.add_edge(3, 0);
  graph.add_edge(1, 3);

  static constexpr size_t expected_max_cut_edges{3};
  static constexpr size_t expected_min_cut_edges{2};
  size_t                  measured_min_cut_edges = min_cut_randomized_contraction(graph);
  ASSERT_LE(measured_min_cut_edges, expected_max_cut_edges);
  ASSERT_GE(measured_min_cut_edges, expected_min_cut_edges);
}

TEST(TestMinCuts, SimpleTest5) {
  // A slightly more complex connected four node graph with a five edges (square with diaganol through it)
  Adjacency_List graph;
  graph.add_node(0);
  graph.add_node(1);
  graph.add_node(2);
  graph.add_node(3);
  graph.add_edge(0, 1);
  graph.add_edge(1, 2);
  graph.add_edge(2, 3);
  graph.add_edge(3, 0);
  graph.add_edge(1, 3);

  static constexpr size_t expected_min_cut_edges{2};
  size_t                  overall_measured_min_cut_edges{std::numeric_limits<std::size_t>::max()};
  static const size_t     max_loop{graph.number_of_nodes() * graph.number_of_nodes() *
                               static_cast<std::size_t>(std::log2(graph.number_of_nodes()))};
  for (uint32_t trial_index = 0; trial_index < max_loop; ++trial_index) {
    size_t trial_min_cut_edges = min_cut_randomized_contraction(graph);
    if (trial_min_cut_edges < overall_measured_min_cut_edges) {
      overall_measured_min_cut_edges = trial_min_cut_edges;
    }
  }
  ASSERT_EQ(overall_measured_min_cut_edges, expected_min_cut_edges);
}

TEST(TestMinCuts, CourseraQuiz) {
  Adjacency_List graph;
  std::ifstream  in_file("data/kargerMinCut.txt");
  ASSERT_TRUE(in_file.is_open());
  std::string line;
  // probably not the most effecient... but do two passes through the file
  // first all of the rows represent a node
  while (std::getline(in_file, line)) {
    std::stringstream liness(line);
    uint32_t          u_node;
    liness >> u_node;
    graph.add_node(u_node);
  }
  in_file.clear();
  in_file.seekg(0, in_file.beg);  // start back at the beginning
  // now parse each row to add the connective edges between nodes
  // column 1 represents the row number (and the node number)
  while (std::getline(in_file, line)) {
    std::stringstream liness(line);
    // get the root node of the row
    uint32_t          u_node;
    liness >> u_node;
    uint32_t v_node;
    while (liness >> v_node) {
      // only add unique edges
      graph.add_edge(u_node, v_node, true);
    }
  }

  in_file.close();

  size_t              overall_measured_min_cut_edges{std::numeric_limits<std::size_t>::max()};
  static const size_t max_loop{graph.number_of_nodes() - 1};
  for (uint32_t trial_index = 0; trial_index < max_loop; ++trial_index) {
    size_t trial_min_cut_edges = min_cut_randomized_contraction(graph);
    if (trial_min_cut_edges < overall_measured_min_cut_edges) {
      overall_measured_min_cut_edges = trial_min_cut_edges;
    }
  }

  static constexpr size_t expected_min_cut_edges{17};  // determine this actual number....
  ASSERT_EQ(overall_measured_min_cut_edges, expected_min_cut_edges);
}
