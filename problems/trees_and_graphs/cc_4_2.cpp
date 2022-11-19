/*
given a directed graph, design an algo to find whether there is a path between
two nodes.

use BFS, mark visited nodes as visited.
if node == nullptr, return 0
else if node == nodeToFind return 1
else
search left
search right

return 0.

time complexity O(N) where N is nodes in graph
space complexity O(1)

*/

#include <queue>
#include <stdio.h>
#include <vector>

struct GraphNode {
  int data;
  bool visited;
  std::vector<GraphNode *> connected_nodes;
};

bool doesPathExist(GraphNode *origin, GraphNode *dest) {
  std::queue<GraphNode *> nodes_to_visit;
  nodes_to_visit.push(origin);
  while (nodes_to_visit.size() > 0) {
    GraphNode *node = nodes_to_visit.front();
    nodes_to_visit.pop();
    if (node == nullptr) {
      continue;
    } else if (node->visited) {
      continue;
    } else if (node == dest) {
      return true;
    } else {
      node->visited = true;
      for (int i = 0; i < node->connected_nodes.size(); i++) {
        nodes_to_visit.push(node->connected_nodes[i]);
      }
    }
  }
  return false;
}

int main() {
  std::vector<GraphNode> nodes;
  std::vector<GraphNode> seperate_node_graph;
  for (int i = 0; i < 10; i++) {
    GraphNode node;
    node.data = i;
    node.visited = false;
    nodes.push_back(node);
  }
  nodes[0].connected_nodes.push_back(&nodes[1]);
  nodes[0].connected_nodes.push_back(&nodes[2]);
  nodes[1].connected_nodes.push_back(&nodes[3]);
  nodes[2].connected_nodes.push_back(&nodes[4]);
  nodes[2].connected_nodes.push_back(&nodes[5]);
  nodes[5].connected_nodes.push_back(&nodes[2]);
  nodes[5].connected_nodes.push_back(&nodes[6]);
  nodes[3].connected_nodes.push_back(&nodes[7]);
  nodes[7].connected_nodes.push_back(&nodes[8]);
  nodes[8].connected_nodes.push_back(&nodes[9]);

  bool path_exists = doesPathExist(&nodes[0], &nodes[8]);
  printf("path between %d and %d: %d\n", nodes[0].data, nodes[8].data,
         path_exists);

  for (int i = 0; i < 10; i++) {
    GraphNode node;
    node.data = i;
    node.visited = false;
    seperate_node_graph.push_back(node);
  }

  path_exists = doesPathExist(&nodes[0], &seperate_node_graph[8]);
  printf("path between %d and %d: %d\n", nodes[0].data,
         seperate_node_graph[8].data, path_exists);

  printf("done.\n");
}