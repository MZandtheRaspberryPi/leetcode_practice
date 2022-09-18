/*
Imagine reading a stream of integers. want to look up rank of number x (number of values less than or equal to x).
Implement data structures and algos to support these operations. implement method track(int x).
getRankOfNumber(int x) which returns the number of values less than or equal to x (not including x itself).

Ex
Stream: 5, 1, 4, 4, 5, 9, 7, 13, 3
getRankOfNumber(1) = 0
getRankOfNumber(3) = 1
getRankOfNumber(4) = 3

exemplify

find patterns

solve for base case

simplify

datastructure brainstorm

we could use an array, and each time we insert we shift everything. then looking up we could binary search, logn, but inserting O(N).
binary search tree could work well. keep track of rank for each node when we insert.
when track, check root and if nullptr set and return. if not nullptr and if less than root or equal, add one to rank of root and recurse on left.
else recurse right.

when looking up rank, if number less than root and left not null ptr recurse left. if left nullptr return -1.
if number greater than root, and right not nullptr, add root rank plus 1 to rank counter and recurse right. if right nullptr return -1.
if number equal root, add root rank ctr to rank counter and return rank counter.

for a balanced binary tree, O(logn). for unbalanced binary tree O(N). storage: O(N).

*/

#include <stdio.h>
#include <queue>
#include <vector>

struct Node
{
    int data;
    int rank;
    Node* left = nullptr;
    Node* right = nullptr;
};

void insertRankedNode(Node* node_to_insert, Node* node_to_search);

int findNumberRank(Node* node_to_search, int x, int& rank_counter);

class BinaryTree
{
    public:
        ~BinaryTree();
        void track(int x);
        int getRankOfNumber(int x);
        void print();
    private:
        Node* root;
        std::vector<Node*> created_nodes;
};

void insertRankedNode(Node* node_to_insert, Node* node_to_search)
{
    Node* next_node = nullptr;
    bool insert_left;
    if (node_to_insert->data <= node_to_search->data)
    {
        node_to_search->rank++;
        next_node = node_to_search->left;
        insert_left = true;
    }
    else
    {
        next_node = node_to_search->right;
        insert_left = false;
    }
    if (next_node != nullptr)
    {
        insertRankedNode(node_to_insert, next_node);
    }
    else if (next_node == nullptr && insert_left)
    {
        node_to_search->left = node_to_insert;
    }
    else
    {
        node_to_search->right = node_to_insert;
    }
    return;
}

BinaryTree::~BinaryTree()
{
    for (int i = 0; i < created_nodes.size(); i++)
    {
        delete created_nodes[i];
    }
}

void BinaryTree::print()
{
    std::queue<Node*> q;
    q.push(root);
    while(q.size() != 0)
    {
        Node* node = q.front();
        q.pop();
        if (node == nullptr)
        {
            continue;
        }
        printf("node, data: %d rank: %d\n", node->data, node->rank);
        if (node->left != nullptr)
        {
            printf("left, data: %d rank: %d  |  ", node->left->data, node->left->rank);
        }
        else
        {
            printf("left, nullptr  |  ");
        }

        if (node->right != nullptr)
        {
            printf("right, data: %d rank: %d  |  ", node->right->data, node->right->rank);
        }
        else
        {
            printf("right, nullptr  |  ");
        }

        printf("\n\n");

        q.push(node->left);
        q.push(node->right);
    }
}


void BinaryTree::track(int x)
{
    Node* new_node = new Node{};
    created_nodes.push_back(new_node);
    new_node->data = x;
    new_node->rank = 0;
    if (root == nullptr)
    {
        root = new_node;
        return;
    }
    
    insertRankedNode(new_node, root);
}

int findNumberRank(Node* node_to_search, int x, int& rank_counter)
{
    Node* next_node = nullptr;
    if (x > node_to_search->data)
    {
        rank_counter += node_to_search->rank + 1;
        next_node = node_to_search->right;
    }
    else if (x < node_to_search->data)
    {
        next_node = node_to_search->left;
    }
    else
    {
        rank_counter += node_to_search->rank;
        return rank_counter;
    }

    if (next_node != nullptr)
    {
        findNumberRank(next_node, x, rank_counter);
    }
    else
    {
        return -1;
    }
}


int BinaryTree::getRankOfNumber(int x)
{
    int rank = 0;
    return findNumberRank(root, x, rank);
}

int main()
{
    BinaryTree tree = BinaryTree();
    std::vector<int> nums_to_add = {5, 1, 4, 4, 5, 9, 7, 13, 3};
    for (int i = 0; i < nums_to_add.size(); i++)
    {
        tree.track(nums_to_add[i]);
    }
    tree.print();
    
    printf("rank 1: %d\n", tree.getRankOfNumber(1));
    printf("rank 3: %d\n", tree.getRankOfNumber(3));
    printf("rank 4: %d\n", tree.getRankOfNumber(4));
    printf("rank 40: %d\n", tree.getRankOfNumber(40));
}
