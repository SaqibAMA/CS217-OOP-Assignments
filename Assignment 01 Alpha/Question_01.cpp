#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void allocateTriangular(int*** M, int n) {

    int** mArray = new int*[n];
    for (int i = 0; i < n; i++) {
        *(mArray + i) = new int[n - i + 1];
        *(*(mArray + i) + n - i) = INT_MIN;
    }

    *M = mArray;
}

void deallocate(int** &M, int n) {

    for (int i = 0; i < n; i++)
        delete[] *(M + i);

    delete[] M;
    M = nullptr;

}

bool isTriangular(int** M, int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if(*(*(M + i) + j) != 0)
                return false;
        }
    }

    return true;
}

void inputTriangular(int*** M, int &n) {

    if (n <= 0) {
        cout << "ENTER ORDER OF THE MATRIX -> ";
        cin >> n;

        while (n <= 0) {
            cout << "INVALID VALUE!" << endl;
            cout << "ENTER ORDER OF THE MATRIX -> ";
            cin >> n;
        }
    }

    cout << "\nINPUT THE CONTENTS ROW BY ROW" << endl;

    int** buffM = new int*[n];
    for (int i = 0; i < n; i++)
        *(buffM + i) = new int[n];

    bool isTri = false;

    while (!isTri) {
        for (int i = 0; i < n; i++) {
            cout << "ENTER R" << i + 1 << ": ";
            for (int j = 0; j < n; j++) {
                cin >> *(*(buffM + i) + j);
            }
            cout << endl;
        }
        isTri = isTriangular(buffM, n);
        if(!isTri)
            cout << "NOT TRIANGULAR! INPUT AGAIN!" << endl;
    }

    allocateTriangular(M, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            *(*(*M + i) + j) = *(*(buffM + i) + j + i);
        }
    }

    deallocate(buffM, n);

}

void readFromFile(int*** A, int &aSize, int*** B, int &bSize) {

    ifstream fin;
    fin.open("sampleMatrices.txt");

    int n = 0;
    bool endReading = false;

    bool m1Stored = false, m2Stored = false;

    while (!fin.eof() && !endReading) {

        fin >> n;
        fin.ignore();

        int** buffM = new int*[n];
        for (int i = 0; i < n; i++)
            *(buffM + i) = new int[n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                fin >> *(*(buffM + i) + j);
            }
        }

        if (!isTriangular(buffM, n)) {
            cout << "THE MATRIX READ FROM THE FILE IS\n"
            << "NOT UPPER TRIANGULAR! SOME VALUES WILL BE OMITTED!"
            << endl;
            cout << "Do you want to continue? (y/n)";
            char choice = 'y';
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
                cout << "VALUES STORED!" << endl;
            else
                endReading = true;
        }

        if (!endReading) {

            if(!m1Stored) {
                m1Stored = true;

                aSize = n;

                allocateTriangular(A, n);

                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n - i; j++) {
                        *(*(*A + i) + j) = *(*(buffM + i) + j + i);
                    }
                }
            }
            else if (!m2Stored) {
                m2Stored = true;

                bSize = n;

                allocateTriangular(B, n);

                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n - i; j++) {
                        *(*(*B + i) + j) = *(*(buffM + i) + j + i);
                    }
                }

            }

            deallocate(buffM, n);

        }

    }

    fin.close();

}

void printTriangular(int** M, int n, int mode = 0) {

    cout << "ROW WISE REPRESENTATION: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "R: ";
        int j = 0;
        while (*(M + i) != nullptr && *(*(M + i) + j) != INT_MIN && j < n) {
            cout << setw(5) << *(*(M + i) + j);
            j++;
        }
        cout << endl;
    }

    if (mode != 0) {
        cout << "\nCOLUMN WISE REPRESENTATION: " << endl;
        for (int i = 0; i < n; i++) {
            cout << "C: ";

            for (int j = 0, k = i; j <= n && k >= 0; k--, j++) {
                if (*(*(M + j) + k) != INT_MIN)
                    cout << setw(5) << *(*(M + j) + k);
            }

            cout << endl;
        }
    }

}

void swapRows(int** A, int r1, int r2) {

    int* temp = *(A + r1);
    *(A + r1) = *(A + r2);
    *(A + r2) = temp;

}

int colProduct(const int* A, int** B, int n, int c) {

    int sum = 0;

    for (int i = 0, j = c, k = 0; A[i] != INT_MIN && k <= c && j >= 0; i++, j--, k++) {

        sum += (A[i] * B[k][j]);

    }

    return sum;

}

bool MultiplyMatrices(int** A, int** B, int*** C, int m, int n, int r) {

    if (*C != nullptr || m != n || n != r) {
        cout << "MATRICES CANNOT BE MULTIPLIED!" << endl;
        return false;
    }

    int **prod;
    allocateTriangular(&prod, n);

    for (int i = 0; i < n; i++) {
        for (int j = i, k = 0; j < n; j++, k++) {

            prod[i][k] = colProduct(A[i], B, n, j);

        }
    }

    *C = prod;
    return true;
}

