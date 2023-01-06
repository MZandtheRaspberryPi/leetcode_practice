/*
write algo to find next node in order
successor of given node in binary tree.
assume node has parent link.


so if given a node we've just visited, assuming its the current node ( in order traversal is left current right) then we need to go down right and then left all the way and visit that.


and its left of parent, return parent.
if its right we need to go up check the oarents parent. and while our parent is the right of the our parents parent, go up. when we get to the left, return that node.

f we dont reach that, ie, right is totally exhausted, then we need to return nullptr

*/

#include <stdio.h>

struct Node
{
    int data;
    Node* left;
    Node* right;
    Node* parent;
};

Node* findNextInOrderNode(Node* visited_node)
{
    if (visited_node == nullptr || visited_node->parent == nullptr)
    {
        return nullptr;
    }
    
    if (visited_node->parent->left == visited_node)
    {
        return visited_node->parent;
    }
    else (visited_node->parent->right == visited_node)
    {
        return findNextInOrderNode(visited_node->parent);
    }
    
}

int main()
{
    Node root;
    root->data = 0;
    Node left1;
    root->left = &left;
    left1->data = 1;
    left1->parent = &root;
    Node right2;
    right2->data =2;
    right2->parent = &root;
    root->right = &right;
    Node left21;
    left21->data = 3;
    left1->left = &left21;
    Node left22;
    left22->data= 4;
    left1->right = &left22;
    
    Node next = findNextInOrderNode(right2);
    if (next != nullptr) printf("%d\n", next->data) else printf("nullptr\n");
}