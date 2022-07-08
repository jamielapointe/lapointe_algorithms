
#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <exception>
#include <functional>
#include <iostream>
#include <list>
#include <random>
#include <stdexcept>
#include <unordered_map>

namespace LaPointe_Algorithms::algorithms::graphs {

struct Edge;
struct Node;
struct Adjacency_List;
Node&       merge_nodes(Node& u, Node& v, Adjacency_List& graph);
std::size_t min_cut_randomized_contraction(Adjacency_List const& graph_in);

/// basic data structure representing a node or vertex of a graph
struct Node {
  // can contain weights and stuff
  explicit Node(uint32_t id) : node_id{id} {}
  std::list<std::reference_wrapper<Edge>> edges;

  uint32_t                                node_id;
  bool                                    is_visited{false};

  bool                                    operator==(Node const& node) const { return node.node_id == node_id; }
};

/// undirected edge of a graph; thus no head or tail
struct Edge {
  explicit Edge(Node& u, Node& v) : endpoint_node_u{u}, endpoint_node_v{v} {}
  Node& endpoint_node_u;
  Node& endpoint_node_v;
  bool  operator==(Edge const& edge) const {
     return edge.endpoint_node_u.node_id == endpoint_node_u.node_id &&
            edge.endpoint_node_v.node_id == endpoint_node_v.node_id;
  }
  bool contains_node(Node const& node) const {
    return node.node_id == endpoint_node_u.node_id || node.node_id == endpoint_node_v.node_id;
  }
};

/// Data structure representing a graph
struct Adjacency_List {
  Adjacency_List() = default;

  Adjacency_List(Adjacency_List const& other) {
    for (auto const& node : other.nodes) {
      add_node(node.node_id);
    }
    for (auto const& edge : other.edges) {
      add_edge(edge.endpoint_node_u.node_id, edge.endpoint_node_v.node_id);
    }
  }
  Adjacency_List(Adjacency_List const&& other) = delete;

  Adjacency_List& operator=(Adjacency_List const& other) {
    nodes.clear();
    edges.clear();
    for (auto const& node : other.nodes) {
      add_node(node.node_id);
    }
    for (auto const& edge : other.edges) {
      add_edge(edge.endpoint_node_u.node_id, edge.endpoint_node_v.node_id);
    }
    return *this;
  }
  Adjacency_List&& operator=(Adjacency_List const&& other) = delete;

  ~Adjacency_List()                                        = default;

  Node& add_node(uint32_t id) {
    if (id > max_node_id) max_node_id = id;
    return nodes.emplace_back(id);
  }

  Node& add_node() { return add_node(max_node_id + 1); }

  void  clear_visitations() {
     for (auto& node : nodes) {
       node.is_visited = false;
    }
  }

  bool all_nodes_visited() {
    bool all_visited{true};
    for (auto const& node : nodes) {
      all_visited &= node.is_visited;
    }
    return all_visited;
  }

  Edge& add_edge(Node& u, Node& v, bool unique_only = false) {
    if (unique_only) {
      auto it = std::find_if(edges.begin(), edges.end(), [&](Edge const& edge) {
        return (edge.endpoint_node_u.node_id == u.node_id && edge.endpoint_node_v.node_id == v.node_id) ||
               (edge.endpoint_node_u.node_id == v.node_id && edge.endpoint_node_v.node_id == u.node_id);
      });
      if (it != edges.end()) {
        // not unique, so just return the found edge
        auto& edge = *it;
        u.edges.push_back(edge);
        v.edges.push_back(edge);
        return edge;
      }
    }
    auto& edge = edges.emplace_back(u, v);
    u.edges.push_back(edge);
    v.edges.push_back(edge);
    return edge;
  }

  Edge& add_edge(uint32_t u_node_id, uint32_t v_node_id, bool unique_only = false) {
    auto node_iterator_u =
        std::find_if(nodes.begin(), nodes.end(), [u_node_id](Node& node) { return node.node_id == u_node_id; });
    if (node_iterator_u == std::end(nodes)) {
      throw std::out_of_range("Could not find u_node_id.");
    }
    Node& u = *node_iterator_u;

    auto  node_iterator_v =
        std::find_if(nodes.begin(), nodes.end(), [v_node_id](Node& node) { return node.node_id == v_node_id; });
    if (node_iterator_v == std::end(nodes)) {
      throw std::out_of_range("Could not find v_node_id.");
    }
    Node& v = *node_iterator_v;

    return add_edge(u, v, unique_only);
  }

  void remove_node(Node& node) {
    // 1st remove edge references from any nodes connected to this current node
    remove_edges_pointing_to_node(node);
    // 2nd clear the current node edge list (to remove the references)
    node.edges.clear();
    // 3rd remove the edges themselves from the Adjacency_List
    remove_edges_containing_node(node);
    // 4th remove the node itself
    nodes.remove(node);
  }

  /// Remove any edge references from any Nodes with an edge to the passed in node
  /// NOTE This only affects the nodes themselves, it does not remove anything from the edges container
  void remove_edges_pointing_to_node(Node& node) {
    for (auto& edge_wrapper : node.edges) {
      auto& edge       = edge_wrapper.get();
      Node& other_node = node == edge.endpoint_node_u ? edge.endpoint_node_v : edge.endpoint_node_u;
      auto  edge_it    = other_node.edges.begin();
      while (edge_it != other_node.edges.end()) {
        auto& edge2 = edge_it->get();
        if (edge2.contains_node(node)) {
          edge_it = other_node.edges.erase(edge_it);
        } else {
          ++edge_it;
        }
      }
    }
  }

  /// only removes edges containing a node from the edges container (leaves the nodes container alone)
  void remove_edges_containing_node(Node& node) {
    auto edge_it = edges.begin();
    while (edge_it != edges.end()) {
      auto& edge = *edge_it;
      if (edge.contains_node(node)) {
        edge_it = edges.erase(edge_it);
      } else {
        ++edge_it;
      }
    }
  }

  auto            number_of_nodes() const { return nodes.size(); }
  auto            number_of_edges() const { return edges.size(); }

  std::list<Node> nodes;
  std::list<Edge> edges;
  uint32_t        max_node_id{0};
};

}  // namespace LaPointe_Algorithms::algorithms::graphs
