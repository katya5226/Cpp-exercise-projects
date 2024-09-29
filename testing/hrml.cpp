/*#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


int main() {
    int num_lines{ 0 };
    int num_queries{ 0 };

    cin >> num_lines >> num_queries;
    cin.ignore();

    unsigned pos;
    unsigned first;
    unsigned middle;
    unsigned start_pos;
    unsigned end_pos;
    unsigned len;

    //struct tag {
    //    string tagname;
    //    int level;
    //};

    string line;
    string tag;
    vector<string> lines;
    vector<string> tags;

    string query_tagname;
    string query_value;

    string result;

    while (num_lines--) {
        getline(cin, line);
        lines.push_back(line);
        start_pos = line.find('<');
        end_pos = line.find_first_of(' ');
        len = end_pos - start_pos;
        tag = line.substr(start_pos, len);
        tags.push_back(tag);
    }


    while (num_queries--) {
        result = "";
        getline(cin, line);
        line.find_last_of('.') != string::npos ? first = line.find_last_of('.') + 1 : first = 0;
        middle = line.find('~');
        query_tagname = '<' + line.substr(first, middle - first);

        query_value = line.substr(middle + 1);

        for (string s : lines) {
            if (s.find(query_tagname) != string::npos && s.find(query_value) != string::npos) {
                start_pos = s.find(query_value) + query_value.length() + 4;
                end_pos = s.find_first_of('"', start_pos + 1);
                len = end_pos - start_pos;
                result = s.substr(start_pos, len);
                cout << result << endl;
            }
        }
        if (result == "") cout << "Not Found!" << endl;
    }
    return 0;
}*/