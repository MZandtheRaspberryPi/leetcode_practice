// pseudocode dfs, depth first search

void search(Node root) {
	if (root == nullptr) return;
	visit(root);
	root.visited = true;
	foreach (Node n in root.adjacent) {
		if (n.visited == false) {
			search(n);
		}
	}
}

void searchBFS(Node root) {
	Queue queue = new Queue();
	root.visited = true;
	visit(root);
	queue.enqueue(root); // add to end of queue
	
	while (!queue.isEmpty()) {
		Node r = queue.dequeue(); // remove from front of queue
		foreach (Node n in r.adjacent) {
			if (n.visited == false) {
				visit(n);
				n.visited = true;
				queue.enqueue(n);
			}
		}
	}

}