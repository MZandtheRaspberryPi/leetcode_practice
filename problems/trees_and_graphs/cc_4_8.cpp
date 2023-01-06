/*

You have two very large binary trees. t1 wtih millions of nodes,
and t2 with hundreds of nodes. write algo to decide if t2 is subtree of t1.

a tree t2 is a subtree of t1, if there exists a node n in t1 such that subtree
of n is identical to t2. That is, if you cut off the tree at noden, the two
trees would be identical.

use dfs to find root of t2 in t1, then use BFS with 2 queues for each tree
and return true if get to end of both without a mismatch, or false if
mismatch.

if dfs returns false keep searching with dfs. if true, return true.

check for nullptrs at the start

time complexity in worst case, O(N) where N is size of big tree.
space complexity O(logn), where N size of big tree to store recursive calls

could improve this by doing targeted searching of big tree for node in tree.
then wouldnt have to search all of big tree repeatedly, as its binary tree.


feedback from solution
a simpler way is to make copies of both trees into a string.
represent nullptr in some way in the string.
then check if str2 is a substr of str1.

need to make strings for in-order traversal and pre-order traversal. and if both
are substr, then tree substr. this uses a lot of memory. O(2*N + 2 *M) where N
is size of big tree and M size of small tree.

time complexity, O(N + M), as we visit each node, and then do string comparison
which is linear time

sometimes simpler may be better if no memory constraints.

also the way i suggested, has very diff worst case from avg case. In avg case,
its probably fine.

*/
#include <queue>
#include <stdio.h>
#include <vector>

struct Node {
  int data;
  Node *left;
  Node *right;
};

bool isSubtree(Node *root1, Node *root2) {
  if (root1 == nullptr || root2 == nullptr) {
    return false;
  }

  if (root1->data == root2->data) {
    // BFS, return true if got it
    std::queue<Node *> queue1;
    std::queue<Node *> queue2;
    queue1.push(root1);
    queue2.push(root2);
    bool are_trees_matched = true;
    while (queue1.size() > 0 && queue2.size() > 0) {
      Node *node1 = queue1.front();
      queue1.pop();
      Node *node2 = queue2.front();
      queue2.pop();
      if (node1 != nullptr && node2 != nullptr) {
        if (node1->data != node2->data) {
          are_trees_matched = false;
          break;
        } else {
          queue1.push(node1->left);
          queue2.push(node2->left);
          queue1.push(node1->right);
          queue2.push(node2->right);
        }
      } else if ((node1 == nullptr && node2 != nullptr) ||
                 (node1 != nullptr && node2 == nullptr)) {
        are_trees_matched = false;
        break;
      }
    }
    if ((queue1.size() != queue2.size()) || queue1.size() != 0 ||
        queue2.size() != 0) {
      are_trees_matched = false;
    }
    if (are_trees_matched) {
      return true;
    }

    // else, keep searching rest of tree 1
  }

  bool is_sub_tree = isSubtree(root1->left, root2);
  if (is_sub_tree) {
    return is_sub_tree;
  }
  is_sub_tree = isSubtree(root1->right, root2);
  return is_sub_tree;
}

int main() {
  std::vector<Node *> vect1;
  std::vector<Node *> vect2;
  const int NUM_NODES = 10;

  for (int i = 0; i < NUM_NODES; i++) {
    Node *node1 = new Node();
    node1->data = i;
    Node *node2 = new Node();
    node2->data = i;

    vect1.push_back(node1);
    vect2.push_back(node2);
  }

  Node *root1 = vect1[4];
  Node *root2 = vect2[2];

  root1->left = vect1[2];
  root1->right = vect1[7];

  root1->left->left = vect1[1];
  root1->left->right = vect1[3];
  root1->left->left->left = vect1[0];

  root2->left = vect2[1];
  root2->right = vect2[3];
  root2->left->left = vect2[0];

  bool is_subtree = isSubtree(root1, root2);
  printf("is subtree, expect true: %d\n", is_subtree);

  root2->right->data = 8;
  is_subtree = isSubtree(root1, root2);
  printf("is subtree, expect false: %d\n", is_subtree);

  for (int i = 0; i < NUM_NODES; i++) {
    Node *node = vect1.back();
    vect1.pop_back();
    delete node;
    node = vect2.back();
    vect2.pop_back();
    delete node;
  }
}
