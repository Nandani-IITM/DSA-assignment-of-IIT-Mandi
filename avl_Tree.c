#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// AVL Tree Node
struct AVLNode {
    int data;
    struct AVLNode* left;
    struct AVLNode* right;
    int height;
};

// Function to get height of node
int height(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Create a new AVL node
struct AVLNode* createNode(int data) {
    struct AVLNode* newNode = (struct AVLNode*)malloc(sizeof(struct AVLNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// Right rotate subtree rooted with y
struct AVLNode* rightRotate(struct AVLNode* y) {
    struct AVLNode* x = y->left;
    struct AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate subtree rooted with x
struct AVLNode* leftRotate(struct AVLNode* x) {
    struct AVLNode* y = x->right;
    struct AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get balance factor of node
int getBalance(struct AVLNode* node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Recursive function to insert a key in the subtree rooted with node
struct AVLNode* insert(struct AVLNode* node, int key) {
    // Perform normal BST insertion
    if (node == NULL)
        return createNode(key);

    if (key < node->data)
        node->left = insert(node->left, key);
    else if (key > node->data)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in AVL
        return node;

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are four cases
    // Left Left Case
    if (balance > 1 && key < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Function to perform in-order traversal of AVL tree
void inorderTraversal(struct AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Function to delete an AVL tree
void deleteTree(struct AVLNode* root) {
    if (root != NULL) {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
    }
}

// Function to generate a random permutation of [1...n]
int* generateRandomPermutation(int n) {
    int* permutation = (int*)malloc(n * sizeof(int));
    if (permutation == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    // Initialize permutation array with values 1 to n
    for (int i = 0; i < n; i++) {
        permutation[i] = i + 1;
    }

    // Shuffle the permutation array using Fisher-Yates algorithm
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = permutation[i];
        permutation[i] = permutation[j];
        permutation[j] = temp;
    }

    return permutation;
}

// Function to perform insertion sort
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    // Start with a small value of n and keep increasing until AVL tree-based sorting is faster than insertion sort
    int n = 100;
    double avlTime, insertionTime;
    clock_t start, end;

    do {
        int* permutation = generateRandomPermutation(n);

        // AVL Tree-based sorting
        struct AVLNode* root = NULL;
        start = clock();
        for (int i = 0; i < n; i++) {
            root = insert(root, permutation[i]);
        }
        avlTime = (double)(clock() - start) / CLOCKS_PER_SEC;

        // In-order traversal of AVL tree to get sorted sequence
        start = clock();
        inorderTraversal(root);
        end = clock();
        avlTime += (double)(end - start) / CLOCKS_PER_SEC;

        // Insertion sort
        int* arr = (int*)malloc(n * sizeof(int));
        for (int i = 0; i < n; i++) {
            arr[i] = permutation[i];
        }
        start = clock();
        insertionSort(arr, n);
        insertionTime = (double)(clock() - start) / CLOCKS_PER_SEC;

        free(permutation);
        deleteTree(root);
        free(arr);

        n *= 2; // Double the value of n for next iteration
    } while (avlTime > insertionTime);

    printf("Smallest n_0 for which AVL tree-based sorting is faster than insertion sort: %d\n", n / 2);

    return 0;
}

