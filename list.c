#include <stdlib.h>
#include "list.h"

Node* node_new(void* data) {
	Node* n = malloc(sizeof(Node));
	n->next = NULL;
	n->prev = NULL;
	n->data = data;
	return n;
}

void* node_unwrap(Node* n) {
	void* data = n->data;
	free(n);
	return data;
}

void node_free(Node* n, void (*free_func)(void*)) {
	if (free_func != NULL && n->data != NULL)
		(*free_func)(n->data);
	free(n);
}

List* list_default() {
	return list_new(&free);
}

List* list_new(void (*free_func)(void*)) {
	List* l = malloc(sizeof(List));
	l->first = NULL;
	l->last = NULL;
	l->size = 0;
	l->free_func = free_func;
	return l;
}

void list_add(List* l, void* data) {
	Node* n = node_new(data);

	if (l->first == NULL) {
		l->first = n;
	} else {
		l->last->next = n;
		n->prev = l->last;
	}

	l->last = n;
	l->size++;
}

Node* list_nth(List* l, int n) {
	if (n < 0 || n >= l->size) return NULL;

	Node* nptr;

	// pick a side to start on
	if (n <= l->size / 2) {
		nptr = l->first;
		for (int i = 0; i < n && nptr != NULL; i++) {
			nptr = nptr->next;
		}
	} else {
		nptr = l->last;
		for (int i = l->size-1; i > n && nptr != NULL; i--) {
			nptr = nptr->prev;
		}
	}

	return nptr;
}

void* list_get(List* l, int i) {
	Node* n = list_nth(l, i);
	return (n == NULL) ? NULL : n->data;
}

void* list_pop(List* l) {
	if (l->first == NULL)
		return NULL;

	// detach and unwrap the first node
	Node* n = l->first;
	list_detach(l, n);
	return node_unwrap(n);
}

// potential error:
// this function does not verify the given node is in the given list
void list_detach(List* l, Node* n) {
	if (n->prev != NULL)
		n->prev->next = n->next;
	if (n->next != NULL)
		n->next->prev = n->prev;
	if (l->first == n)
		l->first = n->next;
	if (l->last == n)
		l->last = n->prev;
	n->prev = NULL;
	n->next = NULL;
	l->size--;
}

void list_delete(List* l, Node* n) {
	list_detach(l, n);
	node_free(n, l->free_func);
}

void list_clear(List* l) {
	while (l->first != NULL) {
		list_delete(l, l->first);
	}
	l->size = 0;
}

void list_free(List* l) {
	Node* n = l->first;
	while (n != NULL) {
		Node* tmp = n;
		n = n->next;
		node_free(tmp, l->free_func);
	}
	free(l);
}
