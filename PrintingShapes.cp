#include <iostream>
using namespace std;

void printTriangle(int n);
void printOppositeTriangle(int n);
void printRuler(int n);

int main() {

    int n;
    cout << "Enter a positive integer: " << endl;
    cin >> n;

    cout << "First triangle" << endl;
    printTriangle(n);

    cout << "Second triangle" << endl;
    printOppositeTriangle(n);

    cout << "Ruler" << endl;
    printRuler(n);

}

void printTriangle(int n) {

   if (n - 1 > 0) {

       printTriangle(n-1);
   }

   for (int i = 0; i < n; i++) {
            cout << '*';
        }
        cout << endl;
}

void printOppositeTriangle(int n) {

    for (int i = 0; i < n; i++) {
        cout << "*";
    }
    cout << endl;

    if (n-1 > 0) {
        printOppositeTriangle(n-1);
    }
    for (int i = 0; i< n; i++) {
        cout << "*";
    }
    cout << endl;

}

void printRuler(int n) {

    if (n-1 > 0) {
        printRuler(n-1);
    }
    for (int i = 0; i < n; i++) {
        cout << "-";
    }
    cout << endl;
    if (n-1 > 0) {
        printRuler(n-1);
    }
}

