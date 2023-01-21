/*
Design a class which provides a lock only if there are no possible deadlocks.

perhaps we can make a class that keeps track of who asks it for resources and trys to find circular dependencies.

a circular reference is when process a has resource 1, and process b has resource 2, and process a asks for resource 2, and process b
asks for resource 1. both are waiting for the other to release it.

the deadlock really starts when a asks for resource 1 and resource 2, and resource 2 is held, and b asks for resource 1, and it is held.

feedback from solution:

one way to do this is to have processes declare resources and the order they will request them up front. we can make a graph of that,
where edges are one resource to another. then we traverse and see if we have circular dependencies.
*/

#include <map>
#include <mutex>
#include <stdio.h>
#include <vector>

class LockNode
{
	public:
	  enum VisitState { FRESH, VISITING, VISITED };
		LockNode(int id, int max);
		void lock();
		void unlock();
		void joinTo(LockNode* node);
		void remove(LockNode* node);
		bool hasCycle(std::map<int, bool> touchedNodes);
		int getId();
		
	private:
	  bool hasCycle(std::vector<VisitState> visited, std::map<int, bool> touchedNodes);
	
	  std::vector<LockNode*> children;
		int lockId;
		std::mutex mtx_lock;
		int maxLocks;
};

class LockFactory
{
	private:
	  static LockFactory instance;
		static const int numberOfLocks = 5;
		
		std::vector<LockNode*> locks;
		std::map<int, std::vector<LockNode*>> lockOrder;
		LockFactory();
		
	public:
	  ~LockFactory();
	  static LockFactory& getInstance();
		bool hasCycle(std::map<int, bool> touchedNodes, std::vector<int> resourcesInOrder);
		/* to prevent deadlocks, force processes to declare upfront
		what order they will need locks in. verify that this order
		does not contain a deadlock ( a cycle in a directed graph).
		*/
		bool declare(int ownerId, std::vector<int> resourcesInOrder);
		// get lock, verifying first process is using in order it said it would
		LockNode* getLock(int ownerId, int resourceId);
		
};

LockFactory::LockFactory()
{
	locks.resize(numberOfLocks);
	for (int i = 0; i < numberOfLocks; i++)
	{
		locks[i] = new LockNode(i, numberOfLocks);
	}
}

LockFactory::~LockFactory()
{
	for (int i = 0; i < numberOfLocks; i++)
	{
		delete locks[i];
	}
}

LockFactory& LockFactory::getInstance()
{
	static LockFactory factory;
	return factory;
}

bool LockFactory::hasCycle(std::map<int, bool> touchedNodes, std::vector<int> resourcesInOrder)
{
	// checks for cycle
	for (int resource : resourcesInOrder)
	{
		if (touchedNodes[resource] == false)
		{
			LockNode* n = locks[resource];
			if (n->hasCycle(touchedNodes))
			{
				return true;
			}
		}
	}
	return false;
}


bool LockFactory::declare(int ownerId, std::vector<int> resourcesInOrder)
{
	std::map<int, bool> touchedNodes;
	
	// add nodes to graph
	int index = 1;
	touchedNodes[resourcesInOrder[0]] = false;
	for (index = 1; index < resourcesInOrder.size(); index++)
	{
		LockNode* prev = locks[resourcesInOrder[index - 1]];
		LockNode* curr = locks[resourcesInOrder[index]];
		prev->joinTo(curr);
		touchedNodes[resourcesInOrder[index]] = false;
	}
	
	// if we create a cycle, destroy resource list and return false
	if (hasCycle(touchedNodes, resourcesInOrder))
	{
		for (int j = 1; j < resourcesInOrder.size(); j++)
		{
			LockNode* p = locks[resourcesInOrder[j - 1]];
			LockNode* c = locks[resourcesInOrder[j]];
			p->remove(c);
		}
		return false;
	}
	
	/*
	no cycles deteced. save order that was declared, so that we can
	verify that the process is really calling the locks in the order
	it said it would
	*/
	
	std::vector<LockNode*> list;
	for (int i = 0; i < resourcesInOrder.size(); i++)
	{
		LockNode* resource = locks[resourcesInOrder[i]];
		list.push_back(resource);
	}
	
	lockOrder[ownerId] = list;
	return true;
}

LockNode* LockFactory::getLock(int ownerId, int resourceId)
{
	// TODO, check its in map
	std::vector<LockNode*> list = lockOrder[ownerId];
	LockNode* head = list[0];
	if (head->getId() == resourceId)
	{
		std::vector<LockNode*> new_list;
		for (int i = 1; i < list.size(); i++)
		{
			new_list.push_back(list[i]);
		}
		
		lockOrder[ownerId] = new_list;
		return head;
	}
	else
	{
		return nullptr;
	}
}


LockNode::LockNode(int id, int max) : lockId(id), maxLocks(max) {}

void LockNode::lock()
{
	mtx_lock.lock();
}

void LockNode::unlock()
{
	mtx_lock.unlock();
}


void LockNode::joinTo(LockNode* node)
{
	children.resize(children.size() + 1);
	children[children.size() - 1] = node;
	
}

void LockNode::remove(LockNode* node)
{
	std::vector<LockNode*> new_list;
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i] != node)
		{
			new_list.push_back(children[i]);
		}
	}
	children = new_list;
}


bool LockNode::hasCycle(std::map<int, bool> touchedNodes)
{
	std::vector<VisitState> visited(maxLocks);
	for (int i = 0; i < maxLocks; i++)
	{
		visited[i] = VisitState::FRESH;
	}
	return hasCycle(visited, touchedNodes);
}

bool LockNode::hasCycle(std::vector<VisitState> visited, std::map<int, bool> touchedNodes)
{
	if (touchedNodes.find(lockId) != touchedNodes.end())
	{
		touchedNodes[lockId] = true;
	}
	
	if (visited[lockId] == VisitState::VISITING)
	{
		// we looped back to this node while still visiting it, so we know theres a cycle
		return true;
	}
	else if (visited[lockId] == VisitState::FRESH)
	{
		visited[lockId] = VisitState::VISITING;
		for (LockNode* n : children)
		{
			if (n->hasCycle(visited, touchedNodes))
			{
				return true;
			}
		}
		visited[lockId] = VisitState::VISITED;
	}
	return false;
}

int LockNode::getId() { return lockId; }


int main()
{
	LockFactory factory = LockFactory::getInstance();
	int process_1_id = 0;
	int process_2_id = 1;
	int process_3_id = 2;
	std::vector<int> process_1_resource_requests = {1, 2, 3, 0};
	std::vector<int> process_2_resource_requests = {4};
	std::vector<int> process_3_resource_requests = {3, 1};
	
	bool res_1 = factory.declare(process_1_id, process_1_resource_requests);
	printf("resource %d result %d\n", process_1_id, res_1);
	bool res_2 = factory.declare(process_2_id, process_2_resource_requests);
	printf("resource %d result %d\n", process_2_id, res_2);
	bool res_3 = factory.declare(process_3_id, process_3_resource_requests);
	printf("resource %d result %d\n", process_3_id, res_3);
	return 0;
}

