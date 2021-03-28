/*
  Priority queue header file
  (C) 2021  xuri <xuri_tomcat@foxmail.com>
  
  This program is priority queue structure & functions decleration.

  priorityqueue.h
*/

#ifndef __PRIORITYQUEUEADT_H__
#define __PRIORITYQUEUEADT_H__

#ifdef __cplusplus
extern "C" {
#endif

#define MINKEYVALUE NULL
#define priorityqueue_for_each_element(Q, element, cnt) \
	for (cnt = 1, element = Q->elements[cnt]; cnt <= Q->size; element = Q->elements[++cnt])


typedef struct _element_type {
	void *key;
	void *value;
} element_type;

typedef int (*compare_handler_t)(void *, void *);

typedef struct priorityqueue_node {
	int capacity;
	int size;
	element_type *elements;
	compare_handler_t cb_func;
} priorityqueue_node_t;

typedef priorityqueue_node_t *ptrtopriorityqueue;

ptrtopriorityqueue
priorityqueue_init(int elements_num, compare_handler_t cb_func);

int
priorityqueue_deinit(ptrtopriorityqueue Q);

int
priorityqueue_clear(ptrtopriorityqueue Q);

int
priorityqueue_push(ptrtopriorityqueue Q, element_type X);

int
priorityqueue_top(ptrtopriorityqueue Q, element_type *out);

int
priorityqueue_pop(ptrtopriorityqueue Q, element_type *out);

int
priorityqueue_is_full(ptrtopriorityqueue Q);

int
priorityqueue_is_empty(ptrtopriorityqueue Q);


#ifdef __cplusplus
}
#endif

#endif
