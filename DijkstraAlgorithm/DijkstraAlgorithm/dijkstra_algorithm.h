#ifndef __DIJKSTRA_A
#define __DIJKSTRA_A

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

#endif
