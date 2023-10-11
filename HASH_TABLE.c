

#include <stdio.h>             //header files
#include <stdlib.h>

// Define a structure for linked list nodes

struct ListNode {
    int element;                        //data stored in th node
    struct ListNode* next;           //Pointer to the next node
};

// Function to create a new linked list node
struct ListNode* createListNode(int element) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    newNode->element = element;
    newNode->next = NULL;
    return newNode;
}

// Definition of structure for the hash table
struct HashTable {
    int tableSize;         //Size of hte hash table
    struct ListNode** table;       //Array of linked list table
};

//  creating a new hash table
struct HashTable* createHashTable(int size) {
    struct HashTable* hashTable = (struct HashTable*)malloc(sizeof(struct HashTable));
    hashTable->tableSize = size;
    hashTable->table = (struct ListNode**)malloc(sizeof(struct ListNode*) * size);

    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }

    return hashTable;
}

// Hash function to calculate the index for a element( h(k)=k%m )

int calculateHash(int element, int size) {
    int hash = element % size;
    if (hash < 0) {
        hash += size;  // Ensure the hash is non-negative
    }
    return hash;
}

// Function to insert a element into the hash table
void insert(struct HashTable* hashTable, int element) {
     int index = calculateHash(element, hashTable->tableSize);
       struct ListNode* newNode = createListNode(element);

    if (hashTable->table[index] == NULL) {      //if the slot is empty,add the new slot
        hashTable->table[index] = newNode;
    } else {
        newNode->next = hashTable->table[index];   //if slot is not empty,add the new node at the beginning of the linked list
        hashTable->table[index] = newNode;
    }
}

// Function to delete a element from the hash table
void deleteelement(struct HashTable* hashTable, int element) {

    int index = calculateHash(element, hashTable->tableSize);
    
       struct ListNode* current = hashTable->table[index];
    
       struct ListNode* previous = NULL;

    while (current != NULL) {
        if (current->element == element) {
            if (previous == NULL) {
                hashTable->table[index] = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }

    printf("Searched element %d is not found in slot %d\n", element, index);
}

// Function to search for a element in the hash table

void search(struct HashTable* hashTable, int element) {

    int index = calculateHash(element, hashTable->tableSize);

    struct ListNode* current = hashTable->table[index];
//if element is present
    while (current != NULL) {
        if (current->element == element) {
            printf("Searched element %d is found in slot number %d\n",element, index);
            return;
        }
        current = current->next;
    }
          //if the element is not found

    printf("Element is not present\n");
}

// Function to display the elements of the hash table

void display(struct HashTable* hashTable) {
    for (int k = 0; k < hashTable->tableSize; k++) {
                 printf("index %d: ", k);


        struct ListNode* current = hashTable->table[k];
        while (current!= NULL) {
                printf("%d  ", current->element);
            current = current->next;
        }

        printf("NULL\n");
    }
}

int main() {

    int tableSize;
        printf("Enter hash table size m: ");
        scanf("%d", &tableSize);


    struct HashTable* hashTable = createHashTable(tableSize);

    while (1) {

        int choice;

       
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Display\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int element;
        switch (choice) {


            case 1:            //Insert 
                printf("Enter value to insert: ");
                scanf("%d", &element);
                insert(hashTable, element);
                break;

            case 2:                 //Delete
                printf("Enter value to delete: ");
                scanf("%d", &element);
                deleteelement(hashTable, element);
                break;

            case 3:               //Search
                printf("Enter the element to be searched: ");
                scanf("%d", &element);
                search(hashTable, element);
                break;

            case 4:            //Display
                display(hashTable);
                break;
 
            case 5:            //Quit
                return 0;

            default:          
                printf("Invalid choice.\n");
        }
    }

    // Free allocated memory 
    for (int i = 0; i < tableSize; i++) {
        struct ListNode* current = hashTable->table[i];
        while (current != NULL) {
            struct ListNode* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable->table);
    free(hashTable);

    return 0;

    //CODE ENDING
}
