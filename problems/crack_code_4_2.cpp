#include<iostream>
#include<vector>
#include<queue>

// given a directed graph design an algorithm to find out whether there is a route between two nodes
// we could employ depth first search or breadth first search
// we take a node, and if we are using adjacency list representation, loook through its list
// and if we fine the node we want to link, return true, else, continue to next. if next is nullprt, return false.


// directed graph, ie with direction in nodes
// adjacency matrix or adjacency list representation.
// matrix, rows and cols nodes. n rows, n cols. A, B, first row, second col, 1 if edge, 0 if not.
// list rep, have linked list. if A connected to B, C. First entry is A > B > C > null. can't get to C from B, but only A.

// operations: add a vertex. add an edge. display graph vertices.
struct adjNode {
	int val, cost;
	adjNode* next;
};

struct graphEdge {
	int startVer, endVer, weight;
};

adjNode* delVertex(adjNode* vert) {
	if (vert->next == nullptr) {
		return vert;
	}
	else {
		adjNode* nextVert = delVertex(vert->next);
		delete nextVert;
		vert->next = nullptr;
		return vert;
	}
}

class DiaGraph {
	// insert new nodes into adjacency list from given graph
	adjNode* getAdjListNode(int value, int weight, adjNode* head) {
		adjNode* newNode = new adjNode;
		newNode->val = value;
		newNode->cost = weight;
		newNode->next = head; // point new node to current head
		return newNode;
	}
	int N; // number of nodes in the graph
public:
	adjNode** head; // adjacency list as array of pointers
	// constructor
	DiaGraph(graphEdge edges[], int n, int N) {
		// allocate new node
		head = new adjNode * [N]();
		this->N = N;
		// initialize head pointer for all indices
		for (int i = 0; i < N; i++) {
			head[i] = nullptr;
		}
		// construct directed graph by adding edges to it
		for (int i = 0; i < n; i++) {
			int startVer = edges[i].startVer;
			int endVer = edges[i].endVer;
			int weight = edges[i].weight;
			// insert node in the beginning
			adjNode* newNode = getAdjListNode(endVer, weight, head[startVer]);

			// point head pointer to new node
			head[startVer] = newNode;
		}
	}

	// destructor
	~DiaGraph() {
		for (int i = 0; i < N; i++) {
			adjNode* final = delVertex(head[i]);
			delete final;
		}
		delete[] head;
	}
};

// print all adj vertices of given index
void displayAdjList(adjNode* ptr, int i) {
	while (ptr != nullptr) {
		std::cout << "(" << i << ", " << ptr->val
			<< ", " << ptr->cost << ") ";
		ptr = ptr->next;
	}
	std::cout << std::endl;
}

// datastruct to store edge
struct Edge {
	int src, dest;
};

class Graph {
public:
	// vect of vectors to represent adj list
	std::vector<std::vector<int>> adjList;

	// constructor
	Graph(const std::vector<Edge> &edges, int N) {
		// resize vector to hold N elements of type vector<int>
		adjList.resize(N);

		// add edges to directed graph
		for (auto& edge : edges) {
			// insert at the end
			adjList[edge.src].push_back(edge.dest);
			// uncomment for undirected graph
			// adjList[edge.dest].push_back(edge.src);
		}
	}

	std::vector<std::vector<int>> getNodes() {
		return adjList;
	}
};

void printGraph(Graph const& graph, int N) {
	for (int i = 0; i < N; i++) {
		// print vertex num
		std::cout << i << " --> ";
		// print neighboring vertices
		for (int v : graph.adjList[i]) {
			std::cout << v << " ";
		}
		std::cout << std::endl;
	}
}

bool routeBetweenNodes(Graph const &graph, int node1, int node2) {
	for (int i = 0; i < graph.adjList[node1].size(); i++) {
		if (graph.adjList[node1][i] == node2) {
			return true;
		}
	}
	return false;
}

enum State {
	Unvisited, Visited, Visiting
};

