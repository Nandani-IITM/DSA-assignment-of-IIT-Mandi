#include <iostream>
using namespace std;

// Structure for a node in the linked list representing a non-zero element
struct Node {
    int value;
    int col;
    Node* next;
};

// Function to create a new node
Node* createNode(int value, int col) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->col = col;
    newNode->next = nullptr;
    return newNode;
}

// Function to populate the linked list representing a sparse matrix
void populateLinkedList(int matrix[][6], Node* sparseMatrix[]) {
    for (int i = 0; i < 5; ++i) {
        sparseMatrix[i] = nullptr;
        for (int j = 0; j < 6; ++j) {
            if (matrix[i][j] != 0) {
                Node* newNode = createNode(matrix[i][j], j);
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

// Function to perform matrix multiplication using linked list representations
Node** matrixMultiply(Node* matrixA[], Node* matrixB[]) {
    // Initialize result matrix as an array of linked lists
    Node** resultMatrix = new Node*[5]();

    // Perform matrix multiplication
    for (int i = 0; i < 5; ++i) {
        for (Node* nodeA = matrixA[i]; nodeA != nullptr; nodeA = nodeA->next) {
            int colA = nodeA->col;
            int valueA = nodeA->value;

            for (Node* nodeB = matrixB[colA]; nodeB != nullptr; nodeB = nodeB->next) {
                int colB = nodeB->col;
                int valueB = nodeB->value;
                int newValue = valueA * valueB;

                // Add the product to the corresponding position in the result matrix
                if (resultMatrix[i] == nullptr) {
                    resultMatrix[i] = createNode(newValue, colB);
                } else {
                    Node* temp = resultMatrix[i];
                    while (temp->next != nullptr) {
                        temp = temp->next;
                    }
                    temp->next = createNode(newValue, colB);
                }
            }
        }
    }

    return resultMatrix;
}

// Function to display the result matrix
void displayResultMatrix(Node** resultMatrix) {
    cout << "Result Matrix:" << endl;
    for (int i = 0; i < 5; ++i) {
        Node* temp = resultMatrix[i];
        while (temp != nullptr) {
            cout << "(" << i << ", " << temp->col << ", " << temp->value << ") ";
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

    // Sparse matrices represented as linked lists
    Node* sparseMatrixA[5];
    Node* sparseMatrixB[6];

    // Populate linked lists for matrices A and B
    populateLinkedList(A, sparseMatrixA);
    populateLinkedList(B, sparseMatrixB);

    // Perform matrix multiplication
    Node** resultMatrix = matrixMultiply(sparseMatrixA, sparseMatrixB);

    // Display the result matrix
    displayResultMatrix(resultMatrix);

    return 0;
}
