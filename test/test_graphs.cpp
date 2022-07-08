
#include <gtest/gtest.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "basic_bfs.hpp"
#include "min_cut_randomized_contraction.hpp"

using Adjacency_List = LaPointe_Algorithms::algorithms::graphs::Adjacency_List;

static std::unique_ptr<Adjacency_List> get_graph_0() {
  std::unique_ptr<Adjacency_List> graph(new Adjacency_List());
  graph->add_node(0);
  graph->add_node(1);
  graph->add_edge(0, 1);
  return graph;
}

static std::unique_ptr<Adjacency_List> get_graph_1() {
  std::unique_ptr<Adjacency_List> graph(new Adjacency_List());
  graph->add_node(0);
  graph->add_node(1);
  graph->add_node(2);
  graph->add_edge(0, 1);
  graph->add_edge(1, 2);
  graph->add_edge(2, 0);
  return graph;
}

static std::unique_ptr<Adjacency_List> get_graph_2() {
  std::unique_ptr<Adjacency_List> graph(new Adjacency_List());
  graph->add_node(0);
  graph->add_node(1);
  graph->add_node(2);
  graph->add_node(3);
  graph->add_edge(0, 1);
  graph->add_edge(1, 2);
  graph->add_edge(2, 3);
  graph->add_edge(3, 0);
  return graph;
}

static std::unique_ptr<Adjacency_List> get_graph_3() {
  std::unique_ptr<Adjacency_List> graph(new Adjacency_List());
  graph->add_node(0);
  graph->add_node(1);
  graph->add_node(2);
  graph->add_node(3);
  graph->add_edge(0, 1);
  graph->add_edge(1, 2);
  graph->add_edge(2, 3);
  graph->add_edge(3, 0);
  return graph;
}

static std::unique_ptr<Adjacency_List> get_graph_4() {
  std::unique_ptr<Adjacency_List> graph(new Adjacency_List());
  graph->add_node(0);
  graph->add_node(1);
  graph->add_node(2);
  graph->add_node(3);
  graph->add_edge(0, 1);
  graph->add_edge(1, 2);
  graph->add_edge(2, 3);
  graph->add_edge(3, 0);
  graph->add_edge(1, 3);
  return graph;
}

static std::unique_ptr<Adjacency_List> get_graph_5() {
  std::unique_ptr<Adjacency_List> graph(new Adjacency_List());
  graph->add_node(0);
  graph->add_node(1);
  graph->add_node(2);
  graph->add_node(3);
  graph->add_edge(0, 1);
  graph->add_edge(1, 2);
  graph->add_edge(2, 3);
  graph->add_edge(3, 0);
  graph->add_edge(1, 3);
  return graph;
}

static std::unique_ptr<Adjacency_List> get_graph_from_file(std::string const& fname) {
  std::unique_ptr<Adjacency_List> graph(new Adjacency_List());
  std::ifstream                   in_file(fname);
  if (!in_file.is_open()) {
    std::stringstream ss;
    ss << "Cannot open file named [ " << fname << " ]";
    throw std::logic_error(ss.str());
  }
  std::string line;
  // probably not the most effecient... but do two passes through the file
  // The first column of each row represents a node
  while (std::getline(in_file, line)) {
    std::stringstream liness(line);
    uint32_t          u_node{0};
    liness >> u_node;
    graph->add_node(u_node);
  }
  in_file.clear();
  in_file.seekg(0, in_file.beg);  // start back at the beginning
  // now parse each row to add the connective edges between nodes
  // column 1 represents the node number, subsequent columns represent
  // edges connected to node in column 1
  while (std::getline(in_file, line)) {
    std::stringstream liness(line);
    // get the root node of the row
    uint32_t          u_node{0};
    liness >> u_node;
    uint32_t v_node{0};
    while (liness >> v_node) {
      // only add unique edges
      graph->add_edge(u_node, v_node, true);
    }
  }

  in_file.close();
  return graph;
}

TEST(TestGraphs, TestSimpleMinCut0) {  // NOLINT
  // A simple connected two node graph with a single edge
  auto                    graph = *get_graph_0();

  static constexpr size_t expected_min_cut_edges{1};
  size_t                  measured_min_cut_edges = min_cut_randomized_contraction(graph);
  ASSERT_EQ(measured_min_cut_edges, expected_min_cut_edges);
}

