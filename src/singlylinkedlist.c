#include "singlylinkedlist.h"
#include "string.h"

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
  node* temp = *insertPoint; 

  // if the insert node is null, create it as a node and store the data there
  // this is the 'head' case
  if (temp == NULL) {
    SinglyListCreateNode(&temp, data, dataSize);
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
void SingleListAppendBeginning(node** head, node* insertNode) {
  // insert before the head
  (*insertNode)->next = head;
}

/* Remove from the list after a specified node */
void SingleListRemoveAfter(node** removePoint, node* removedNode) {
  // remove after 
  void* afterNode = (*removePoint)->next->next;
  removedNode = (*removePoint)->next;
  (*removePoint)->next = afterNode;
}

/* remove from the head and set the new head */
node* SingleListRemoveBeginning(node** head, node* removedNode) {
  // remove the head, new head is returned
  void* newHead = (*head)->next;
  removedNode = (*head);
  return newHead;
}

/* destroy the list */
void SingleListDestroy(node** head, void (*freefn) (node* node)) {
  // go through each node in the list and call the freefn
  while(head!=NULL) {
    node* next = (*head)->next;
    freefn(*head);
    head = &(head->next);
  }
}


int main(char** argv, int argc) {

  // create a list
  node* head = NULL;
  
  // add main args to linked list
  if(argv!=NULL) {
    for(int i=0; i < argc; ++i) {
      node* newNode = malloc(sizeof(node));
      assert(newNode!=NULL);

      SingleListCreateNode(newNode, argv[i], sizeof(char)*strlen(argv[i]));

  }
}
