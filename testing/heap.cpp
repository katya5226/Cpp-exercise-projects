/*#include<iostream>
#include<vector>
#include<string>
#include <algorithm>

using namespace std;

int main() {

    int q;
    int x;
    long v;
    int index;
    long min = LONG_MAX;
    vector<long>::iterator it;
    vector<long> vec;

    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> x;
        switch (x) {
        case 1:
            cin >> v;
            if (v < min) min = v;
            vec.push_back(v);
            break;
        case 2:
            cin >> v;
            vec.erase(remove(vec.begin(), vec.end(), v), vec.end());
            if (v == min) {
                if (vec.size() > 0) {
                    sort(vec.begin(), vec.end());
                    min = vec[0];
                }
                else min = LONG_MAX;
            }
            break;
        case 3:
            if (vec.size() > 0)
                cout << min << endl;
            break;
        default:
            break;
        }
    }

    return 0;
}*/