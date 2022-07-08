#pragma once

#include <queue>

#include "adjacency_list.hpp"

namespace LaPointe_Algorithms::algorithms::graphs {

void bfs(Adjacency_List& graph, Node& start_node);

void bfs(Adjacency_List& graph, Node& start_node) {
  // assumes all nodes start as unvisited - does not waste time checking
  start_node.is_visited = true;
  std::queue<Node> q;
  q.push(start_node);
  while (!q.empty()) {
    auto  v       = q.front();
    auto& v_edges = v.edges;
    for (auto& edge : v_edges) {
      auto& w =
          edge.get().endpoint_node_v.node_id != v.node_id ? edge.get().endpoint_node_v : edge.get().endpoint_node_u;
      if (!w.is_visited) {
        w.is_visited = true;
        q.push(w);  // FIFO, so pushes to the back
      }
    }
    q.pop();  // FIFO, so pops from the front
  }
  (void)graph;
}

}  // namespace LaPointe_Algorithms::algorithms::graphs
