#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the linked list
struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to push a node to the top of the stack
void push(struct Node** top, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

// Function to pop the top node from the stack
int pop(struct Node** top) {
    if (*top == NULL) {
        printf("Stack underflow\n");
        exit(1);
    }
    struct Node* temp = *top;
    int data = temp->data;
    *top = temp->next;
    free(temp);
    return data;
}

// Function to move a disk from one pole to another
void moveDisk(char from, char to, int disk) {
    printf("Move disk %d from %c to %c\n", disk, from, to);
}

// Function to solve Tower of Hanoi problem using recursion
void towerOfHanoi(int numDisks, struct Node** source, struct Node** aux, struct Node** dest) {
    if (numDisks == 1) {
        int disk = pop(source);
        push(dest, disk);
        moveDisk('A', 'C', disk);
        return;
    }
    towerOfHanoi(numDisks - 1, source, dest, aux);
    int disk = pop(source);
    push(dest, disk);
    moveDisk('A', 'C', disk);
    towerOfHanoi(numDisks - 1, aux, source, dest);
}

int main() {
    int numDisks = 3; // Change the number of disks here
    struct Node* source = NULL;
    struct Node* aux = NULL;
    struct Node* dest = NULL;
    
    // Push disks onto source stack
    for (int i = numDisks; i >= 1; i--)
        push(&source, i);

    // Solve Tower of Hanoi problem
    towerOfHanoi(numDisks, &source, &aux, &dest);
    
    return 0;
}

