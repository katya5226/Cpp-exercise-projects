#include "graph.h"


//class Node {
//public:
//	int id;
//	Node(int id) : id(id) {}
//};

//class Edge {
//	std::shared_ptr<Node> node1;
//	std::shared_ptr<Node> node2;
//	int cost;
//public:
//	Edge(std::shared_ptr<Node>&, std::shared_ptr<Node>&, int);
//};

//class Graph {
//public:
//	Graph(std::ifstream&);
//};


Graph::Graph(std::ifstream& graphData) {
	if (!graphData.is_open()) {
		std::cerr << "There was a problem opening the input file!\n";
		exit(1);
	}

	int numNodes{ 0 };
	graphData >> numNodes;

	for (int i = 0; i < numNodes; i++) {

		nodes.push_back(new Node(i));
	}

	int id1, id2, cost;

	while (graphData >> id1 >> id2 >> cost) {
		edges.push_back(new Edge(nodes.at(id1), nodes.at(id2), cost));
	}

	graphData.close();
}

Graph::~Graph() {
	for (auto p : nodes) {
		delete p;
	}
	for (auto p : edges) {
		delete p;
	}
}

Edge::Edge(Node* n1, Node* n2, int c) {
	node1 = n1;
	node2 = n2;
	cost = c;
}

//bool operator<(const Edge& a, const Edge& b) {
//	return a.cost < b.cost;
//}

bool Edge::operator<(const Edge& a) {
	std::cout << "OVERLOADED OPERATOR < " << std::endl;
	return cost < a.cost;
}

void Graph::sortEdges(std::vector<Edge*>& v) {
	std::vector<Edge> vec;

	for (int i = 0; i < v.size(); i++) {
		vec.push_back(*v[i]);
	}

	sort(vec.begin(), vec.end());

	for (int i = 0; i < v.size(); i++) {
		vec.push_back(*v[i]);
	}

};