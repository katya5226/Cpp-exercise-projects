#include <iostream>
#include <string>
using namespace std;
int main()
{
    string sentence1, sentence2, words[10];
    int pos = 0, old_pos = 0, nwords, i = 0;
    sentence1 = "Eskimos have 23 ways to ";
    sentence1 += "describe snow";
    while (pos < sentence1.size()) {
        pos = sentence1.find(' ', old_pos);
        words[i++].assign(sentence1, old_pos, pos - old_pos);
        old_pos = pos + 1;
    }
    nwords = i;
    cout << sentence1 << endl;
    sentence2 = "C++ programmers ";
    for (i = 1; i < nwords - 1; ++i)
        sentence2 += words[i] + ' ';
    sentence2 += "windows";
    cout << sentence2 << endl;
}