#include <iostream>
using namespace std;

const int ROWS_A = 5;
const int COLS_A = 6;
const int ROWS_B = 5;
const int COLS_B = 6;

void dense_matrix_multiply(int A[ROWS_A][COLS_A], int B[ROWS_B][COLS_B], int C[ROWS_A][COLS_B]) {
    for (int i = 0; i < ROWS_A; ++i) {
        for (int j = 0; j < COLS_B; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < COLS_A; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void display_matrix(int matrix[ROWS_A][COLS_B]) {
    for (int i = 0; i < ROWS_A; ++i) {
        for (int j = 0; j < COLS_B; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int A[ROWS_A][COLS_A] = {
        {0 , 0 , 0 , 0 , 9, 0 },
        {0 , 8 , 0 , 0 , 0, 0 },
        {4 , 0 , 0 , 2 , 0, 0 },
        {0 , 0 , 0 , 0 , 0, 5 },
        {0 , 0 , 2 , 0 , 0, 0 }
    };

    int B[ROWS_B][COLS_B] = {
        {0 , 0 , 0 , 0 , 1, 0 },
        {0 , 5 , 0 , 2 , 0, 0 },
        {0 , 0 , 1 , 0 , 0, 5 },
        {2 , 8 , 0 , 0 , 1, 0 },
        {0 , 0 , 4 , 0 , 0, 0 }
    };

    int C[ROWS_A][COLS_B];

    dense_matrix_multiply(A, B, C);

    cout << "Result of Dense Matrix Multiplication:\n";
    display_matrix(C);

    return 0;
}
