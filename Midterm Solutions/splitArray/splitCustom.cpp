#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Function to print the array
void printArray(int** A, int n, bool isTerminated = true) {

    if (A != nullptr) {
        for (int i = 0; i < n && A[i][0] != INT_MIN; i++) {
            if (isTerminated) {
                for (int j = 0; A[i][j] != INT_MIN; j++) {
                    cout << setw(3) << A[i][j] << " ";
                }
            } else {
                for (int j = 0; j < n; j++) {
                    cout << setw(3) << A[i][j] << " ";
                }
            }
            cout << endl;
        }
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
void append(int* &A, int s, int n) {

    int* newA = new int[s + 1];

    for (int i = 0; i < s; i++) {
        newA[i] = A[i];
    }
    newA[s - 1] = n;
    newA[s] = INT_MIN;

    delete[] A;
    A = newA;

}

// Function to add row
void addRow(int** &A, int n) {

    int** newA = new int*[n + 1];
    int i;
    for (i = 0; i < n; i++) {

        int j;
        for (j = 0; A[i][j] != INT_MIN; j++);

        newA[i] = new int[j + 1];

        for (int k = 0; k <= j; k++) {
            newA[i][k] = A[i][k];
        }
        newA[i][j] = INT_MIN;

    }
    newA[i] = new int(INT_MIN);


    deallocateArray(A, n);
    A = newA;

}

// Split Array function
void splitArray(int** A, int n, int** &P, int &pSize, int** &nP, int &nPSize) {

    int Pi = 0, Pj = 1;
    int nPi = 0, nPj = 1;

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if (isPrime(A[i][j])) {

                if (Pj == 1) {
                    addRow(P, Pi);
                    Pi++;
                }

                append(P[Pi - 1], Pj, A[i][j]);
                Pj++;

            } else {

                if (nPj == 1) {
                    addRow(nP, nPi);
                    nPi++;
                }

                append(nP[nPi - 1], nPj, A[i][j]);
                nPj++;

            }

        }

        Pj = 1, nPj = 1;

    }

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

    cout << "Original Matrix->" << endl;
    printArray(Arr, n, false);
    cout << endl;

    int** P = nullptr;  // Primes
    int** nP = nullptr;	// Not Primes

    int pSize = 0;		// Prime array size
    int nPSize = 0;		// Non-Prime Array Size

    splitArray(Arr, n, P, pSize, nP, nPSize);

    cout << "Primes->" << endl;
    printArray(P, pSize);

    cout << "\nNon-Primes->" << endl;
    printArray(nP, nPSize);

    deallocateArray(Arr, n);
    deallocateArray(P, pSize);


    return 0;
}