#include <iostream>
#include <fstream>

using namespace std;

void allocateTriangular(int** &M, int n) {

    M = new int*[n];
    for (int i = 0; i < n; i++)
        *(M + i) = new int[n - i];

}

void deallocate(int** &M, int n) {

    for (int i = 0; i < n; i++)
        delete[] *(M + i);

    delete[] M;
    M = nullptr;

}

void inputMatrix(int** &M, int &n) {

    cout << "ENTER THE ORDER -> ";
    cin >> n;

    while (n <= 0) {
        cout << "INVALID INPUT!" << endl;
        cout << "ENTER THE ORDER -> ";
        cin >> n;
    }

    allocateTriangular(M, n);

    for (int i = 0; i < n; i++){
        cout << "Enter " << n - i << " entries: ";
        for (int j = 0; j < n - i; j++) {
            cin >> *(*(M + i) + j);
        }
        cout << endl;
    }

}

int main() {

    int** M = nullptr;
    int n;

    inputMatrix(M, n);
    deallocate(M, n);

    return 0;
}