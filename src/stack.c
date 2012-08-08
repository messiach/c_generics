#include "stack.h"
#include "assert.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#ifndef INIT_ALLOC
#define INIT_ALLOC 32
#endif

/* Create a new Stack */
/* Assumes stack structure has been created (memory allocated) */
/* Will copy data to the stack struct and allocate initial space for the stack elements */
void StackNew(stack* s, int size, void (*freefn)(void*)) {
  s->loglength = 0;
  s->alloclength = INIT_ALLOC;
  s->elemSize = size;
  s->freefn = freefn;
  s->elems = realloc(NULL, s->alloclength * s->elemSize);
  assert(s->elems != NULL);
}

/* Destroy the Stack */
/* Dispose will attempt to use the memory freeing function if it exists */
/* It is the responsibility of the client to correctly implement a memory freeing function */
void StackDispose(stack* s) {
  if (s->freefn != NULL) {
    for (int i=0; i < s->loglength; ++i) {
      s->freefn((char*)s->elems + i * s->elemSize);
    }
  }
 free(s->elems);
}

/* Push an item onto the Stack */
/* Will increment the top of the stack */
void StackPush(stack* s, void* elemAddr) {
  // stack full
  if(s->loglength == s->alloclength) {
    s->alloclength *= 2;  // doubling strategy for mem realloc
    s->elems = realloc(s->elems, s->alloclength * s->elemSize);
    assert(s->elems != NULL);
  }
  // using char* cast to use pointer arithmatic to get the top of the stack
  void* targetLoc = (char*)s->elems + (s->loglength * s->elemSize);  

  // using memcpy to copy the incoming data to the stack 
  memcpy(targetLoc, elemAddr, s->elemSize);

  // increment the top of the stack
  s->loglength++;
}

/* Pop an element off of the stack */
/* It is the client's responsibility to create the location to store the popped element */
void StackPop(stack* s, void* elemAddr) {
  // check for empty stack
  assert(s->loglength >= 0);

  // decrement the top of the stack
  s->loglength--;

  // grab the element on top
  void* sourceLoc = (char*)s->elems + (s->loglength * s->elemSize);

  // copy the element to the client address space provided
  memcpy(elemAddr, sourceLoc, s->elemSize);
}



// TESTING ONLY
void int_test() {
  // create a new stack
  stack* s = malloc(sizeof(stack));
  StackNew(s, sizeof(int), NULL);  // no mem freeing function

  // push ints on the stack
  int a=5, b=3, c=2;
  StackPush(s, &a);
  printf("pushing %i onto the stack...\n", a);
  StackPush(s, &b);
  printf("pushing %i onto the stack...\n", b);
  StackPush(s, &c);
  printf("pushing %i onto the stack...\n", c);

  // get the items off the stack
  int x, y, z;
  StackPop(s, &x);
  printf("popping %i off the stack...\n", x);
  StackPop(s, &y);
  printf("popping %i off the stack...\n", y);
  StackPop(s, &z);
  printf("popping %i off the stack...\n", z);

  printf("Disposing of the stack...\n");
  StackDispose(s);
}

// freeing function for cstrings
void freefn(void* elem) {
  // elem is a char** (vector of char* or cstrings)
  free(*((char**)elem));
}

// TESTING ONLY
void cstr_test() {
  // create a new stack
  stack s;
  StackNew(&s, sizeof(char*), &freefn);

  // push cstrings onto the stack
  char* str1 = "help";
  char* str2 = "me";
  printf("pushing '%s' onto the stack...\n",str1);
  StackPush(&s,&str1);
  printf("pushing '%s' onto the stack...\n",str2);
  StackPush(&s,&str2);

  // attempt to free something copied to the stack
  // this will prove - do we have a real copy on the stack or just a copy of the pointer?
  // free(str1);  // FAILS with a seg fault
  // free(str2);  // If you remove the previous line, this fails with an invalid pointer error
  // What we need to be sure of is that a duplicate deep copy of the cstrings pushed to the stack are created prior to pushing AND the pointer is not stored anywhere on the client (otherwise the client may still be able to free it)

  // get items off the stack
  char* str = realloc(NULL,(sizeof(char)*24));  // use an arbitrary space large enough to hold those items we know are on the stack
  StackPop(&s,&str);
  printf("popping '%s' off the stack...\n",str);
  StackPop(&s,&str);
  printf("popping '%s' off the stack...\n",str);

  printf("Disposing of the stack...\n");
  StackDispose(&s);
}


// TEST DRIVER
int main(char** argv, int argc) {

  // int_test();

  cstr_test();
 
}

/** NOTES:
 * 
 * 2 Bugs:
 *  - Need to deep copy cstrings before pushing to the stack and avoid having the client keep the pointer
 * - Attempting to clear the stack WITHOUT popping off all data causes a seg fault!
 */

