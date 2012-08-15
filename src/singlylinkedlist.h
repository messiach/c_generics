#include "stdlib.h"

/*
 * Singly linked list definition
 *
 * This is a generic singly linked list
 * - elemSize = size of the data being stored in the list
 * - elem = pointer to the data being stored in this node 
 *   (storage of the elem is done at the time the node is created and pushed onto the list)
 * - next = pointer to the next node in the list
 */
typedef struct node {
  int elemSize;
  void* elem;
  struct node* next;
} node;

/* Create a new singly linked list */
void SinglyListCreateNode(node*, void*, int);

/* Append to the singly linked list after specified node */
void SinglyListAppendAfter(node**, void*, int);






/* Append to the singly linked list at the beginning of a list */
void SingleListAppendBeginning(node**, void*);

/* Remove from the list after specified node */
void SingleListRemoveAfter(node**, void*);

/* Remove from list at the beginning */
node* SingleListRemoveBeginning(node**, void**);

/* Destroy the list */
void SingleListDestroy(node**, /*free function*/void (*freefn)(node*));
