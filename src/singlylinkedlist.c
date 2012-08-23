#include "singlylinkedlist.h"
#include "string.h"
#include "stdio.h"

/*
 * Implementation of a singly linked list
 */

/* create a new node with some data */
void SinglyListCreateNode(node** newNode, void* data, int dataSize) {
  (*newNode)->elemSize = dataSize;
  (*newNode)->next = NULL;  // null the next for now - will insert later

  // copy the data to the node
  (*newNode)->elem = malloc((*newNode)->elemSize);
  memcpy((*newNode)->elem, data, (*newNode)->elemSize);
}

/* append after a node in the list */
void SingleListAppendAfter(node** insertPoint, void* data, int dataSize) {
  node** temp = insertPoint; 

  // if the insert node is null, create it as a node and store the data there
  // this is the 'head' case
  if (temp == NULL) {
    node* head = malloc(sizeof(node));
    SinglyListCreateNode(&head, data, dataSize);
  }

  // if the insert node is not null, create a new node and append it after the 
  // insert node given, making sure to append the node after the insert node
  // to the end of the new node.
  else {
    node* afterNode = (*insertPoint)->next;
    node* newNode = NULL;
    SinglyListCreateNode(&newNode, data, dataSize);
    (*insertPoint)->next = newNode;
    newNode->next = afterNode;
  }
}

/* append before a node in the list */
void SingleListAppendBeginning(node** head, void* data, int dataSize) {
  // create a new node
  node* newNode = malloc(sizeof(node));
  SinglyListCreateNode(&newNode, data, dataSize);
  // insert before the head
  newNode->next = *head;
  // reset the head to the new node
  head = &newNode;
}

/* Remove from the list after a specified node */
void SingleListRemoveAfter(node** removePoint, void* removedData) {
  // get the node after the remove point
  void* afterNode = (*removePoint)->next->next;

  // copy the data from the removed node
  memcpy(removedData, (*removePoint)->next->elem, (*removePoint)->next->elemSize);
  free((*removePoint)->next);
  (*removePoint)->next = afterNode;
}

/* remove from the head and set the new head */
void SingleListRemoveBeginning(node** head, void* removedData) {
  // remove the head, new head is returned
  void* newHead = (*head)->next;
  // copy the data from the removed node
  memcpy(removedData, (*head)->elem, (*head)->elemSize);

  // set the new head and return it
  (*head) = newHead;
}

/* destroy the list */
void SingleListDestroy(node** head, void (*freefn) (node* node)) {
  // go through each node in the list and call the freefn
  if (head!=NULL) {
    while(*head!=NULL) {
      node* next = (*head)->next;
      freefn(*head);
      head = &next;
    } 
  }
}



/** --- TESTING AREA --- **/
int main(char** argv, int argc) {

  // create a list
  node* head = malloc(sizeof(node));

  // create a head node with some data
  int start = 1;
  SinglyListCreateNode(&head, &start, sizeof(int));
  
  // print out the new node
  printf("head pointer is = %p\n", head);
  printf("head data is = %i\n", *((int*)head->elem));
}
