#include <iostream>
using namespace std;

// Node structure for the linked list
struct Node {
    int value;
    int row;
    int col;
    Node* next;
};

// Function to create a new node
Node* createNode(int value, int row, int col) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->row = row;
    newNode->col = col;
    newNode->next = nullptr;
    return newNode;
}

// Function to represent sparse matrix using array of linked lists
void representSparseMatrix(int matrix[5][6], Node* sparseMatrix[]) {
    for (int i = 0; i < 5; ++i) {
        sparseMatrix[i] = nullptr;
        for (int j = 0; j < 6; ++j) {
            if (matrix[i][j] != 0) {
                Node* newNode = createNode(matrix[i][j], i, j);
                if (sparseMatrix[i] == nullptr) {
                    sparseMatrix[i] = newNode;
                } else {
                    Node* temp = sparseMatrix[i];
                    while (temp->next != nullptr) {
                        temp = temp->next;
                    }
                    temp->next = newNode;
                }
            }
        }
    }
}

// Function to display the sparse matrix represented using linked lists
void displaySparseMatrix(Node* sparseMatrix[]) {
    for (int i = 0; i < 5; ++i) {
        Node* temp = sparseMatrix[i];
        while (temp != nullptr) {
            cout << "(" << temp->row << ", " << temp->col << ", " << temp->value << ") ";
            temp = temp->next;
        }
        cout << endl;
    }
}

int main() {
    // Sparse matrices A and B
    int A[5][6] = {
        {0, 0, 0, 0, 9, 0},
        {0, 8, 0, 0, 0, 0},
        {4, 0, 0, 2, 0, 0},
        {0, 0, 0, 0, 0, 5},
        {0, 0, 2, 0, 0, 0}
    };
    int B[5][6] = {
        {0, 0, 0, 0, 1, 0},
        {0, 5, 0, 2, 0, 0},
        {0, 0, 1, 0, 0, 5},
        {2, 8, 0, 0, 1, 0},
        {0, 0, 4, 0, 0, 0}
    };

    // Arrays of linked lists to represent sparse matrices A and B
    Node* sparseMatrixA[5];
    Node* sparseMatrixB[5];

    // Represent sparse matrices A and B using linked lists
    representSparseMatrix(A, sparseMatrixA);
    representSparseMatrix(B, sparseMatrixB);

    // Display sparse matrices A and B
    cout << "Sparse Matrix A:" << endl;
    displaySparseMatrix(sparseMatrixA);
    cout << endl;
    cout << "Sparse Matrix B:" << endl;
    displaySparseMatrix(sparseMatrixB);

    return 0;
}
