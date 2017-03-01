#include <stdlib.h>

#include "heap.h"

Heap* heap_new(Comparator comp, void (*free_func)(void*)) {
	Heap* h = malloc(sizeof(Heap));
	h->tree = malloc(HEAP_STARTING_SIZE * sizeof(void*));
	h->size = HEAP_STARTING_SIZE;
	h->count = 0;
	h->comp = comp;
	h->free_func = free_func;
	return h;
}

Heap* heap_default(Comparator comp) {
	return heap_new(comp, &free);
}

void* heap_peek(Heap* h) {
	// return top item
	if (h->count > 0)
		return h->tree[0];
	else
		return NULL;
}

void* heap_pop(Heap* h) {
	if (h->count <= 0) return NULL;

	// repace first item with last item
	void* val = h->tree[0];
	h->tree[0] = h->tree[--h->count];

	// balance
	int pos = 0;
	for (;;) {
		// calc child indexes
		int left = 2*pos + 1;
		int right = 2*pos + 2;
		int bigger;

		// check for out of bounds
		if (left >= h->count)
			break;
		else if (right >= h->count)
			bigger = left;
		// find bigger child
		else if ((*h->comp)(h->tree[left], h->tree[right]) >= 0)
			bigger = left;
		else
			bigger = right;

		// check current value versus child value
		if ((*h->comp)(h->tree[pos], h->tree[bigger]) < 0) {
			void* tmp = h->tree[pos];
			h->tree[pos] = h->tree[bigger];
			h->tree[bigger] = tmp;
			pos = bigger;
		} else {
			break;
		}
	}

	return val;
}

void heap_push(Heap* h, void* val) {
	int pos = h->count++;

	// resize if needed
	if (h->count >= h->size) {
		h->size = h->size*2 + 1;
		h->tree = realloc(h->tree, h->size * sizeof(void*));
	}

	// add new value
	h->tree[pos] = val;

	// balance
	for (;;) {
		int parent = (pos-1) / 2;

		// check bounds
		if (pos <= 0)
			break;
		// check to see if pos > parent
		else if ((*h->comp)(h->tree[pos], h->tree[parent]) > 0) {
			void* tmp = h->tree[pos];
			h->tree[pos] = h->tree[parent];
			h->tree[parent] = tmp;
			pos = parent;
		} else {
			break;
		}
	}
}

void heap_free(Heap* h) {
	// free children
	if (h->free_func != NULL) {
		for (int i = 0; i < h->count; i++) {
			if (h->tree[i] != NULL)
				(*h->free_func)(h->tree[i]);
		}
	}
	free(h);
}
