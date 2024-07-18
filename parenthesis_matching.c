#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a structure for a node in the linked list
struct Node {
    char data;
    struct Node* next;
};

// Function to create a new node
struct Node* newNode(char data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to push a node to the top of the stack
void push(struct Node** top, char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

// Function to pop the top node from the stack
char pop(struct Node** top) {
    if (*top == NULL) {
        printf("Stack underflow\n");
        exit(1);
    }
    struct Node* temp = *top;
    char data = temp->data;
    *top = temp->next;
    free(temp);
    return data;
}

// Function to check if parenthesis are matching
bool isMatching(char exp[]) {
    struct Node* stack = NULL;
    int i = 0;
    while (exp[i]) {
        if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{') {
            push(&stack, exp[i]);
        } else if (exp[i] == ')' || exp[i] == ']' || exp[i] == '}') {
            if (stack == NULL) {
                return false; // More closing brackets than opening brackets
            }
            char topChar = pop(&stack);
            if ((exp[i] == ')' && topChar != '(') ||
                (exp[i] == ']' && topChar != '[') ||
                (exp[i] == '}' && topChar != '{')) {
                return false; // Mismatched brackets
            }
        }
        i++;
    }
    return stack == NULL; // Check if stack is empty after processing all characters
}

int main() {
    char expr[100];
    printf("Enter the expression: ");
    fgets(expr, sizeof(expr), stdin);
    
    if (isMatching(expr)) {
        printf("Parentheses are balanced\n");
    } else {
        printf("Parentheses are not balanced\n");
    }
    
    return 0;
}

