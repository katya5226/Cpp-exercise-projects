#include <iostream>
#include <vector>
#include <algorithm>
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
#include <time.h>


class Graph {
public:
	std::vector<int> stones;

	Graph(int n) {
		hsize = n;
		size = n * n;
		stones.resize(n * n);
		for (int i = 0; i < size; i++) {
			stones[i] = 0;
		}
		Edges.resize(n * n);
		int count = 0;
		for (int i = 0; i < hsize; i++) {
			for (int j = 0; j < hsize; j++) {
				makeEdges(i, j, Edges[count++]);
			}
		}
	}

	void next_move() {
		auto start = std::chrono::high_resolution_clock::now();

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

		std::vector<int> fixed = stones;

		std::vector<int> remaining;
		remaining.resize(size - numMoves - 1);
		int rs = static_cast<int>(remaining.size()/2);

		for (int i = 0; i < rs ; i++) {
			remaining[i] = 1;
			remaining[rs+i] = 2;
		}

		std::vector<int> evaluations(size, 0);
		for (int i = 0; i < size; i++) {
			if (fixed[i] == 0) {
				stones[i] = 1;
				for (int k = 0; k < 100; k++) {
					shuffle(remaining.begin(), remaining.end(), std::default_random_engine(seed));
					int it = 0;

					//printVec(remaining);
					//printVec(stones);
					//printVec(fixed);

					for (int j = 0; j < size; j++) {
						if (fixed[j] == 0 && j != i) {
							stones[j] = remaining[it];
							it++;
						}
					}
					if (who_won() == 1) evaluations[i]++;
				}

			}
		}
		auto i = max_element(evaluations.begin(), evaluations.end());
		int index = std::distance(evaluations.begin(), i);
		stones = fixed;
		std::cout << "Next blue move: " << index << std::endl;
		stones[index] = 1;
		numMoves++;
		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
		std::cout << "1 move duration: " << duration.count() << " seconds" << std::endl;
	}

	void increase_moves() {
		numMoves++;
	}

	void printVec(std::vector<int> vec) {
		for (int i = 0; i < vec.size(); i++) {
			std::cout << vec[i] << "\t";
		}
		std::cout << std::endl;
	}

private:
	std::vector<std::vector<int>> Edges;
	int hsize;
	int size;
	int numMoves{ 0 };

	void makeEdges(int i, int j, std::vector<int>& v) {

		if (i == 0 && j == 0) {
			v.push_back(1);
			v.push_back(hsize);
		}
		else if (i == 0 && j == hsize - 1) {
			v.push_back(hsize - 2);
			v.push_back(2 * hsize - 2);
			v.push_back(2 * hsize - 1);
		}
		else if (i == hsize - 1 && j == 0) {
			v.push_back((hsize - 2) * hsize);
			v.push_back((hsize - 2) * hsize + 1);
			v.push_back((hsize - 1) * hsize + 1);
		}
		else if (i == hsize - 1 && j == hsize - 1) {
			v.push_back((hsize - 1) * hsize - 1);
			v.push_back(hsize * hsize - 2);
		}
		else if (i == 0) {
			v.push_back(j - 1);
			v.push_back(j + 1);
			v.push_back(j + hsize - 1);
			v.push_back(j + hsize);
		}
		else if (i == hsize - 1) {
			v.push_back((hsize - 2) * hsize + j);
			v.push_back((hsize - 2) * hsize + j + 1);
			v.push_back((hsize - 1) * hsize + j - 1);
			v.push_back((hsize - 1) * hsize + j + 1);
		}
		else if (j == 0) {
			v.push_back((i - 1) * hsize);
			v.push_back((i - 1) * hsize + 1);
			v.push_back(i * hsize + 1);
			v.push_back((i + 1) * hsize);
		}
		else if (j == hsize - 1) {
			v.push_back(i * hsize + j - 1);
			v.push_back((i + 1) * hsize + j - 1);
			v.push_back((i + 1) * hsize + j);
			v.push_back((i - 1) * hsize + j);
		}
		else {
			v.push_back(i * hsize + j + 1);
			v.push_back(i * hsize + j - 1);
			v.push_back((i + 1) * hsize + j - 1);
			v.push_back((i + 1) * hsize + j);
			v.push_back((i - 1) * hsize + j);
			v.push_back((i - 1) * hsize + j + 1);
		}

	}

	bool who_won() {
		for (int i = 0; i < size; i++) {
			if (stones[i] == 1 && (i % hsize == 0)) {
				for (int j = 0; j < size; j++) {
					if (stones[j] == 1 && (j % hsize == hsize - 1)) {
						if (DFS(i, j)) return true;
					}
				}
			}
		}
		return false;
	}

	void DFSUtil(int v, bool visited[])
	{
		if (stones[v] == 1) {
			visited[v] = true;
		}
		std::vector<int>::iterator i;
		for (i = Edges[v].begin(); i != Edges[v].end(); ++i) {
			if(stones[v] == 1)
				if (!visited[*i])
					DFSUtil(*i, visited);
		}
	}

	bool DFS(int startnode, int endnode)
	{
		//printVec(stones);
		//auto start = std::chrono::high_resolution_clock::now();
		bool* visited = new bool[size];
		for (int i = 0; i < size; i++)
			visited[i] = false;

		DFSUtil(startnode, visited);
		//auto stop = std::chrono::high_resolution_clock::now();
		//auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
		//std::cout << "Path finding duration: " << duration.count() << " microseconds" << std::endl;
		if (visited[endnode] == true) {
			//std::cout << "endnode: " << endnode << " connected to " << startnode << std::endl;
			return true;
		}
		delete[] visited;
		//std::cout << "endnode: " << endnode << " not connected to " << startnode << std::endl;
		return false;
	}

};

int main() {

	Graph graph(11);

	graph.stones[12] = 1;
	graph.increase_moves();

	int red;

	for (int i = 0; i < 1; i++) {
		std::cin >> red;
		graph.stones[red] = 2;
		graph.increase_moves();
		graph.next_move();
	}

	return 0;
}