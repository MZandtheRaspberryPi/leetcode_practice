# Trees and Graphs

Worst and avg case time may vary wiedely.

## Issues to Watch out For
Binary Tree vs Binary Search Tree 
Binary search tree means for all nodes, left children are less than or equal to current node, which is less than all right nodes

Balanced vs Unbalanced
Many trees are balanced, but not all. If unbalanced, describe algo in terms of avg and worst case time.
Multiple ways to balance a tree, only means that depth of subtrees will not vary by more than certain amount.

Full and Complete
Trees in which all leaves are at bottom of the three and all non-leaf nodes have exactly 2 children.
extremely rare as tree must have exactly 2^n - 1 nodes to meet this condition.

Binary Tree traversal.
in order, post order, pre-order traversal.
in order: visit left side, then current, then right.

Tree balancing. red-black trees and avl trees.
rare to ask. should know runtime of ops on blaanced trees, vaguely familiar with how balance.
details probs unnescessary.

Trie
varian of an n-ary tree, where characters at each node. each path might represent word.

## Graph Traversal.
BFS. and DFS. DFS usually if want to visit each node in graph, or till we find what looking for.
But if big tree, and we want to quit when get too far from origin, DFS hard. maybe BFS.

DFS
visit node r and iterate through each of r's adjacent nodes. when visit node n that adjacent to r, visit n adjacent nodes
before going to r's other adjacent nodes. n is exhaustively searched before r moves on to searching other children.

pre-order and such are form of DFS. key diff for graph is have to mark if node visited. if not, could infinite loop.

BFS
less intuitive. visit each of node r's adjacent nodes before searching any of r's grandchildren.
iterative sol w/ queue usually works best.
