/*

Write algo to find next node, ie, in-order sucessor of a given node
in a binary tree. avoid storing additional nodes in a datastructure.

note, this is not nescessarily a binary search tree.

*/

#include <cmath>
#include <vector>
#include <stdio.h>

struct Node {
  int data;
  Node *left;
  Node *right;
};




int main() {

  std::vector<Node *> created_nodes;

  for (int i = 0; i < 10; i++) {
    Node *new_node = new Node{};
    new_node->data = i;
    created_nodes.push_back(new_node);
  }

  for (int i = 0; i < created_nodes.size(); i++) {
    delete created_nodes[i];
  }

}