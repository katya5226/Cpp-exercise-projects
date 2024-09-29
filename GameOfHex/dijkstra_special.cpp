//#include<iostream>
//#include<stdio.h>
//#include<vector>
//
//#define INFINITY 9999
//#define max 5
//
//bool dijkstra(std::vector<int> nodes, int startnode, int endnode) {
//
//	std::cout << "DIJKSTRA ( " << startnode << ", " << endnode << " )" << std::endl;
//
//	int n = 5;
//
//	//std::sort(nodes.begin(), nodes.end());
//	//printVec(nodes);
//	//std::cout << "nodes size " << nodes.size() << std::endl;
//
//	int cost[max][max], distance[max], pred[max];
//	int visited[max], count, mindistance, nextnode, i, j;
//	nextnode = 0;
//	for (i = 0; i < nodes.size(); i++) {
//		int node1 = nodes[i];
//		//std::cout << "node1 = " << node1 << std::endl;
//		for (j = 0; j < nodes.size(); j++) {
//			//std::cout << "i, j: " << i << ", " << j << std::endl;
//			int node2 = nodes[j];
//			//std::cout << "node2 = " << node2 << std::endl;
//			if (std::find(edgeList[node1].begin(), edgeList[node1].end(), node2) == edgeList[node1].end()) {
//				cost[i][j] = INFINITY;  //find out cost according to edgelist. i must be in blue/red nodes vector
//				//std::cout << "cost infinity" << std::endl;
//			}
//			else
//				cost[i][j] = 1;
//		}
//	}
//
//	//std::cout << "COSTS: " << std::endl;
//	//for (int i = 0; i < nodes.size(); i++) {
//	//	for (j = 0; j < nodes.size(); j++) {
//	//		std::cout << cost[i][j] << "  ";
//	//	}
//	//	std::cout << "\n";
//	//}
//
//	std::vector<int>::iterator i1 = std::find(nodes.begin(), nodes.end(), startnode);
//	int ind1 = std::distance(nodes.begin(), i1);
//	std::vector<int>::iterator i2 = std::find(nodes.begin(), nodes.end(), endnode);
//	int ind2 = std::distance(nodes.begin(), i2);
//
//
//	for (i = 0; i < nodes.size(); i++) {
//		distance[i] = cost[ind1][i];
//		pred[i] = ind1;
//		visited[i] = 0;
//	}
//	distance[ind1] = 0;
//	visited[ind1] = 1;
//	count = 1;
//	while (count < nodes.size() - 1) {
//		mindistance = INFINITY;
//		for (i = 0; i < n; i++)
//			if (distance[i] < mindistance && !visited[i]) {
//				mindistance = distance[i];
//				nextnode = i;
//			}
//		visited[nextnode] = 1;
//		for (i = 0; i < nodes.size(); i++)
//			if (!visited[i])
//				if (mindistance + cost[nextnode][i] < distance[i]) {
//					distance[i] = mindistance + cost[nextnode][i];
//					pred[i] = nextnode;
//				}
//		count++;
//	}
//	if (ind2 != ind1) {
//		if (distance[ind2] >= INFINITY) { std::cout << "FALSE" << std::endl; return false; }
//		else {
//			std::cout << "TRUE" << std::endl;
//			return true;
//		}
//	}
//	else {
//		std::cout << "FALSE" << std::endl;
//		return false;
//	}
//}
//
