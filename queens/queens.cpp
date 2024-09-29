#include<iostream>
#include<vector>
using namespace std;

void printBoard(vector<vector<int>>& board) {
    int N = board.size();
    for (int i = 0; i < N; i++) {
        cout << '\n';
        for (int j = 0; j < N; j++) {
            cout << board[i][j];
        }
    }
    cout << '\n';
}

bool isAttacked(int x, int y, vector<vector<int>>& board, int N) {
    for (int i = 0; i < N; i++) {
        if ((board[x][i] == 1 && i != y) || (board[i][y] == 1 && i != x)) {
            return true;
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (x + y == i + j && board[i][j] == 1) {
                return true;
            }
            if (i - j == x - y && board[i][j] == 1) {
                return true;
            }
        }
    }
    return false;
}

bool NQueens(vector<vector<int>>& board, int N) {
    int M = board.size();
    if (N == 0) return true;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {

            if (isAttacked(i, j, board, M)) continue;

            board[i][j] = 1;

            if (NQueens(board, N - 1)) return true;

            board[i][j] = 0;
        }
    }
    return false;
}

int main() {

    vector<vector<int>> board;
    int N{ 4 };
    //cin >> N;
    for (int i = 0; i < N; i++) {
        vector<int> row(N, 0);
        board.push_back(row);
    }

    board[0][0] = 0;

    /*for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << "\n" << i << "," << j << endl;
            if (isAttacked(i, j, board, N)) cout << "ATTACKED";
            else cout << "NOT ATTACKED";
        }
    }*/

    /*if (solveNQUtil(board, N)) {
        cout << "YES";
        for (int i = 0; i < N; i++) {
            cout << '\n';
            for (int j = 0; j < N; j++) {
                cout << board[i][j];
            }
        }
    }
    else {
        cout << "NO";
    }*/

    if (NQueens(board, N)) {
        cout << "YES";
        for (int i = 0; i < N; i++) {
            cout << '\n';
            for (int j = 0; j < N; j++) {
                cout << board[i][j];
            }
        }
    }
    else {
        cout << "NO";
    }



    return 0;
}