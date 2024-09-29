#include <iostream>
#include <vector>
#include <string>
using namespace std;


int main() {
    string sName = "QivcjGDoqoZKuiDcFHqRBdtuPRrisYZoSyQuERxvPiYZNfbWTZHqwLiCeebfYSAgSZiOc";
    int m = sName.length();
    vector<vector<char>> seqs;
    string jour = "OAAeqEXEmijuQqDEDYBlklSWURxcLxHlFBYuWSWMYHWJVHXigdjohAundoufZ";
    int n = jour.length();

        int L[69 + 1][61 + 1];
        int i, j;

        for (i = 0; i <= m; i++) {
            for (j = 0; j <= n; j++) {
                if (i == 0 || j == 0)
                    L[i][j] = 0;

                else if (sName.at(i - 1) == jour.at(j - 1))
                    L[i][j] = L[i - 1][j - 1] + 1;

                else
                    L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];

            }
        }

        cout << L[m][n];


    return 0;
}


