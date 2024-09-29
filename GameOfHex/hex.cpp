//#include <iostream>
//#include <vector>
//#include <deque>
//#include <algorithm>
//#include <array>        // std::array
//#include <random>       // std::default_random_engine
//#include <chrono>       // std::chrono::system_clock
//
//constexpr auto infinity = 9999;
//constexpr auto max = 25;
//
//
//class HexGraph {
//public:
//	HexGraph() {
//		int count = 0;
//		edgeList.resize(n*n);
//		for (int i = 0; i < n; i++) {
//			for (int j = 0; j < n; j++) {
//				makeNode(i, j, edgeList[count++]);
//			}
//		}
//		borderNodes();
//		initializeLegalMoves();
//	}
//
//	void getLegalMoves() {
//		std::cout << "Legal moves:\n";
//		printVec(legalMoves);
//	}
//
//	void getBlueAndRed() {
//		std::cout << "BLUE:\n";
//		printVec(blueNodes);
//		std::cout << "RED:\n";
//		printVec(redNodes);
//	}
//
//	void placeBlue(int nn) {
//		blueNodes.push_back(nn);
//		legalMoves.erase(std::remove(legalMoves.begin(), legalMoves.end(), nn), legalMoves.end());
//	}
//
//	void placeRed(int nn) {
//		redNodes.push_back(nn);
//		legalMoves.erase(std::remove(legalMoves.begin(), legalMoves.end(), nn), legalMoves.end());
//	}
//
//	//blue: left-right; red: north-south
//
//	bool checkIfOverBlue() {
//
//		//std::cout << "Blue nodes temp:\n";
//		//printVec(blueNodesTemp);
//
//		if (blueNodesTemp.size() < n) return false;
//		else {
//			int bn = blueNodesTemp.size();
//			for (int i = 0; i < bn; i++) {
//				//std::cout << "i: " << i << std::endl;
//				int ln = blueNodesTemp[i];
//				if (ln % n == 0) {
//					for (int j = 0; j < bn; j++) {
//						//std::cout << "j: " << j << std::endl;
//						int rn = blueNodesTemp[j];
//						if (rn % n == n - 1) {
//							//std::cout << "i, j, ln, rn: " << i << ", " << j << ", " << ln << ", " << rn << std::endl;
//							if (dijkstra(blueNodesTemp, ln, rn)) return true;
//						}
//					}
//				}
//			}
//			return false;
//		}
//
//		//for blue and red nodes check if they contain one of left and right nodes or one of upper and lower nodes
//		//if there is a node on each side, use dijkstra to find a path. if there is a path, the game is over
//	}
//
//	int getN() {
//		return n;
//	}
//
//	void nextMove() {
//		int m = legalMoves.size();
//		evaluations.clear();
//		evaluations.resize(m);
//		int move = legalMoves[0];
//		////std::cout << "LegalMoves:\n";
//		////printVec(legalMoves);
//
//		for (int i = 0; i < m; i++) {
//			move = legalMoves[i];
//			std::vector<int> remaining = legalMoves;
//			remaining.erase(std::remove(remaining.begin(), remaining.end(), move), remaining.end());
//			//std::cout << "Remaining:\n";
//			//printVec(remaining);
//			for (int k = 0; k < 1000; k++) {
//				blueNodesTemp = blueNodes;
//				blueNodesTemp.push_back(move);
//				redNodesTemp = redNodes;
//				unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//				shuffle(remaining.begin(), remaining.end(), std::default_random_engine(seed));
//				fillPlaces(remaining);
//				//std::cout << "Blue and red nodes temp:\n";
//				//printVec(blueNodesTemp);
//				//printVec(redNodesTemp);
//				if (checkIfOverBlue()) evalCount++;
//			}
//			//std::cout << "COUNT = " << evalCount << std::endl;
//			evaluations[i] = evalCount;
//			evalCount = 0;
//		}
//		//std::cout << " ****************** " << std::endl;
//		std::cout << "evaluations:\n";
//		printVec(evaluations);
//		//std::cout << " ****************** " << std::endl;
//		auto i = max_element(evaluations.begin(), evaluations.end());
//		//std::cout << "*i = " <<*i << std::endl;
//		int index = std::distance(evaluations.begin(), i);
//		//std::cout << "index  = " << index << std::endl;
//		int newMove = legalMoves[index];
//		std::cout << "Blue Move = " << newMove << std::endl;
//		placeBlue(newMove);
//	}
//
//	bool dijkstra(std::vector<int> nodes, int startnode, int endnode) {
//
//		//std::cout << "DIJKSTRA ( " << startnode << ", " << endnode << " )" << std::endl;
//
//		//std::sort(nodes.begin(), nodes.end());
//		//printVec(nodes);
//		//std::cout << "nodes size " << nodes.size() << std::endl;
//
//		int cost[max][max], distance[max], pred[max];
//		int visited[max], count, mindistance, nextnode, i, j;
//		nextnode = 0;
//		for (i = 0; i < nodes.size(); i++) {
//			int node1 = nodes[i];
//			//std::cout << "node1 = " << node1 << std::endl;
//			for (j = 0; j < nodes.size(); j++) {
//				//std::cout << "i, j: " << i << ", " << j << std::endl;
//				int node2 = nodes[j];
//				//std::cout << "node2 = " << node2 << std::endl;
//				if (std::find(edgeList[node1].begin(), edgeList[node1].end(), node2) == edgeList[node1].end()) {
//					cost[i][j] = infinity;  //find out cost according to edgelist. i must be in blue/red nodes vector
//					//std::cout << "cost infinity" << std::endl;
//				}
//				else
//					cost[i][j] = 1;
//			}
//		}
//
//		//std::cout << "COSTS: " << std::endl;
//		//for (int i = 0; i < nodes.size(); i++) {
//		//	for (j = 0; j < nodes.size(); j++) {
//		//		std::cout << cost[i][j] << "  ";
//		//	}
//		//	std::cout << "\n";
//		//}
//
//		std::vector<int>::iterator i1 = std::find(nodes.begin(), nodes.end(), startnode);
//		int ind1 = std::distance(nodes.begin(), i1);
//		std::vector<int>::iterator i2 = std::find(nodes.begin(), nodes.end(), endnode);
//		int ind2 = std::distance(nodes.begin(), i2);
//
//		//std::cout << "ind1, ind2: " << ind1 << ", " << ind2 << std::endl;
//
//
//		for (i = 0; i < nodes.size(); i++) {
//			distance[i] = cost[ind1][i];
//			pred[i] = ind1;
//			visited[i] = 0;
//		}
//		distance[ind1] = 0;
//		visited[ind1] = 1;
//		count = 1;
//		while (count < nodes.size() - 1) {
//			mindistance = infinity;
//			for (i = 0; i < nodes.size(); i++)
//				if (distance[i] < mindistance && !visited[i]) {
//					mindistance = distance[i];
//					nextnode = i;
//				}
//			visited[nextnode] = 1;
//			for (i = 0; i < nodes.size(); i++)
//				if (!visited[i])
//					if (mindistance + cost[nextnode][i] < distance[i]) {
//						distance[i] = mindistance + cost[nextnode][i];
//						pred[i] = nextnode;
//					}
//			count++;
//		}
//		if (ind2 != ind1) {
//			if (distance[ind2] >= infinity) { return false; }
//			else {
//				//std::cout << "TRUE" << std::endl;
//				return true;
//			}
//		}
//		else {
//			//std::cout << "FALSE" << std::endl;
//			return false;
//		}
//	}
//
//private:
//	int n = 5;
//	int evalCount{0};
//	std::vector<int> leftNodes;
//	std::vector<int> rightNodes;
//	std::vector<int> upperNodes;
//	std::vector<int> lowerNodes;
//	std::vector<std::deque<int>> edgeList;
//	std::vector<int> blueNodes;
//	std::vector<int> redNodes;
//	std::vector<int> blueNodesTemp;
//	std::vector<int> redNodesTemp;
//	std::vector<int> stones;
//	std::vector<int> legalMoves;
//	std::vector<int> evaluations;
//
//	void borderNodes() {
//		for (int i = 0; i < n; i++) {
//			leftNodes.push_back(n * i);
//			rightNodes.push_back(n * (i + 1) - 1);
//			upperNodes.push_back(i);
//			lowerNodes.push_back((n - 1) * n + i);
//		}
//	}
//
//
//	void makeNode(int i, int j, std::deque<int>& eL) {
//
//		if (i == 0 && j == 0) {
//			eL.push_front(1);
//			eL.push_front(n);
//		}
//		else if (i == 0 && j == n-1) {
//			eL.push_front(n - 2);
//			eL.push_front(2 * n - 2);
//			eL.push_front(2 * n - 1);
//		}
//		else if (i == n-1 && j == 0) {
//			eL.push_front((n - 2) * n);
//			eL.push_front((n - 2) * n + 1);
//			eL.push_front((n - 1) * n + 1);
//		}
//		else if (i == n-1 && j == n-1) {
//			eL.push_front((n - 1) * n - 1);
//			eL.push_front(n * n - 2);
//		}
//		else if (i == 0) {
//			eL.push_front(j - 1);
//			eL.push_front(j + 1);
//			eL.push_front(j + n - 1);
//			eL.push_front(j + n);
//		}
//		else if (i == n - 1) {
//			eL.push_front((n - 2)* n + j);
//			eL.push_front((n - 2) * n + j + 1);
//			eL.push_front((n - 1) * n + j - 1);
//			eL.push_front((n - 1) * n + j + 1);
//		}
//		else if (j == 0) {
//			eL.push_front((i-1) * n);
//			eL.push_front((i-1) * n + 1);
//			eL.push_front(i * n + 1);
//			eL.push_front((i + 1) * n);
//		}
//		else if (j == n - 1) {
//			eL.push_front(i * n + j - 1);
//			eL.push_front((i + 1) * n + j - 1);
//			eL.push_front((i + 1) * n + j);
//			eL.push_front((i - 1) * n + j);
//		}
//		else {
//			eL.push_front(i * n + j + 1);
//			eL.push_front(i * n + j - 1);
//			eL.push_front((i + 1) * n + j - 1);
//			eL.push_front((i + 1) * n + j);
//			eL.push_front((i - 1) * n + j);
//			eL.push_front((i - 1) * n + j + 1);
//		}
//	}
//
//	void initializeLegalMoves() {
//		for (int i = 0; i < n * n; i++) {
//			legalMoves.push_back(i);
//			evaluations.push_back(0);
//		}
//	}
//
//	void fillPlaces(std::vector<int>& places) {
//		int len = places.size();
//		int k = static_cast<int> (len / 2.0 + 0.5);
//		for (int i = 0; i < k; i++) {
//			redNodesTemp.push_back(places[i]);
//		}
//		for (int i = k; i < len; i++) {
//			blueNodesTemp.push_back(places[i]);
//		}
//		//std::cout << "Blue and red nodes temp:\n";
//		//printVec(blueNodesTemp);
//		//printVec(redNodesTemp);
//	}
//
//
//
//	bool dfs() {
//
//	}
//
//	void printVec(std::vector<int> vec) {
//		for (int i = 0; i < vec.size(); i++) {
//			std::cout << vec[i] << "\t";
//		}
//		std::cout << std::endl;
//	}
//
//};
//
//int main() {
//
//	bool over = 0;
//	int i, j, nn;
//
//	HexGraph hexBoard;
//
//	//hexBoard.getLegalMoves();
//
//	hexBoard.placeBlue(12);
//
//	//hexBoard.getBlueAndRed();
//	//hexBoard.getLegalMoves();
//	int rm{0};
//	for (int i = 0; i < 3; i++) {
//		std::cout << "RED MOVE:\n";
//		std::cin >> rm;
//		hexBoard.placeRed(rm);
//		hexBoard.nextMove();
//	}
//
//	//hexBoard.getBlueAndRed();
//	//hexBoard.getLegalMoves();
//
//	//hexBoard.placeBlue(2, 3);
//	//hexBoard.placeBlue(1, 0);
//	//hexBoard.placeBlue(1, 2);
//	//hexBoard.placeBlue(1, 3);
//	//over = hexBoard.checkIfOverBlue();
//	
//	//while (true) {
//	//	std::cout << "Blue move: " << std::endl;
//	//	std::cin >> i >> j;
//	//	nn = hexBoard.getN() * i + j;
//	//	hexBoard.placeBlue(nn);
//	//	over = hexBoard.checkIfOverBlue();
//	//	if (over) break;
//	//	std::cout << "Red move: " << std::endl;
//	//	std::cin >> i >> j;
//	//	nn = hexBoard.getN() * i + j;
//	//	hexBoard.placeRed(nn);
//	//	//over = hexBoard.checkIfOverRed();
//	//	//if (over) break;
//	//}
//
//	//std::cout << "OVER!" << over << std::endl;
//
//	//std::vector<int> nodes = { 5, 10, 11, 3, 4, 12, 13, 14, 18, 19, 15, 21, 7 };
//	//hexBoard.dijkstra(nodes, 21, 14);
//
//	return 0;
//}
