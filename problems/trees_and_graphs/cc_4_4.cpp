/*
Given binary tree, write algo to make linked list of all nodes at each depth. eg
if have a tree wtih depth D will have D linked lists.

we could do BFS, and we keep count each time we visit a node.
when the node is an even power of 2, then we know we just finished a level. But
that assumes balanced...

create an array of Node*.

do DFS, and keep count referenced. When visit a node, increment count. after
visiting a node decrement count. check size of array and resize if count is
greater than size. at each point in array it will be a second array of node
ptrs.

Then after we are done we can go through that and make linked lists for each of
them. We could also make a LL during, but then would need ot traverse the list
many times, so if levels get big that will take time.

This would be O(N) in time complexity, though we will end up visiting each node
twice. This will be O(N) in space as well.

feedback from solution.

Could have created linked list in the DFS. do in order traversal. so visit node,
then left, then right. and keep track of level. then if list is nullptr at that
spot, set it to node, else set next.

or could even have done BFS.
for this, you have to iterate through root, then level2, then3.
with level i, will have visisted fully nodes on i - 1. to get which nodes are on
level i, look at children of nodes of level i -1.

*/

#include <stdio.h>
#include <vector>

struct Node {
  int data;
  Node *left;
  Node *right;
};

struct LLNode {
  Node *data;
  LLNode *next;
};

void getNodesAtDepths(Node *root, int &count,
                      std::vector<std::vector<Node *>> &nodes_list) {
  if (root != nullptr) {
    count++;
    if (nodes_list.size() <= count) {
      nodes_list.resize(count + 1);
    }

    nodes_list[count].push_back(root);

    getNodesAtDepths(root->left, count, nodes_list);
    getNodesAtDepths(root->right, count, nodes_list);
    count--;
  }
}

std::vector<LLNode *> makeLLAtDepths(Node *root) {
  int count = 0;
  std::vector<std::vector<Node *>> nodes_list;

  getNodesAtDepths(root, count, nodes_list);

  std::vector<LLNode *> ll_list;

  for (int i = 1; i < nodes_list.size(); i++) {
    LLNode *root = nullptr;
    LLNode *runner = nullptr;
    for (int j = 0; j < nodes_list[i].size(); j++) {
      LLNode *new_node = new LLNode{};
      new_node->data = nodes_list[i][j];
      if (root == nullptr) {
        root = new_node;
        runner = new_node;
      } else {
        runner->next = new_node;
        runner = runner->next;
      }
    }
    ll_list.push_back(root);
  }
  return ll_list;
}

int main() {

  std::vector<Node *> created_nodes;

  for (int i = 0; i < 10; i++) {
    Node *new_node = new Node{};
    new_node->data = i;
    created_nodes.push_back(new_node);
  }

  Node *root = created_nodes[0];
  root->left = created_nodes[1];
  root->right = created_nodes[2];
  root->left->left = created_nodes[3];
  root->left->right = created_nodes[4];

  std::vector<LLNode *> ll_at_depths = makeLLAtDepths(root);

  for (int i = 0; i < ll_at_depths.size(); i++) {
    LLNode *runner = ll_at_depths[i];
    while (runner != nullptr) {
      printf("%d ", runner->data->data);
      runner = runner->next;
    }
    printf("\n");
  }

  for (int i = 0; i < created_nodes.size(); i++) {
    delete created_nodes[i];
  }

  for (int i = 0; i < ll_at_depths.size(); i++) {
    delete ll_at_depths[i];
  }
}