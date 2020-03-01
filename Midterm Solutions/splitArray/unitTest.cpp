#include <iostream>
#include <iomanip>

using namespace std;

void printArray(int** A, int n) {

    for (int i = 0; i < n; i++) {

        int j = 0;

        while (j < n && A[i][j] != INT_MIN) {
            cout << setw(5) << A[i][j];
            j++;
        }

        cout << endl;
    }

}

void deallocateArray(int** &A, int n) {

    for (int i = 0; i < n; i++)
        delete[] A[i];

    delete [] A;
    A = nullptr;

}

void addRow(int** &A, int &s) {

    int** newA = new int*[s + 1];
    int i;
    for (i = 0; i < s; i++) {

        int j = 0;
        for (j = 0; A[i][j] != INT_MIN && j < s; j++);

        newA[i] = new int[j];

        for (int k = 0; k <= j; k++)
            newA[i][k] = A[i][k];

    }
    newA[i] = new int(INT_MIN);

    deallocateArray(A, s);
    A = newA;
    s++;

}

int main(){

    int n = 5;
    int** A = new int*[n];
    for (int i = 0; i < n; i++) {
        A[i] = new int[n + 1];
        for (int j = 0; j < n + 1; j++) {
            A[i][j] = 3*j;
            if (j == n)
                A[i][j] = INT_MIN;
        }
    }

    printArray(A, n);
    addRow(A, n);

    cout << "\n\n Mod 2: " << endl;
    printArray(A, n);
    addRow(A, n);

    cout << "\n\n Mod 3: " << endl;

    printArray(A, n);
    addRow(A, n);


    return 0;
}