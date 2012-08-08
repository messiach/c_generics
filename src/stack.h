/** 
 * Simple implementation of a type-generic stack
 */
#include "stdlib.h"

/* stack will describe:
   - elems = list of items on the stack
   - loglength = number of items on the stack (logical length of the stack)
   - alloclength = number of storage locations allocated on the stack
   - elemSize = size of the data type on the stack (int, long, char, etc..)
   - freefn = a function that will free items on the stack (complex types like cstrings)
*/
typedef struct {
  void* elems;
  int loglength;
  int alloclength;
  int elemSize;
  void (*freefn)(void*);
} stack;

/* Need the stack, the data type size, and a mem free function */
void StackNew(stack*, int, void (*freefn)(void*));

/* Dispose will use the mem free function if it is available */
/* This is necessary for more complex types of elems held by the stack */
void StackDispose(stack*);

/* Need the stack and the element being pushed onto the stack */
void StackPush(stack*, void*);

/* Need the stack and a location to place the popped item */
/* It is recommended the client provide the store location */
/* the 'client' should not be responsible for mem alloc'd by the function */
/* so.. the 'client' will alloc the location and provide it to the function */
void StackPop(stack*, void*);
