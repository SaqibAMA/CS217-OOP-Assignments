#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

// Printing function

void printArray(int** A, int n) {

    for (int i = 0; i < n; i++) {

        int j = 0;

        while (A[i][j] != INT_MIN && j < n) {
            cout << setw(5) << A[i][j] << " ";
            j++;
        }

        cout << endl;
    }

}

// Prime checker function

bool isPrime(int n) {

    if (n <= 2) {
        return (n == 2);
    }
    else {

        for (int i = 2; i <= n / 2; i++) {
            if (n % i == 0) return false;
        }

    }

    return true;

}

// Deallocation function

void deallocateArray(int** &A, int n) {

    for (int i = 0; i < n; i++)
        delete[] A[i];

    delete [] A;
    A = nullptr;

}

// Append function

void append(int n, int s, int* &A) {

    int* newA = new int[s + 1];

    int i;
    for (i = 0; i < s; i++)
        newA[i] = A[i];
    newA[i] = n;
    i++;
    newA[i] = INT_MIN;

    A = newA;

}

// Function to add a new row

void addRow(int** &A, int &s) {

    int** newA = new int*[s + 1];
    int i;
    for (i = 0; i < s; i++) {

        int j = 0;
        for (j = 0; A[i][j] != INT_MIN && j < s; j++);

        newA[i] = new int[j];

        for (int k = 0; k <= j; k++) {
            newA[i][k] = A[i][k];
        }

    }
    newA[i] = new int;

    deallocateArray(A, s);
    A = newA;

}


// Split array function

void splitArr(int** A, int n, int** &P, int &pSize, int** &nP, int &nPSize) {

    int nPi = 0, nPj = 0;
    int Pi = 0, Pj = 0;

    for (int i = 0; i < n; i++) {

        Pj = 0, nPj = 0;

        for (int j = 0; j < n; j++) {

            if (isPrime(A[i][j])) {

                if (Pj == 0) {
                    addRow(P, Pi);
                    Pi++;
                }
                append(A[i][j], Pj, P[Pi - 1]);
                Pj++;

                static int round = 1;
                cout << "round " << round++ << endl;
                for (int l = 0; l < Pj; l++) {
                    cout << setw(3) << P[Pi - 1][Pj] << ", ";
                }
                cout << endl;

            }

        }

    }

    /*int nPi = 0, nPj = 0;
    int Pi = 0, Pj = 0;

    for (int i = 0; i < n; i++) {

        Pj = 0, nPj = 0;

        for (int j = 0; j < n; j++) {

            if (isPrime(A[i][j])) {
                if (Pj == 0) {
                    //cout << "Row Added! " << endl;
                    addRow(P, Pi);
                    Pi++;
                }
                append(A[i][j], Pj, P[Pi - 1]);
                Pj++;
            } else {

                if (nPj == 0) {
                    //cout << "Row Added! " << endl;
                    addRow(nP, nPi);
                    nPi++;
                }
                append(A[i][j], nPj, nP[nPi - 1]);
                //cout << "npInd: " << nP[nPi - 1][nPj] << endl;
                nPj++;

            }

        }

    }*/

    pSize = Pi;
    nPSize = nPi;

}

int main(){

    int** Arr = nullptr;
    int n;

    // Reading matrix from a file

    ifstream fin;
    fin.open("array.txt");

    // Getting rows

    fin >> n;
    fin.ignore();

    Arr = new int*[n];
    for (int i = 0; i < n; i++)
        Arr[i] = new int[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){

            fin >> Arr[i][j];

        }
    }

    fin.close();


    int** P = nullptr;	// Primes
    int** nP = nullptr;	// Not Primes

    int pSize = 0;		// Prime array size
    int nPSize = 0;		// Non-Prime Array Size


    splitArr(Arr, n, P, pSize, nP, nPSize);

    printArray(P, pSize);

    /*cout << "nP ->" << endl;
    printArray(nP, nPSize);*/

    // Deallocation calls
    deallocateArray(Arr, n);
    deallocateArray(P, pSize);
    deallocateArray(nP, nPSize);

    return 0;
}