void copyRow(int* &A, int* B, int t = 0) {

    int i = 0;
    while (B[i] != INT_MIN) {
        A[i] = B[i];
        i++;
    }
    A[i] = INT_MIN;
    if (t != 0) {
        A[i - 1] = INT_MIN;
    }

}

void deleteRow(int** &A, int& n, int r) {

    int** newA = new int*[n - 1];
    for (int i = 0, j = 0; i < n; i++) {

        if (i == 0 && i != r) {
            newA[j] = new int[n - i];
            copyRow(newA[j], A[i], -1);
            j++;
        }
        else {
            if (i != r) {
                newA[j] = new int[n - i + 1];
                copyRow(newA[j], A[i]);
                j++;
            }
        }

    }

    for (int i = 0; i < n; i++)
        delete[] A[i];
    delete[] A;

    A = newA;
    n--;
}

int main() {

    int** M = nullptr;
    int n = -1;

    bool mAllocated = false;
    bool mEntered = false;

    int** A = nullptr;
    int aSize = 0;
    int** B = nullptr;
    int bSize = 0;
    int** C = nullptr;
    int cSize = 0;

    bool fMatricesRead = false;
    int choice = -1;

    readFromFile(&A, aSize, &B, bSize);
    deleteRow(A, aSize, 1);

    cout
        << " MENU" << endl
        << " -------------------------------------" << endl
        << "| 1. Allocate memory                  |" << endl
        << "| 2. Deallocate memory                |" << endl
        << "| 3. Input a matrix                   |" << endl
        << "| 4. Read matrices from file          |" << endl
        << "| 5. Print matrix                     |" << endl
        << "| 6. Multiply matrices                |" << endl
        << "| 7. Swap rows                        |" << endl
        << "| 8. Delete row                       |" << endl
        << " -------------------------------------"
        << endl;


    while (choice != 0) {

        cout << "ENTER CHOICE: ";
        cin >> choice;

        if (choice == 1) {

            if (!mAllocated) {
                cout << "Enter order of the matrix you want to allocate: ";
                cin >> n;
                allocateTriangular(&M, n);
                cout << "Memory allocated for a matrix of order " << n << endl;
                mAllocated = true;
            } else {
                cout << "Memory already allocated for a matrix!" << endl;
            }

        } else if (choice == 2) {

            if (mAllocated) {
                mAllocated = false;
                deallocate(M, n);
            } else {
                cout << "No memory has been allocated!" << endl;
            }

        } else if (choice == 3) {

            if (mAllocated) {

                inputTriangular(&M, n);
                mEntered = true;

            } else {
                cout << "No memory has been allocated!" << endl;
            }

        } else if (choice == 4) {

            if (!fMatricesRead) {
                readFromFile(&A, aSize, &B, bSize);
                fMatricesRead = true;
            } else {
                cout << "File matrices have already been stored!" << endl;
            }

        } else if (choice == 5) {

            cout << "1. Print the stored matrix\n"
                 << "2. Print the file matrices" << endl;

            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1 && mEntered) {
                printTriangular(M, n, 1);
            } else if (choice == 2 && fMatricesRead) {
                cout << "A ->" << endl;
                printTriangular(A, aSize, 1);

                cout << "B -> " << endl;
                printTriangular(B, bSize, 1);
            } else {
                cout << "Invalid." << endl;
            }

        } else if (choice == 6) {

            if (!fMatricesRead) {
                cout << "File matrices were not loaded!" << endl;

                cout << "Enter data for matrices below!" << endl;

                cout << "Matrix A -> " << endl;
                inputTriangular(&A, aSize);

                cout << "Matrix B -> " << endl;
                inputTriangular(&B, bSize);

                if(MultiplyMatrices(A, B, &C, aSize, bSize, bSize)) {
                    cout << "The product of the matrices is -> " << endl;
                    cSize = aSize;
                    printTriangular(C, cSize);
                }

            }
            else {

                if (MultiplyMatrices(A, B, &C, aSize, bSize, bSize)) {
                    cout << "The product of the matrices is -> " << endl;
                    cSize = aSize;
                    printTriangular(C, cSize);
                } else {
                    cout << "Either multiplication failed or C was not a nullptr." << endl;
                }

            }

        } else if (choice == 7) {

            if (mEntered) {
                printTriangular(M, n);

                int r1, r2;

                cout << "Enter row : ";
                cin >> r1;
                cout << "Enter row : ";
                cin >> r2;

                swapRows(M, r1, r2);

                cout << "Matrix after swapping -> " << endl;
                printTriangular(M, n);
            }
            else {
                cout << "Matrix has not been entered yet!" << endl;
            }

        }
        else if (choice == 8) {

            if (mEntered) {

                printTriangular(M, n);

                int r;

                cout << "Enter row to delete -> " << endl;
                cin >> r;

                deleteRow(M, n, r);

                cout << "\nMatrix after deletion - >" << endl;
                printTriangular(M, n);

            }
            else {
                cout << "Matrix has not been entered yet!" << endl;
            }

        }
    }

    system("pause");

    return 0;
}