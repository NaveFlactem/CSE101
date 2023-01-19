/*
Name: Evan Metcalf
CruzID: evmetcal 1963052
Assignment Name: pa1
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"

// structs --------------------------------------------------------------------
typedef struct NodeObj* Node;

typedef struct NodeObj{
    ListElement data;
    Node prev;
    Node next;
}NodeObj;

typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int index;
    int length;
}ListObj;
//------------------------------------------------------------------------------

// Constructors-Destructors ---------------------------------------------------
List newList(void){
    List L = (List) malloc(sizeof(struct ListObj)); //defines L and allocates memory for the struct List and assigns to L
    if(L == NULL) {
        printf("Error: memory allocation failed in List creation\n");
        return NULL;
    }  //check the case of the above line failing
    L->length = 0; //set list size to 0
    L->front = L->back = L->cursor = NULL; //sets pointers to Null
    return L; //return the new list
}


//used in functions to make a new node with int x;
Node newNode(int x) {
    Node N = malloc(sizeof(NodeObj)); //defines N and creates a new node
    if(N == NULL) {
        printf("Error: memory allocation failed in Node creation\n");
        return NULL;
    }  //check the case of the above line failing
    N->data = x;
    N->next = N->prev = NULL;
    return N;
}

void freeList(List* pL){
    if (pL != NULL && *pL != NULL) {
        while ((*pL)->length != 0) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}
// Frees all heap memory associated with *pL, and sets
 // *pL to NULL



//used in delete functions to free a node
void freeNode(Node* pN){
    if (pN == NULL || *pN == NULL){
        return -1;
    } //check if pN or *pN are NULL so the function is exited before wasting time
    free(*pN);
    *pN = NULL;
}

















// Access functions -----------------------------------------------------------
int length(List L){
    if(L == NULL){
        printf("Error: NULL List\n");
        return -1;
    }
    return L->length;
} // Returns the number of elements in L.


int index(List L){
    if(L == NULL){
        printf("Error: List is NULL\n");
        return -1;
    }
    if(L->cursor == NULL){
        return -1;
    }
    return L->index;
} // Returns index of cursor element if defined, -1 otherwise.


int front(List L){
    if(L == NULL){
        printf("Error: NULL List\n");
        return -1;
    }
    if(L->length == 0){
        printf("Error: Empty List\n");
        return -1;
    }
    return L->front->data;
} // Returns front element of L. Pre: length()>0


int back(List L){
    if(L == NULL){
        printf("Error: NULL List\n");
        return -1;
    }
    if(L->length == 0){
        printf("Error: Empty List\n");
        return -1;
    }
    return L->back->data;
} // Returns back element of L. Pre: length()>0


int get(List L){
    if(L == NULL){
        printf("Error: NULL List\n");
        return -1;
    }
    if(L->length == 0){
        printf("Error: Empty List\n");
        return -1;
    }
    // if(L->index < 0){
    //     printf("Error: Undefined cursor\n");
    //     return -1;
    // }
    return L->cursor->data;
} // Returns cursor element of L. Pre: length()>0, index()>=0


bool equals(List A, List B){
    if (A == NULL || B == NULL || A->length != B->length){
        return false;
    }
    //check conditions that would immediately mean false

    //loop through the list comparing between the two lists
    Node currA = A->front;
    Node currB = B->front;
    while (currA != NULL && currB != NULL) {
        if (currA->data != currB->data){
            return false;
        }
        currA = currA->next;
        currB = currB->next;
    }
    //if it gets to here then they match so return true
    return true;
} // Returns true if Lists A and B are in same
 // state, and returns false otherwise.

























// Manipulation procedures ----------------------------------------------------
void clear(List L){
    if (L == NULL) {
        printf("Error: NULL List");
        return;
    }

    while(length(L) > 0) deleteFront(L);
    L->cursor = NULL;
    L->index = -1;
} // Resets L to its original empty state.


void set(List L, int x){
    if(L == NULL){
        printf("Error: NULL List\n");
        return;
    }
    if(L->length == 0){
        printf("Error: Empty List\n");
        return;
    }
    if(L->index < 0){
        printf("Error: Undefined cursor\n");
        return;
    }    
    L->cursor->data = x;
    
} // Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0


void moveFront(List L){
    if(L == NULL){
        printf("Error: NULL List\n");
        return;
    }
    if(L->length == 0){
        printf("Error: Empty List\n");
        return;
    }
    L->cursor = L->front;
    L->index = 0;
} // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.


void moveBack(List L){
    if(L == NULL){
        printf("Error: NULL List\n");
        return;
    }
    if(L->length == 0){
        printf("Error: Empty List\n");
        return;
    }
    L->cursor = L->back;
    L->index = L->length - 1;
} // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.


void movePrev(List L){
    if(L == NULL){
        printf("Error: NULL List\n");
        return;
    }
    
    if(L->index > 0){
        L->cursor = L->cursor->prev;
        L->index--;
    }
    else if(L->index == 0){
        L->cursor = NULL;
        L->index = -1;
    }
    else{
        printf("Error");
        return;
    }
}// If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing


void moveNext(List L){
    if(L == NULL){
        printf("Error: NULL List\n");
        return;
    }
    if(L->index < L->length - 1){
        L->cursor = L->cursor->next;
        L->index++;
    }
    else if(L->index == L->length - 1){
        L->cursor = NULL;
        L->index = -1;
    }
    else{
        printf("Error");
        return;
    }
} // If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing


void prepend(List L, int x) {
    if(L == NULL){
        printf("Error: NULL List\n");
        return;
    }

    Node temp = newNode(x);
    
    if (length(L) == 0){
        L->front = L->back = temp;
    }
    else{
        temp->next = L->front;
        L->front->prev = temp;
        L->front = temp;
    }

    L->length++;
    
    if(L->index >= 0){ 
        L->index++;
    }
} // Insert new element into L. If L is non-empty,
 // insertion takes place before front element.


void append(List L, int x){
    if(L == NULL){
        printf("Error: NULL List\n");
        return;
    }
    
    Node temp = newNode(x);
    
    if (length(L) == 0){
        L->front = L->back = temp;
    }
    else{
        temp->prev = L->back;
        L->back->next = temp;
        L->back = temp;
    }

    L->length++;
} // Insert new element into L. If L is non-empty,
 // insertion takes place after back element.


void insertBefore(List L, int x){
    if(L == NULL){
        printf("Error: NULL List\n");
        return;
    }
    if(L->cursor == NULL) {
        printf("Error: Undefined cursor\n");
        return;
    }
    Node temp = newNode(x);
    temp->prev = L->cursor->prev;
    temp->next = L->cursor;
    L->cursor->prev->next = temp;
    L->cursor->prev = temp;
    L->length++;
    if (L->index >= 0){
        L->index++;
    }
} // Insert new element before cursor.
 // Pre: length()>0, index()>=0


void insertAfter(List L, int x){
    if(L == NULL){
        printf("Error: NULL List\n");
        return;
    }
    if(L->cursor == NULL) {
        printf("Error: Undefined cursor\n");
        return;
    }
    if(index >= 0){
        Node temp = newNode(x);
        temp->prev = L->cursor;
        temp->next = L->cursor->next;
        L->cursor->next = temp;
        L->cursor->next->prev = temp;
        if(L->cursor = L->back){
            L->back = temp;
        }
    L->length++;
    }
} // Insert new element after cursor.
 // Pre: length()>0, index()>=0


void deleteFront(List L){
    if(L==NULL){
        printf("Error: NULL List\n");
        return;
    }
    if(L->length == 0){
        printf("Error: Empty List\n");
        return;
    }
    Node temp = L->front;
    if(L->front->next != NULL){
        L->front = L->front->next;
        L->front->prev = NULL;
    }
    else{
        L->front = L->back = NULL;
    }
    
    if(L->index == 0){
        L->cursor = NULL;
        L->index = -1;
    }
    else if(L->index > 0){
        L->index--;
    }
    freeNode(&temp);
    L->length--;
} // Delete the front element. Pre: length()>0


void deleteBack(List L){
    if(L==NULL){
        printf("Error: NULL List\n");
        return;
    }
    if(L->length == 0){
        printf("Error: Empty List\n");
        return;
    }

    Node temp = L->back;
    if(L->back->prev != NULL){
        L->back = L->back->prev;
        L->back->next = NULL;
    }
    else{
        L->front = L->back = NULL;
    }
    if(L->index == L->length - 1){
        L->cursor = NULL;
        L->index = -1;
    }
    freeNode(&temp);
    L->length--;
} // Delete the back element. Pre: length()>0


void delete(List L){
    if(L==NULL){
        printf("Error: NULL List\n");
        return;
    }
    if(L->length == 0){
        printf("Error: Empty List\n");
        return;
    }
    if(L->cursor == NULL) {
        printf("Error: Undefined cursor\n");
        return;
    }
    Node temp = L->cursor;
    if(temp->prev != NULL){
        temp->prev->next = temp->next;
    }
    else{
        L->front = temp->next;
    }

    if(temp->next != NULL){
        temp->next->prev = temp->prev;
    }
    else{
        L->back = temp->prev;
    }
    L->cursor = NULL;
    L->index = -1;
    free(&temp);
    L->length--;
} // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0





















// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
    if(L==NULL){
        printf("Error: NULL List\n");
        return;
    }
    Node temp = L->front;
    while (temp != NULL){
        fprintf(out, "%d\n", temp->data);
        temp = temp->next;
    }
} // Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.


List copyList(List L){
    if(L==NULL){
        printf("Error: NULL List\n");
        return NULL;
    }
    List L2 = newList();
    Node temp = L->front;
    while(temp != NULL){
        append(L2, temp->data);
        temp = temp ->next;
    }
    return L2;
} // Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.


List concatList(List A, List B){
    if(A==NULL || B==NULL){
        printf("Error: Concatenation on NULL List\n");
        return NULL;
    }
    List L = copyList(A);
    Node temp = B->front;
    while(temp != NULL){
        append(L, temp->data);
        temp = temp->next;
    }
    return L;
} // Returns a new List which is the concatenation of
 // A and B. The cursor in the new List is undefined,
 // regardless of the states of the cursors in A 

