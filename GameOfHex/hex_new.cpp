#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include<list>

constexpr auto infinity = 9999;
constexpr auto max = 25;


class HexGraph {
public:
	HexGraph() {
		int count = 0;
		edgeList.resize(n * n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				makeNode(i, j, edgeList[count++]);
			}
		}
		adj = new std::list<int>[n*n];

		for (int i = 0; i < n*n; i++) {
			for (int j = 0; j < edgeList[i].size(); j++) {
				adj[i].push_back(edgeList[i][j]);
			}
		}

		for (int i = 0; i < n*n; i++) {
			for (auto j: adj[i]) {
				std::cout << j << "\t";
			}
			std::cout << "\n";
		}

		borderNodes();
		initializeLegalMoves();
	}
	~HexGraph() {
		delete[] adj;
	}

	void getLegalMoves() {
		std::cout << "Legal moves:\n";
		printVec(legalMoves);
	}

	void getBlueAndRed() {
		std::cout << "BLUE:\n";
		printVec(blueNodes);
		std::cout << "RED:\n";
		printVec(redNodes);
	}

	void placeBlue(int nn) {
		blueNodes.push_back(nn);
		legalMoves.erase(std::remove(legalMoves.begin(), legalMoves.end(), nn), legalMoves.end());
	}

	void placeRed(int nn) {
		redNodes.push_back(nn);
		legalMoves.erase(std::remove(legalMoves.begin(), legalMoves.end(), nn), legalMoves.end());
	}

	//blue: left-right; red: north-south

	bool checkIfOverBlue() {

		if (blueNodesTemp.size() < n) return false;
		else {
			int bn = blueNodesTemp.size();
			for (int i = 0; i < bn; i++) {
				int ln = blueNodesTemp[i];
				if (ln % n == 0) {
					for (int j = 0; j < bn; j++) {
						int rn = blueNodesTemp[j];
						if (rn % n == n - 1) {
							//if (dijkstra(blueNodesTemp, i, j)) return true;
							if (DFS(blueNodesTemp, i, j)) return true;
						}
					}
				}
			}
			return false;
		}

		//for blue and red nodes check if they contain one of left and right nodes or one of upper and lower nodes
		//if there is a node on each side, use dijkstra to find a path. if there is a path, the game is over
	}

	int getN() {
		return n;
	}

	void nextMove() {
		int m = legalMoves.size();
		evaluations.clear();
		evaluations.resize(m);
		int move = legalMoves[0];

		//std::cout << "m = " << m << std::endl;

		for (int i = 0; i < m; i++) {
			move = legalMoves[i];
			std::vector<int> remaining = legalMoves;
			remaining.erase(std::remove(remaining.begin(), remaining.end(), move), remaining.end());
			for (int k = 0; k < 100; k++) {
				blueNodesTemp = blueNodes;
				blueNodesTemp.push_back(move);
				unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
				shuffle(remaining.begin(), remaining.end(), std::default_random_engine(seed));
				fillPlaces(remaining);
				if (checkIfOverBlue()) evalCount++;
			}
			evaluations[i] = evalCount;
			evalCount = 0;
			//std::cout << "i = " << i << std::endl;
		}
		auto i = max_element(evaluations.begin(), evaluations.end());
		int index = std::distance(evaluations.begin(), i);
		int newMove = legalMoves[index];
		std::cout << "Blue Move = " << newMove << std::endl;
		placeBlue(newMove);
	}

	bool dijkstra(std::vector<int> nodes, int startnode, int endnode) {

		int distance[max], pred[max];
		int visited[max], count, mindistance, nextnode, i, j;
		nextnode = 0;


		for (i = 0; i < nodes.size(); i++) {
			distance[i] = cost[nodes[startnode]][nodes[i]];
			pred[i] = startnode;
			visited[i] = 0;
		}
		distance[startnode] = 0;
		visited[startnode] = 1;
		count = 1;
		while (count < nodes.size() - 1) {
			mindistance = infinity;
			for (i = 0; i < nodes.size(); i++)
				if (distance[i] < mindistance && !visited[i]) {
					mindistance = distance[i];
					nextnode = i;
				}
			visited[nextnode] = 1;
			for (i = 0; i < nodes.size(); i++)
				if (!visited[i])
					if (mindistance + cost[nodes[nextnode]][nodes[i]] < distance[i]) {
						distance[i] = mindistance + cost[nodes[nextnode]][nodes[i]];
						pred[i] = nextnode;
					}
			count++;
		}
		if (endnode != startnode) {
			if (distance[endnode] >= infinity) { return false; }
			else {
				return true;
			}
		}
		else {
			return false;
		}
	}

