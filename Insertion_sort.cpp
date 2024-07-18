#include <iostream>
using namespace std;

// Class for New Node
class NewNode
{
public:
    int data;
    NewNode *next;
    NewNode *prev;
    NewNode(int data)
    {
        this->data = data;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

// Class for New LinkedList
class Node
{
public:
    NewNode *head;
    NewNode *tail;
    Node()
    {
        // Head and tail points to NULL at start
        this->head = nullptr;
        this->tail = nullptr;
    }
    // Insert new node at end position
    void insert(int value)
    {
        // Creating a new node
        NewNode *node = new NewNode(value);
        if (this->head == nullptr)
        {
            // Adding first node
            this->head = node;
            this->tail = node;
            return;
        }
        // Adding node at last position
        this->tail->next = node;
        node->prev = this->tail;
        this->tail = node;
    }


    // Displaying node element of doubly linked list
    void print()
    {
        if (this->head == nullptr)
        {
            cout << "Empty Linked List" << endl;
        }
        else
        {
            cout << "\nLinked List Head to Tail :";

            // Get first node of linked list
            NewNode *temp = this->head;
            // iterate linked list
            while (temp != nullptr)
            {
                // Displaying node value
                cout << " " << temp->data;
                // Visiting next node
                temp = temp->next;
            }
            cout << "\n";
        }
    }
    // Swapping value of given nodes
    void swapData(NewNode *first, NewNode *second)
    {
        int value = first->data;
        first->data = second->data;
        second->data = value;
    }
    // Sort elements using insertion sort
    void Sort()
    {
        // Getting first node
        NewNode *front = this->head;
        NewNode *back = nullptr;
        while (front != nullptr)
        {
            // Getting next node
            back = front->next;
            // Updating node value when consecutive nodes are not sorted
            while (back != nullptr &&
                   back->prev != nullptr &&
                   back->data < back->prev->data)
            {
                // Changed node data
                this->swapData(back, back->prev);
                // Visiting previous node
                back = back->prev;
            }
            // Visiting next node
            front = front->next;
        }
    }
};
int main()
{ // Initializing new double-linked
    Node *newLL = new Node();
    // Insert element of linked list
    int n;
    cout << " Number of elements in linked list:" << endl;
    cin >> n;

    cout << "Enter thr elements in linked list:" << endl;
    for(int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        newLL->insert(x);
    }

    cout << "Doubly linked list before sorting";
    // printing unsorted linked list
    newLL->print();

    // Sorting the linked list using insertion sort
    newLL->Sort();
    
    cout<<endl;
    cout << "Doubly linked list after sorting";
    // printing sorted linked list
    newLL->print();
    return 0;
}
