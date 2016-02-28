#ifndef __HEAP_H__
#define __HEAP_H__ 1

#define HEAP_STARTING_SIZE 15

/**
 * Comparator
 * a function that compares two values
 *
 * a, b: the input values
 * return:
 *   >0 if a > b
 *   0  if a == b
 *   <0 if a < b
 */
typedef int (*Comparator)(void* a, void* b);

/**
 * Heap
 * a struct thats holds the values for a max heap
 *
 * tree: binary tree of values for this tree
 * size: the size of the binary tree
 * count: the number of values in the tree
 * comp: the comparator function (do not modify)
 * free_func: the function used to free remaining elements from the heap
 */
typedef struct {
	void** tree;
	size_t size;
	size_t count;
	Comparator comp;
	void (*free_func)(void*);
} Heap;

/**
 * creates a new heap with the given comparator and free function
 *
 * comp: the comparator
 * free_func: the free function
 * return: a new heap
 */
Heap* heap_new(Comparator comp, void (*free_func)(void*));

/**
 * creates a new heap with the given comparator and 'free' as the free function
 *
 * comp: the comparator
 * return: a new heap
 */
Heap* heap_default(Comparator comp);

/**
 * peeks the top value of the heap. does not modify the heap
 *
 * h: the heap to use
 * return: the top value
 */
void* heap_peek(Heap* h);

/**
 * pops the top value off of the heap
 *
 * h: the heap to modify
 * return: the top value
 */
void* heap_pop(Heap* h);

/**
 * pushes a value onto the heap
 *
 * h: the heap to modify
 * val: the value to push onto the heap
 */
void heap_push(Heap* h, void* val);

/**
 * frees this heap and its remaining elements
 * will not free elements if free_func == NULL
 *
 * h: the heap to free
 */
void heap_free(Heap* h);

#endif
