#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure for a node in the binary tree
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Create a new node
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Binary Tree implemented using linked data structure
struct BinaryTree {
    struct TreeNode* root;
};

// Initialize binary tree
struct BinaryTree* createBinaryTree() {
    struct BinaryTree* tree = (struct BinaryTree*)malloc(sizeof(struct BinaryTree));
    if (tree == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    tree->root = NULL;
    return tree;
}

// Insertion operation for binary tree using linked data structure
void insert(struct BinaryTree* tree, int data) {
    if (tree->root == NULL) {
        tree->root = createNode(data);
        return;
    }

    struct TreeNode* current = tree->root;
    struct TreeNode* parent = NULL;
    while (current != NULL) {
        parent = current;
        if (data <= current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (data <= parent->data)
        parent->left = createNode(data);
    else
        parent->right = createNode(data);
}

// Function to find the deepest node in the tree
struct TreeNode* findDeepestNode(struct TreeNode* root) {
    struct TreeNode* temp = root;
    while (temp->right != NULL) {
        temp = temp->right;
    }
    return temp;
}

// Deletion operation for binary tree using linked data structure
void deleteNode(struct BinaryTree* tree, int key) {
    if (tree->root == NULL) {
        printf("Tree is empty!\n");
        return;
    }

    struct TreeNode *current = tree->root, *parent = NULL;
    while (current != NULL && current->data != key) {
        parent = current;
        if (key < current->data)
            current = current->left;
        else
            current = current->right;
    }

    if (current == NULL) {
        printf("Key not found in the tree!\n");
        return;
    }

    struct TreeNode* deepestNode = findDeepestNode(tree->root);

    // If the node to be deleted is the deepest node
    if (current == deepestNode) {
        // If the root itself is the only node in the tree
        if (parent == NULL) {
            free(tree->root);
            tree->root = NULL;
            return;
        }

        // Find the parent of the deepest node
        struct TreeNode* deepestParent = NULL;
        struct TreeNode* temp = tree->root;
        while (temp->right != deepestNode) {
            deepestParent = temp;
            temp = temp->right;
        }

        // Update parent pointers
        if (deepestParent != NULL)
            deepestParent->right = NULL;

        // Copy the data of deepest node to the node to be deleted
        current->data = deepestNode->data;

        free(deepestNode);
        return;
    }

    // If the node to be deleted is not the deepest node
    // Replace the node to be deleted with the deepest rightmost node
    if (current == tree->root) {
        tree->root->data = deepestNode->data;
    } else if (parent->left == current) {
        parent->left->data = deepestNode->data;
    } else {
        parent->right->data = deepestNode->data;
    }

    // Find the parent of the deepest node
    struct TreeNode* deepestParent = NULL;
    struct TreeNode* temp = tree->root;
    while (temp->right != deepestNode) {
        deepestParent = temp;
        temp = temp->right;
    }

    // Update parent pointers
    if (deepestParent != NULL)
        deepestParent->right = NULL;

    free(deepestNode);
}

// In-order traversal of binary tree
void inorderTraversal(struct TreeNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

int main() {
    // Creating binary tree using linked data structure
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
    inorderTraversal(tree->root);
    printf("\n");

    // Deleting a node
    deleteNode(tree, 50);

    printf("In-order traversal after deletion: ");
    inorderTraversal(tree->root);
    printf("\n");

    return 0;
}

