/*#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<int> parseInts(string str) {
    vector<int> v;
    stringstream ss(str);
    char ch = ',';
    int n = count(str.begin(), str.end(), ch);
    int x;

    ss >> x;
    v.push_back(x);
    for (int i = 0; i < n; i++) {
        ss >> ch >> x;
        v.push_back(x);
    }
    return v;
}

int main() {
    string str;
    cin >> str;
    vector<int> integers = parseInts(str);
    for (int i = 0; i < integers.size(); i++) {
        cout << integers[i] << "\n";
    }

    return 0;
}*/
