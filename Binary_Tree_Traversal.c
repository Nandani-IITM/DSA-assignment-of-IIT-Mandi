#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

// Structure for a binary tree
struct BinaryTree {
    int nodes[MAX_NODES];
    int size;
};

// Initialize binary tree
struct BinaryTree* createBinaryTree() {
    struct BinaryTree* tree = (struct BinaryTree*)malloc(sizeof(struct BinaryTree));
    if (tree == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    tree->size = 0;
    return tree;
}

// Insertion operation for binary tree using array
void insert(struct BinaryTree* tree, int data) {
    if (tree->size >= MAX_NODES) {
        printf("Tree is full!\n");
        return;
    }
    tree->nodes[tree->size++] = data;
}

// Deletion operation for binary tree using array
void deleteNode(struct BinaryTree* tree, int key) {
    int i;
    for (i = 0; i < tree->size; i++) {
        if (tree->nodes[i] == key) {
            break;
        }
    }
    if (i == tree->size) {
        printf("Key not found in the tree!\n");
        return;
    }

    // Replace the node to be deleted with the last node
    tree->nodes[i] = tree->nodes[tree->size - 1];
    tree->size--;
}

// In-order traversal of binary tree
void inorderTraversal(struct BinaryTree* tree, int rootIndex) {
    if (rootIndex < tree->size) {
        inorderTraversal(tree, 2 * rootIndex + 1); // Traverse left subtree
        printf("%d ", tree->nodes[rootIndex]);    // Print current node
        inorderTraversal(tree, 2 * rootIndex + 2); // Traverse right subtree
    }
}

int main() {
    // Creating binary tree using array
    struct BinaryTree* tree = createBinaryTree();

    // Inserting elements
    insert(tree, 50);
    insert(tree, 30);
    insert(tree, 70);
    insert(tree, 20);
    insert(tree, 40);
    insert(tree, 60);
    insert(tree, 80);

    printf("In-order traversal before deletion: ");
    inorderTraversal(tree, 0); // Start traversal from the root
    printf("\n");

    // Deleting a node
    deleteNode(tree, 50);

    printf("In-order traversal after deletion: ");
    inorderTraversal(tree, 0); // Start traversal from the root
    printf("\n");

    free(tree);

    return 0;
}

