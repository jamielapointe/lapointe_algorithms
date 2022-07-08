#pragma once

///
/// Implements the randomized contraction algorithm for the min cut problem
/// The min cut problem is cutting the graph in such a way that it minimizes the number of
/// crossing edges between the cut graph (A,B)
///
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <random>
#include <unordered_map>

#include "adjacency_list.hpp"

namespace LaPointe_Algorithms::algorithms::graphs {

Node&       merge_nodes(Node& u, Node& v, Adjacency_List& graph);
std::size_t min_cut_randomized_contraction(Adjacency_List const& graph_in);

// ignore any edges that went specifically from/to u and v (there was at least one since it was on the edge we
// selected)
// We merge the edges from Node v onto u (ignoring the edge from u to v) and then remove v
Node&       merge_nodes(Node& u, Node& v, Adjacency_List& graph) {
        // loop through all the edges of node v - adding them to node u (with the exception of any self-nodes)
  // again, we allow parallel (i.e. duplicate) edges
  for (auto& edge_wrapper : v.edges) {
          auto& edge       = edge_wrapper.get();
          // Get the node pointed by edge that is NOT the v node (i.e. the "other" node)
          auto& other_node = v != edge.endpoint_node_u ? edge.endpoint_node_u : edge.endpoint_node_v;
          // ignore self edges
          if (other_node != u) {
            graph.add_edge(u, other_node);
    }
  }
  graph.remove_node(v);
  return u;
}

/// Returns the number of crossing edges in the randomly selected cut
std::size_t min_cut_randomized_contraction(Adjacency_List const& graph_in) {
  Adjacency_List     graph(graph_in);
  std::random_device rd;
  std::mt19937_64    generator(rd());

  // uint32_t       index{0};
  // uint32_t       selected_indicies[]{1, 1, 2, 0, 0, 0, 0};

  // note that there are better optimized ways of doing this...
  while (graph.number_of_nodes() > 2) {
    // randomly select an edge
    std::uniform_int_distribution<uint32_t> distribution(0, static_cast<uint32_t>(graph.number_of_edges() - 1));
    uint32_t                                random_edge_index = distribution(generator);
    // uint32_t random_edge_index = selected_indicies[index++];
    // std::cout << "random edge ID = " << random_edge_index << std::endl;
    auto                                    edge_iterator     = graph.edges.begin();
    std::advance(edge_iterator, random_edge_index);
    auto& edge = *edge_iterator;
    merge_nodes(edge.endpoint_node_u, edge.endpoint_node_v, graph);
  }

  return graph.number_of_edges();
}

}  // namespace LaPointe_Algorithms::algorithms::graphs