TEST(TestGraphs, TestSimpleBfs0) {  // NOLINT
  // A simple connected two node graph with a single edge
  auto graph = *get_graph_0();
  LaPointe_Algorithms::algorithms::graphs::bfs(graph, graph.nodes.front());
  ASSERT_TRUE(graph.all_nodes_visited());
}

TEST(TestGraphs, TestSimpleMinCut1) {  // NOLINT
  // A simple connected three node graph with a three edges (triangle)
  auto                    graph = *get_graph_1();

  static constexpr size_t expected_min_cut_edges{2};
  size_t                  measured_min_cut_edges = min_cut_randomized_contraction(graph);
  ASSERT_EQ(measured_min_cut_edges, expected_min_cut_edges);
}

TEST(TestGraphs, TestSimpleBfs1) {  // NOLINT
  // A simple connected two node graph with a single edge
  auto graph = *get_graph_1();
  LaPointe_Algorithms::algorithms::graphs::bfs(graph, graph.nodes.front());
  ASSERT_TRUE(graph.all_nodes_visited());
}

TEST(TestGraphs, TestSimpleMinCut2) {  // NOLINT
  // A simple connected four node graph with a four edges (square)
  auto                    graph = *get_graph_2();

  static constexpr size_t expected_min_cut_edges{2};
  size_t                  measured_min_cut_edges = min_cut_randomized_contraction(graph);
  ASSERT_EQ(measured_min_cut_edges, expected_min_cut_edges);
}

TEST(TestGraphs, TestSimpleBfs2) {  // NOLINT
  // A simple connected two node graph with a single edge
  auto graph = *get_graph_2();
  LaPointe_Algorithms::algorithms::graphs::bfs(graph, graph.nodes.front());
  ASSERT_TRUE(graph.all_nodes_visited());
}

TEST(TestGraphs, TestSimpleMinCut3) {  // NOLINT
  // A simple connected four node graph with a four edges (square)
  auto                    graph = *get_graph_3();

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

TEST(TestGraphs, TestSimpleBfs3) {  // NOLINT
  // A simple connected two node graph with a single edge
  auto graph = *get_graph_3();
  LaPointe_Algorithms::algorithms::graphs::bfs(graph, graph.nodes.front());
  ASSERT_TRUE(graph.all_nodes_visited());
}

TEST(TestGraphs, TestSimpleMinCut4) {  // NOLINT
  // A slightly more complex connected four node graph with a five edges (square with diaganol through it)
  auto                    graph = *get_graph_4();

  static constexpr size_t expected_max_cut_edges{3};
  static constexpr size_t expected_min_cut_edges{2};
  size_t                  measured_min_cut_edges = min_cut_randomized_contraction(graph);
  ASSERT_LE(measured_min_cut_edges, expected_max_cut_edges);
  ASSERT_GE(measured_min_cut_edges, expected_min_cut_edges);
}

TEST(TestGraphs, TestSimpleBfs4) {  // NOLINT
  // A simple connected two node graph with a single edge
  auto graph = *get_graph_4();
  LaPointe_Algorithms::algorithms::graphs::bfs(graph, graph.nodes.front());
  ASSERT_TRUE(graph.all_nodes_visited());
}

TEST(TestGraphs, TestSimpleMinCut5) {  // NOLINT
  // A slightly more complex connected four node graph with a five edges (square with diaganol through it)
  auto                    graph = *get_graph_5();

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

TEST(TestGraphs, TestSimpleBfs5) {  // NOLINT
  // A simple connected two node graph with a single edge
  auto graph = *get_graph_5();
  LaPointe_Algorithms::algorithms::graphs::bfs(graph, graph.nodes.front());
  ASSERT_TRUE(graph.all_nodes_visited());
}

TEST(TestGraphs, CourseraMinCutQuiz) {  // NOLINT
  const std::string   fname0("data/kargerMinCut.txt");
  auto                graph = *get_graph_from_file(fname0);

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

TEST(TestGraphs, TestSimpleBfs6) {  // NOLINT
  // A simple connected two node graph with a single edge
  const std::string fname0("data/kargerMinCut.txt");
  auto              graph = *get_graph_from_file(fname0);
  LaPointe_Algorithms::algorithms::graphs::bfs(graph, graph.nodes.front());
  ASSERT_TRUE(graph.all_nodes_visited());
}
