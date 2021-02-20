/*
  Priority queue source file
  (C) 2021  xuri <ri.xu@tcl.com>
  
  This program is priority queue functions description based on binary heap.

  priorityqueue.c
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "priorityqueue.h"

static int
default_compare_handler(void *key1, void *key2)
{
	int *ikey1 = (int *)key1;
	int *ikey2 = (int *)key2;
	
	if (*ikey1 < *ikey2) {
		return -1;
	} else if (*ikey1 == *ikey2) {
		return 0;
	} else {
		return 1;
	}
}


ptrtopriorityqueue
priorityqueue_init(int elements_num, compare_handler_t cb_func)
{
	if (elements_num <= 0) {
		printf("elements_num <= 0\n");
		return NULL;
	}

	ptrtopriorityqueue Q = NULL;
    Q = (ptrtopriorityqueue)malloc(sizeof(struct priorityqueue_node));
    if (Q == NULL) {
		printf("Q malloc failed\n");
        return NULL;
    }
    memset(Q, 0, sizeof(struct priorityqueue_node));
    
    Q->capacity = elements_num;
    Q->size = 0;
    Q->elements = (element_type *)malloc(sizeof(element_type) * (Q->capacity + 1));
    if (Q->elements == NULL) {
        if (Q != NULL) {
			printf("Q->elements malloc failed\n");
            free(Q);
        }
		return NULL;
    }
	memset(Q->elements, 0, sizeof(element_type) * (Q->capacity + 1));

	if (cb_func != NULL) {
		Q->cb_func = cb_func;
	} else {
		Q->cb_func = default_compare_handler;
	}
	
	return Q;
}

int
priorityqueue_is_full(ptrtopriorityqueue Q)
{
	if (Q == NULL) {
		printf("ptrtopriorityqueue is NULL\n");
		return -1;
	}

	return (Q->capacity == Q->size ? 1 : 0);
}

int
priorityqueue_is_empty(ptrtopriorityqueue Q)
{
	if (Q == NULL) {
		printf("ptrtopriorityqueue is NULL\n");
		return -1;
	}

	return (Q->size == 0 ? 1 : 0);
}

int
priorityqueue_push(ptrtopriorityqueue Q, element_type X)
{
	if (Q == NULL) {
		printf("ptrtopriorityqueue is NULL\n");
		return -1;
	}
	
	if (priorityqueue_is_full(Q) == 1) {
		printf("ptrtopriorityqueue is full\n");
		return -1;
	}

	int cnt = 1;
	if (Q->size > 0) {
		for (cnt = ++Q->size; cnt > 1 && Q->cb_func((Q->elements[cnt >> 1]).key, X.key) == 1; cnt = cnt >> 1) {
			Q->elements[cnt] = Q->elements[cnt >> 1];
		}
	} else {
		++Q->size;
	}
	Q->elements[cnt] = X;

	return 0;
}


int
priorityqueue_pop(ptrtopriorityqueue Q, element_type *out)
{
	if (Q == NULL) {
		printf("ptrtopriorityqueue is NULL\n");
		return -1;
	}
	
	if (priorityqueue_is_empty(Q) == 1) {
		printf("ptrtopriorityqueue is empty\n");
		return -1;
	}

	int cnt, Child;
	element_type min_key_value = Q->elements[1];
	element_type last_key_value = Q->elements[Q->size--];	

	for (cnt = 1; 2 * cnt <= Q->size; cnt = Child) {
		Child = 2 * cnt;
		if (Child < Q->size && Q->cb_func(Q->elements[Child].key, Q->elements[Child + 1].key) == 1) {
			Child++;
		}

		if (Q->cb_func(last_key_value.key, Q->elements[Child].key) == 1) {
			Q->elements[cnt] = Q->elements[Child];
		} else {
			break;
		}
	}
	Q->elements[cnt] = last_key_value;
	*out = min_key_value;

	return 0;
}


int
priorityqueue_top(ptrtopriorityqueue Q, element_type *out)
{
	if (Q == NULL) {
		printf("ptrtopriorityqueue is NULL\n");
		return -1;
	}

	if (priorityqueue_is_empty(Q) == 1) {
		printf("ptrtopriorityqueue is empty\n");
		return -1;
	}

	*out = Q->elements[1];
	return 0;
}

int
priorityqueue_deinit(ptrtopriorityqueue Q)
{
	if (Q != NULL) {
		if (Q->elements != NULL) {
			free(Q->elements);
		}
		free(Q);
		return 0;
	} else {
		printf("ptrtopriorityqueue is NULL\n");
		return -1;
	}
}

int
priorityqueue_clear(ptrtopriorityqueue Q)
{
	if (Q != NULL) {
		if (Q->elements != NULL) {
			memset(Q->elements, 0, sizeof(element_type) * (Q->capacity + 1));
		}
		Q->size = 0;
		return 0;
	} else {
		printf("ptrtopriorityqueue is NULL\n");
		return -1;
	}	
}


