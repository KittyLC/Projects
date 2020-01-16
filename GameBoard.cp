#include <iostream>
using namespace std;

int jumpCol(int gameBoard[], int n, int highidx);

int main() {

    int gameBoard[] = {0, 3, 80, 6, 57, 10};
    int lowestCost = jumpCol(gameBoard, 0, 5);

    for (int i = 0; i<=5; i++) {

        cout << gameBoard[i] << endl;
    }

    cout << "Lowest cost: " << lowestCost << endl;

    return 0;
}

int jumpCol(int gameBoard[], int n, int highidx) {
    if (highidx == n)
        return gameBoard[n];
    else if (highidx-1 == n)
        return gameBoard[0] + gameBoard[highidx];
    else if (jumpCol(gameBoard, n+1, highidx) < jumpCol(gameBoard, n+2, highidx))
        return gameBoard[n] + jumpCol(gameBoard, n+1, highidx);
    else
        return gameBoard[n] + jumpCol(gameBoard, n+2, highidx);
}

