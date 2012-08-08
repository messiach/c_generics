#include "stdio.h"
#include "string.h"

/* prototypes (forward declarations) */
void* lsearch(void*, void*, int, int);
void swap(void*, void*, int);
void testSwap();
void testLSearch();

/* main entry point */
int main (int argc, char** argv) {
  //testSwap();
  testLSearch();
}

/* generic linear search
 * parameters:
 * - void* key = item to search for
 * - void* list = list to search
 * - int n = number of elements in the list
 * - int elemSize = size of individual list elements
 * returns:
 * - void* = address of the element within the list 
 */
void* lsearch(void* key,
	      void* list, 
	      int n, 
	      int elemSize) {
  // loop through the list of elements
  for (int i=0; i < n; ++i) {
    // void pointer hack to coax the list into a char*, then do normal pointer arithmatic    
    void* elemAddr = (char*)list + i * elemSize;
    if (memcmp(key, elemAddr, elemSize)==0) {
      return elemAddr;
    }
  }
  // nothing found, return null
  return NULL;
}

/* generic swap 
 * parameters:
 * - void* vp1 = first element
 * - void* vp2 = second element
 * - int elemSize = size of each element
 * returns:
 * - nothing, side effect only of swapping values referred to by vp1 and vp2
 */ 
void swap(void* vp1, void* vp2, int elemSize) {
  // create a buffer of bytes the size of each element
  char buffer[elemSize];  

  // use memcpy to copy bytes from location to location
  memcpy(buffer, vp1, elemSize);
  memcpy(vp1, vp2, elemSize);
  memcpy(vp2, buffer, elemSize);
}

/* testing function for the swap */
void testSwap() {
  int x=45;
  int y=78;

  // print prior to swap
  printf("x=%i\n", x);
  printf("y=%i\n", y);

  // call swap
  swap(&x,&y,sizeof(int));

  // print after the swap
  printf("x=%i\n", x);
  printf("y=%i\n", y);
}

/* testing function for the lsearch */
void testLSearch() {
  int arr[5] = {1,2,3,4,5};
  int key = 3;

  printf("calling lsearch for key=%i\n", key);

  // call the list search
  void* elemAddr = lsearch(&key, arr, (sizeof(arr)/sizeof(int)), sizeof(int));

  // print what we found
  printf("found elemAddr=%p\n", elemAddr);
  printf("found item=%i\n", *((int*)elemAddr));
}