private:
	int n = 5;
	int evalCount{ 0 };
	std::vector<int> leftNodes;
	std::vector<int> rightNodes;
	std::vector<int> upperNodes;
	std::vector<int> lowerNodes;
	std::vector<std::deque<int>> edgeList;
	std::list<int>* adj;
	std::vector<int> blueNodes;
	std::vector<int> redNodes;
	std::vector<int> blueNodesTemp;
	std::vector<int> redNodesTemp;
	std::vector<int> stones;
	std::vector<int> legalMoves;
	std::vector<int> evaluations;
	int cost[max][max];

	void borderNodes() {
		for (int i = 0; i < n; i++) {
			leftNodes.push_back(n * i);
			rightNodes.push_back(n * (i + 1) - 1);
			upperNodes.push_back(i);
			lowerNodes.push_back((n - 1) * n + i);
		}
	}


	void makeNode(int i, int j, std::deque<int>& eL) {

		if (i == 0 && j == 0) {
			eL.push_front(1);
			eL.push_front(n);
		}
		else if (i == 0 && j == n - 1) {
			eL.push_front(n - 2);
			eL.push_front(2 * n - 2);
			eL.push_front(2 * n - 1);
		}
		else if (i == n - 1 && j == 0) {
			eL.push_front((n - 2) * n);
			eL.push_front((n - 2) * n + 1);
			eL.push_front((n - 1) * n + 1);
		}
		else if (i == n - 1 && j == n - 1) {
			eL.push_front((n - 1) * n - 1);
			eL.push_front(n * n - 2);
		}
		else if (i == 0) {
			eL.push_front(j - 1);
			eL.push_front(j + 1);
			eL.push_front(j + n - 1);
			eL.push_front(j + n);
		}
		else if (i == n - 1) {
			eL.push_front((n - 2) * n + j);
			eL.push_front((n - 2) * n + j + 1);
			eL.push_front((n - 1) * n + j - 1);
			eL.push_front((n - 1) * n + j + 1);
		}
		else if (j == 0) {
			eL.push_front((i - 1) * n);
			eL.push_front((i - 1) * n + 1);
			eL.push_front(i * n + 1);
			eL.push_front((i + 1) * n);
		}
		else if (j == n - 1) {
			eL.push_front(i * n + j - 1);
			eL.push_front((i + 1) * n + j - 1);
			eL.push_front((i + 1) * n + j);
			eL.push_front((i - 1) * n + j);
		}
		else {
			eL.push_front(i * n + j + 1);
			eL.push_front(i * n + j - 1);
			eL.push_front((i + 1) * n + j - 1);
			eL.push_front((i + 1) * n + j);
			eL.push_front((i - 1) * n + j);
			eL.push_front((i - 1) * n + j + 1);
		}

		for (i = 0; i < max; i++) {
			for (j = 0; j < max; j++) {
				if (std::find(edgeList[i].begin(), edgeList[i].end(), j) == edgeList[i].end()) {
					cost[i][j] = infinity;  //find out cost according to edgelist. i must be in blue/red nodes vector
					//std::cout << "cost infinity" << std::endl;
				}
				else
					cost[i][j] = 1;
			}
		}
	}

	void initializeLegalMoves() {
		for (int i = 0; i < n * n; i++) {
			legalMoves.push_back(i);
			evaluations.push_back(0);
		}
	}

	void fillPlaces(std::vector<int>& places) {
		int len = places.size();
		int k = static_cast<int> (len / 2.0 + 0.5);
		//for (int i = 0; i < k; i++) {
		//	redNodesTemp.push_back(places[i]);
		//}
		for (int i = k; i < len; i++) {
			blueNodesTemp.push_back(places[i]);
		}
		//std::cout << "Blue and red nodes temp:\n";
		//printVec(blueNodesTemp);
		//printVec(redNodesTemp);
	}


	void DFSUtil(std::vector<int>& nodes, int startnode, bool visited[])
	{
		visited[startnode] = true;

		std::list<int>::iterator i;
		for (i = adj[nodes[startnode]].begin(); i != adj[nodes[startnode]].end(); ++i) {
			//std::cout << *i << "\n";
			int v = *i;
			std::vector<int>::iterator it = std::find(nodes.begin(), nodes.end(), v);
			if (it != nodes.end()) {
				int ind = std::distance(nodes.begin(), it);
				if (!visited[ind])
					DFSUtil(nodes, ind, visited);
			}
		}

	}

	bool DFS(std::vector<int>& nodes, int startnode, int endnode)
	{
		//std::cout << "nodes size: " << nodes.size() << std::endl;

		bool* visited = new bool[nodes.size()];
		for (int i = 0; i < nodes.size(); i++)
			visited[i] = false;

		DFSUtil(nodes, startnode, visited);
		if (visited[endnode] == true) return true;
		delete[] visited;
		return false;
	}

	void printVec(std::vector<int> vec) {
		for (int i = 0; i < vec.size(); i++) {
			std::cout << vec[i] << "\t";
		}
		std::cout << std::endl;
	}

};

int main() {

	bool over = 0;
	int i, j, nn;

	HexGraph hexBoard;

	hexBoard.placeBlue(12);

	int rm{ 0 };
	for (int i = 0; i < 2; i++) {
		std::cout << "RED MOVE:\n";
		std::cin >> rm;
		hexBoard.placeRed(rm);
		auto start = std::chrono::steady_clock::now();
		hexBoard.nextMove();
		auto end = std::chrono::steady_clock::now();
		std::cout << "Time: " << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << std::endl;
	}

	return 0;
}
