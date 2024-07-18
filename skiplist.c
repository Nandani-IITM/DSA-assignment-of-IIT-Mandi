#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Maximum level for the skip list
#define MAX_LEVEL 6

// Node structure for skip list
typedef struct Node {
    int key;
    struct Node **forward;
} Node;

// Skip list structure
typedef struct SkipList {
    int level;
    Node *header;
} SkipList;

// Function to create a new node
Node* createNode(int key, int level) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->forward = (Node**)malloc(sizeof(Node*) * (level + 1));
    return newNode;
}

// Function to create a new skip list
SkipList* createSkipList() {
    SkipList* list = (SkipList*)malloc(sizeof(SkipList));
    list->level = 0;
    list->header = createNode(-1, MAX_LEVEL);
    for (int i = 0; i <= MAX_LEVEL; i++)
        list->header->forward[i] = NULL;
    return list;
}

// Function to generate random level for a node
int randomLevel() {
    int level = 0;
    while (rand() % 2)
        level++;
    return level > MAX_LEVEL ? MAX_LEVEL : level;
}

// Function to insert a key into the skip list
void insert(SkipList* list, int key) {
    Node* current = list->header;
    Node* update[MAX_LEVEL + 1];
    for (int i = 0; i <= MAX_LEVEL; i++)
        update[i] = NULL;
    
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key)
            current = current->forward[i];
        update[i] = current;
    }
    
    current = current->forward[0];
    
    if (current == NULL || current->key != key) {
        int newLevel = randomLevel();
        if (newLevel > list->level) {
            for (int i = list->level + 1; i <= newLevel; i++)
                update[i] = list->header;
            list->level = newLevel;
        }
        
        Node* newNode = createNode(key, newLevel);
        for (int i = 0; i <= newLevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// Function to search for a key in the skip list
bool search(SkipList* list, int key, int* comparisons) {
    Node* current = list->header;
    for (int i = list->level; i >= 0; i--) {
        while (current->forward[i] != NULL && current->forward[i]->key < key) {
            current = current->forward[i];
            (*comparisons)++;
        }
        (*comparisons)++;
    }
    current = current->forward[0];
    if (current != NULL && current->key == key)
        return true;
    return false;
}

// Function to print the skip list
void printSkipList(SkipList* list) {
    printf("Skip List:\n");
    for (int i = 0; i <= list->level; i++) {
        Node* node = list->header->forward[i];
        printf("Level %d: ", i);
        while (node != NULL) {
            printf("%d ", node->key);
            node = node->forward[i];
        }
        printf("\n");
    }
}

int main() {
    // Initialize random number generator
    srand(time(NULL));

    // Create a skip list
    SkipList* list = createSkipList();

    // Insert some keys
    insert(list, 3);
    insert(list, 6);
    insert(list, 9);
    insert(list, 12);
    insert(list, 15);
    
    // Print the skip list
    printSkipList(list);
    
    // Search for a key
    int key = 9;
    int comparisons = 0;
    if (search(list, key, &comparisons))
        printf("\n%d found in skip list with %d comparisons.\n", key, comparisons);
    else
        printf("\n%d not found in skip list with %d comparisons.\n", key, comparisons);

    return 0;
}

