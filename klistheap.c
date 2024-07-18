#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Define a structure to represent a node in the heap
typedef struct {
    int value;  // The value of the node
    int listIndex;  // The index of the list from which the node belongs
    int nextIndex;  // The next index to consider in the list
} HeapNode;

// Define a structure for the heap
typedef struct {
    HeapNode heapArray[MAX_SIZE];  // Array to store heap nodes
    int heapSize;  // Current size of the heap
} MinHeap;

// Function to initialize the heap
MinHeap* createMinHeap() {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->heapSize = 0;
    return minHeap;
}

// Function to swap two heap nodes
void swapNodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify a subtree rooted at index i
void heapify(MinHeap* minHeap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minHeap->heapSize && minHeap->heapArray[left].value < minHeap->heapArray[smallest].value)
        smallest = left;

    if (right < minHeap->heapSize && minHeap->heapArray[right].value < minHeap->heapArray[smallest].value)
        smallest = right;

    if (smallest != index) {
        swapNodes(&(minHeap->heapArray[index]), &(minHeap->heapArray[smallest]));
        heapify(minHeap, smallest);
    }
}

// Function to insert a new node into the heap
void insertNode(MinHeap* minHeap, HeapNode newNode) {
    if (minHeap->heapSize == MAX_SIZE) {
        printf("Overflow: Could not insert into heap\n");
        return;
    }

    minHeap->heapSize++;
    int i = minHeap->heapSize - 1;
    minHeap->heapArray[i] = newNode;

    while (i != 0 && minHeap->heapArray[(i - 1) / 2].value > minHeap->heapArray[i].value) {
        swapNodes(&(minHeap->heapArray[i]), &(minHeap->heapArray[(i - 1) / 2]));
        i = (i - 1) / 2;
    }
}

// Function to extract the minimum node from the heap
HeapNode extractMin(MinHeap* minHeap) {
    if (minHeap->heapSize <= 0) {
        printf("Underflow: Could not extract from heap\n");
        HeapNode emptyNode = {0, 0, 0}; // Return an empty node
        return emptyNode;
    }

    if (minHeap->heapSize == 1) {
        minHeap->heapSize--;
        return minHeap->heapArray[0];
    }

    HeapNode root = minHeap->heapArray[0];
    minHeap->heapArray[0] = minHeap->heapArray[minHeap->heapSize - 1];
    minHeap->heapSize--;
    heapify(minHeap, 0);

    return root;
}

// Function to merge k sorted lists using a Min-Heap
void mergeLists(int* lists[], int k, int n) {
    MinHeap* minHeap = createMinHeap();
    int outputSize = k * n;
    int output[outputSize];

    // Insert the first element from each list into the heap
    for (int i = 0; i < k; i++) {
        HeapNode newNode = {lists[i][0], i, 1};
        insertNode(minHeap, newNode);
    }

    // Perform merging
    for (int i = 0; i < outputSize; i++) {
        HeapNode minNode = extractMin(minHeap);
        output[i] = minNode.value;

        // If there are more elements in the list from which minNode was extracted, insert the next element into the heap
        if (minNode.nextIndex < n) {
            minNode.value = lists[minNode.listIndex][minNode.nextIndex];
            minNode.nextIndex++;
            insertNode(minHeap, minNode);
        }
    }

    // Print the merged list
    printf("Merged list: ");
    for (int i = 0; i < outputSize; i++) {
        printf("%d ", output[i]);
    }
    printf("\n");

    // Free memory allocated for the heap
    free(minHeap);
}

int main() {
    // Example usage
    int k = 3;  // Number of lists
    int n = 4;  // Size of each list

    // Define k sorted lists
    int list1[] = {1, 3, 5, 7};
    int list2[] = {2, 4, 6, 8};
    int list3[] = {0, 9, 10, 11};

    // Store the lists in an array of pointers
    int* lists[] = {list1, list2, list3};

    // Merge the lists
    mergeLists(lists, k, n);

    return 0;
}

