#include "graph.h"


bool comparePtrToEdge(Edge* a, Edge* b) { return (a->cost < b->cost); }
bool comparePtrToNode(Node* a, Node* b) { return (a->id < b->id); }

bool checkIfGood(Edge* edge, std::vector<std::vector<Node*>>& trees) {
	bool good = true;
	for (int j = 0; j < trees.size(); j++) {

		Node* key1 = edge->node1;
		Node* key2 = edge->node2;

		if (std::find(trees[j].begin(), trees[j].end(), key1) != trees[j].end()) {
			if (std::find(trees[j].begin(), trees[j].end(), key2) != trees[j].end()) good = false;
		}
	}
	return good;
}


void unifyTrees(Node* node1, Node* node2, std::vector<std::vector<Node*>>& trees) {

	int index1{ -1 };
	int index2{ -1 };

	for (int j = 0; j < trees.size(); j++) {

		auto it1 = std::find(trees[j].begin(), trees[j].end(), node1);
		auto it2 = std::find(trees[j].begin(), trees[j].end(), node2);

		if (it1 != trees[j].end()) index1 = j;
		if (it2 != trees[j].end()) index2 = j;
	}

	std::vector<Node*> A;
	std::vector<Node*> B;
	std::vector<Node*> AB;

	if (index1 == -1 && index2 == -1) {
		AB.push_back(node1);
		AB.push_back(node2);
		trees.push_back(AB);
	}
	else if (index1 != -1 && index2 == -1) {
		A = trees[index1];
		A.push_back(node2);
		trees.erase(trees.begin() + index1);
		trees.push_back(A);

	}
	else if (index1 == -1 && index2 != -1) {
		B = trees[index2];
		B.push_back(node1);
		trees.erase(trees.begin() + index2);
		trees.push_back(B);
	}
	else {
		//std::cout << "I AM HERE" << std::endl;
		A = trees[index1];
		B = trees[index2];
		AB;

		AB.reserve(A.size() + B.size()); // preallocate memory
		AB.insert(AB.end(), A.begin(), A.end());
		AB.insert(AB.end(), B.begin(), B.end());

		trees.push_back(AB);
		//for (int i = 0; i < trees.size(); i++) {

		//	for (int j = 0; j < trees[i].size(); j++) {

		//		std::cout << trees[i][j]->id << "  ";
		//	}
		//	std::cout << '\n';
		//}
		//std::cout << '\n';

		trees.erase(trees.begin(), trees.begin() + 1);
		//for (int i = 0; i < trees.size(); i++) {

		//	for (int j = 0; j < trees[i].size(); j++) {

		//		std::cout << trees[i][j]->id << "  ";
		//	}
		//	std::cout << '\n';
		//}

	}
	//std::cout << "trees:\n" << std::endl;
	//for (int i = 0; i < trees.size(); i++) {

	//	for (int j = 0; j < trees[i].size(); j++) {

	//		std::cout << trees[i][j]->id << "  ";
	//	}
	//	std::cout << '\n';
	//}
	//std::cout << "end trees:\n" << std::endl;
}


int main() {

	std::ifstream graphData("graph.txt", std::ios::in);

	Graph myGraph(graphData);

	std::vector<Node*> nodes = myGraph.getNodes();
	std::vector<Edge*> edges = myGraph.getEdges();

	sort(edges.begin(), edges.end(), comparePtrToEdge);

	std::vector<std::vector<Node*>> trees;

	std::vector<Edge*> spanningTree;

	for (int i = 0; i < edges.size(); i++) {
		Node* a = edges[i]->node1;
		Node* b = edges[i]->node2;

		if (checkIfGood(edges[i], trees)) {
			spanningTree.push_back(edges[i]);
			unifyTrees(a, b, trees);
		}
		else {
			//std::cout << "LOOP!" << std::endl;
		}
		
	}

	int cost{0};

	for (int i = 0; i < spanningTree.size(); i++) {

		std::cout << spanningTree[i]->node1->id << "  "
			<< spanningTree[i]->node2->id << "  "
			<< spanningTree[i]->cost << std::endl;
		
		cost += spanningTree[i]->cost;
	}

	std::cout << "COST: " << cost;

	return 0;
}