struct Node {
	State state = Unvisited;
	int index;
	int val;
	std::vector<Node*> adjacent;

	void addEdge(Node* n) {
		adjacent.push_back(n);
	}

	std::vector<Node*> getAdjacent() {
		return adjacent;
	}

};


class NodeGraph {
public:
	// vect of vectors to represent adj list
	std::vector<Node*> adjList;

	// constructor
	NodeGraph(const std::vector<Edge>& edges, int N) {
		// resize vector to hold N elements of type vector<Node*>
		adjList.resize(N);

		for (int i = 0; i < N; i++) {
			Node* newNode = new Node{};
			newNode->index = i;
			adjList[i] = newNode;
		}

		// add edges to directed graph
		for (auto& edge : edges) {
			// find the node that is the destination
			Node* srcNode = adjList[edge.src];
			Node* destNode = adjList[edge.dest];
			// add it to the source node's adj list
			srcNode->addEdge(destNode);
			// uncomment for undirected graph
			// grabbing dest node adj list and adding src node to it
			destNode->addEdge(srcNode);
		}
	}

	std::vector<Node*> getNodes() {
		return adjList;
	}

	~NodeGraph() {
		for (int i = 0; i < adjList.size(); i++) {
			delete adjList[i];
		}
	}
};

static bool searchOptimal(NodeGraph& g, Node& start, Node& end) {
	// operates as a queue. Does BFS to try to find path.
	std::queue<Node*> q{};
	for (Node* u : g.getNodes()) {
		u->state = State::Unvisited;
	}

	start.state = State::Visiting;
	q.push(&start);
	Node* u;
	while (!q.empty()) {
		u = q.back();
		q.pop();
		if (u != nullptr) {
			for (Node* v : u->getAdjacent()) {
				if (v->state == State::Unvisited) {
					if (v == &end) {
						return true;
					} 
					else {
						v->state = State::Visiting;
						q.push(v);
					}
				}
			}
			u->state = State::Visited;
		}
	}
	return false;
}


// graph implementation
int main() {
	// graph edges array
	graphEdge edges[] = {
		// (x, y, w) edge from x to y with weight w
		{0,1,2},{0,2,4},{1,4,3},{2,3,2},{3,1,4},{4,3,3}
	};
	int N = 5; // number of vertices in graph
	// calc num edges
	int n = sizeof(edges) / sizeof(edges[0]);
	// construct graph
	DiaGraph diagraph(edges, n, N);
	// print adj list rep of graph
	std::cout << "Graph adjacency list " << std::endl << "(start_vertex, end_vertex, weight):" << std::endl;
	for (int i = 0; i < N; i++)
	{
		// display adjacent vertices of vertex i
		displayAdjList(diagraph.head[i], i);
	}

	// Please note that the initialization vector in the below format will
	// work fine in C++11, C++14, C++17 but will fail in C++98.
	std::vector<Edge> gEdges =
	{
		{ 0, 1 }, { 1, 2 }, { 2, 0 }, { 2, 1 },
		{ 3, 2 }, { 4, 5 }, { 5, 4 }
	};

	// total number of nodes in the graph
	int M = 6;

	// construct graph
	Graph graph(gEdges, M);

	// print adjacency list representation of a graph
	printGraph(graph, M);
	printf("0 to 1 exists is %d\n", routeBetweenNodes(graph, 0, 1));
	printf("3 to 1 exists is %d\n", routeBetweenNodes(graph, 3, 1));

	// trying optimal search
	NodeGraph ng(gEdges, M);
	Node* node2 = ng.adjList[2];
	Node* node1 = ng.adjList[1];
	Node* node3 = ng.adjList[3];
	Node* node4 = ng.adjList[4];
	printf("Path from 2 to 1: %d\n", searchOptimal(ng, *node2, *node1));
	printf("Path from 3 to 4: %d\n", searchOptimal(ng, *node3, *node4));


	return 0;
}