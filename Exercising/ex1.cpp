#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

template <class T>
T sum(T arr[], int n) {
	T s = 0;
	for (int i = 0; i < n; i++) {
		s += arr[i];
	}
	return s;
}


int main() {

    vector<string> history = { "456" };
    string el;

    int n = history.size();
    //std::cout << n << "\n";
    vector<vector<int>> his;
    his.resize(n);
    int num;
    int totalStops = 0;
    vector<int>::iterator it;
    for (int i = 0; i < n; i++) {
        el = history[i];
        //cout << el << "\n";
        for (int j = 0; j < 3; j++) {
            num = el[j] - 48;
            //std::cout << el[j] << "\t";
            his[i].push_back(num);
            //std::cout << his[i][j] << "\t";
        }
        //std::cout << "\n";
    }
    

        for (int i = 0; i < his.size(); i++) {
            int max = 0;
            for (int k = 0; k < 3; k++) {
                it = max_element(his[i].begin(), his[i].end());
                if (*it > max) max = *it;
                his[i].erase(it);
        }
        totalStops += max;
    }

    std::cout << totalStops;

	return 0;
}