//graph class
#ifndef __MST__
#define __MST__

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <algorithm>

//class Node;
//class Edge;

class Node {
public:
	int id;
	Node(int id) : id(id) {}
};

class Edge {
public:
	Node* node1;
	Node* node2;
	int cost;
	Edge(Node*, Node*, int);
	bool operator<(const Edge&);
	//friend bool operator<(const Edge&, const Edge&);
};


class Graph {

	std::vector<Node*> nodes;
	std::vector<Edge*> edges;

public:
	Graph(std::ifstream&);
	~Graph();

	std::vector<Node*> getNodes() { return nodes; }
	std::vector<Edge*> getEdges() { return edges; }
	void sortEdges(std::vector<Edge*>&);
};

//class Node {
//public:
//	int id;
//	Node(int id) : id(id) {}
//};
//
//class Edge {
//	std::shared_ptr<Node> node1;
//	std::shared_ptr<Node> node2;
//	int cost;
//public:
//	Edge(std::shared_ptr<Node>&, std::shared_ptr<Node>&, int);
//};
//
//class Graph {
//public:
//	Graph(std::ifstream&);
//};












#endif // !__MST__