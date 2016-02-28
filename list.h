#ifndef __LIST_H__
#define __LIST_H__ 1

/**
 * Node
 * a node for a doubly linked list
 *
 * next: ptr to next node (NULL if none)
 * prev: ptr to prev node (NULL if none)
 * data: ptr to this node's data
 */
typedef struct _node {
	struct _node* next;
	struct _node* prev;
	void* data;
} Node;

/**
 * List
 * A doubly linked list
 * 
 * first: the first node in this list
 * last: the last node in this list
 * size: the number of elements in this list
 * free_func: function to use to free the data of deleted nodes
 */
typedef struct _list {
	Node* first;
	Node* last;
	size_t size;
	void (*free_func)(void*);
} List;

/**
 * creates a new node containing the given data
 *
 * data: the data being held by this node
 */
Node* node_new(void* data);

/**
 * frees the given node and returns it value
 *
 * n: the node to unwrap
 */
void* node_unwrap(Node* n);

/**
 * frees this node and it's data
 * data will not be freed if it or free_func is NULL
 *
 * free_func: the function to use to free the data
 */
void node_free(Node* n, void (*free_func)(void*));

/**
 * creates a new list that has a default free_func of free
 */
List* list_default();

/**
 * creates a new list with the given free_func
 *
 * free_func: the free_func for this list
 */
List* list_new(void (*free_func)(void*));

/**
 * adds the given data to the list as a new node on the end
 *
 * data: the data the new node should hold
 */
void list_add(List* l, void* data);

/**
 * gets nth node of this list (like an array lookup)
 *
 * n: the index of the node to return
 */
Node* list_nth(List* l, int n);

/**
 * gets the data stored at index i
 *
 * i: the index
 */
void* list_get(List* l, int i);

/**
 * pops a value from the front of the list
 *
 * l: the list to modify
 */
void* list_pop(List* l);

/**
 * detaches a node from this list
 * 
 * n: the node to be detached
 */
void list_detach(List* l, Node* n);

/**
 * detaches the given node from this list and frees it
 *
 * n: the node to be deleted
 */
void list_delete(List* l, Node* n);

/**
 * deletes all the nodes in this list
 */
void list_clear(List* l);

/**
 * frees this list and all contained nodes
 */
void list_free(List* l);

#endif
