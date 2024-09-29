#include <iostream>
#include <vector>

constexpr auto INT_MAX_ = 1000000;

class Node;
class Edge;

std::vector<Node*> nodes;
std::vector<Edge*> edges;

class Node {
public:
	char id;
	Node* previous;
	int distFromStart;

	Node(char id) : id(id), previous(NULL), distFromStart(INT_MAX_) {
		nodes.push_back(this);
	};
};

class Edge {
public:
	Node* node1;
	Node* node2;
	int dist;

	Edge(Node* node1, Node* node2, int dist) : node1(node1), node2(node2), dist(dist) {
		edges.push_back(this);
	};
	bool connects(Node*, Node*);
};


void dijkstrasTest();
void dijkstras();
std::vector<Node*>* adjacentRemainingNodes(Node*);
Node* extractSmallest(std::vector<Node*>&);
int distance(Node*, Node*);
bool contains(std::vector<Node*>&, Node*);
void printShortestRouteTo(Node*);

void dijkstrasTest() {
	Node* a = new Node('a');
	Node* b = new Node('b');
	Node* c = new Node('c');
	Node* d = new Node('d');
	Node* e = new Node('e');
	Node* f = new Node('f');
	Node* g = new Node('g');

	Edge* e1 = new Edge(a, c, 1);
	Edge* e2 = new Edge(a, d, 2);
	Edge* e3 = new Edge(b, c, 2);
	Edge* e4 = new Edge(c, d, 1);
	Edge* e5 = new Edge(b, f, 3);
	Edge* e6 = new Edge(c, e, 3);
	Edge* e7 = new Edge(e, f, 2);
	Edge* e8 = new Edge(d, g, 1);
	Edge* e9 = new Edge(g, f, 1);

	a->distFromStart = 0;
	dijkstras();
	printShortestRouteTo(a);
	printShortestRouteTo(b);
	printShortestRouteTo(c);
	printShortestRouteTo(d);
	printShortestRouteTo(e);
	printShortestRouteTo(f);

	delete(a);
	delete(b);
	delete(c);
	delete(d);
	delete(e);
	delete(f);
	delete(g);
	delete(e1);
	delete(e2);
	delete(e3);
	delete(e4);
	delete(e5);
	delete(e6);
	delete(e7);
	delete(e8);
	delete(e9);
}

bool contains(std::vector<Node*>& nodes, Node* node) {
	for (int i = 0; i < nodes.size(); i++) {
		if (nodes.at(i) == node) return true;
	}
	return false;
}

std::vector<Node*>* adjacentRemainingNodes(Node* node) {
	
	std::vector<Node*>* adjacents = new std::vector<Node*>();

	for (int i = 0; i < edges.size(); i++) {
		Edge* edge1 = edges.at(i);
		Node* adjacent = NULL;

		if (edge1->node1 == node) {
			adjacent = edge1->node2;
		}
		else if (edge1->node2 == node) {
			adjacent = edge1->node1;
		}
		if (adjacent && contains(nodes, adjacent)) {
			adjacents->push_back(adjacent);
		}
	}
	return adjacents;
}

int distance(Node* node1, Node* node2) {
	for (int i = 0; i < edges.size(); i++) {
		Edge* edge = edges.at(i);
		if (edge->connects(node1, node2)) {
			return edge->dist;
		}
	}
	return -1;
}

bool Edge::connects(Node* node1, Node* node2) {
	return (
		(node1 == this->node1 && node2 == this->node2) ||
		(node2 == this->node1 && node1 == this->node2)
		);
}

Node* extractSmallest(std::vector<Node*>& nodes) {
	int size = nodes.size();
	if (size == 0) return NULL;
	int smallestPosition = 0;
	Node* smallest1 = nodes.at(0);
	for (int i = 1; i < size; i++) {
		Node* current = nodes.at(i);
		if (current->distFromStart < smallest1->distFromStart) {
			smallest1 = current;
			smallestPosition = i;
		}
	}
	nodes.erase(nodes.begin() + smallestPosition);
	return smallest1;
}

void dijkstras() {
	while (nodes.size() > 0) {
		Node* smallest = extractSmallest(nodes); //push the smallest distance (from start) node to the open set
		std::vector<Node*>* adjacents = adjacentRemainingNodes(smallest);

		for (int i = 0; i < adjacents->size(); i++) { //for adjacent nodes to smallest distance node, update distance from start in the closed set
			Node* adjacent = adjacents->at(i);
			int distn = distance(smallest, adjacent) + smallest->distFromStart;

			if (distn < adjacent->distFromStart) {
				adjacent->distFromStart = distn;
				adjacent->previous = smallest;
			}
		}
		delete adjacents;
	}
}

void printShortestRouteTo(Node* destination)
{
	Node* previous = destination;
	std::cout << "Distance from start: "
		<< destination->distFromStart << std::endl;
	while (previous)
	{
		std::cout << previous->id << " ";
		previous = previous->previous;
	}
	std::cout << std::endl;
}

int main() {

	dijkstrasTest();
	return 0;
}