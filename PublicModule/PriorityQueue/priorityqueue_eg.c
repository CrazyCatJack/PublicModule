/*
  Priority queue testcase
  (C) 2021  xuri <ri.xu@tcl.com>
  
  This program is priority queue testcase.

  priorityqueue_eg.c
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "priorityqueue.h"

#define TEST_INT	0
#define INSERT_NUM	10
#define MAXELEMENTS 50

#if TEST_INT
#define INSERT_ARRAY	{2, 10, 33, 4, 1, 8, 6, 7, 44, 30}

int
cb_func(void *key1, void *key2)
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

void
print_priorityqueue(ptrtopriorityqueue Q)
{
	if (Q == NULL || priorityqueue_is_empty(Q) == 1) {
		printf("ptrtopriorityqueue is NULL or empty\n");
		return;
	}

	int cnt;
	element_type Element;
	priorityqueue_for_each_element(Q, Element, cnt) {
		printf("%d ", (*(int *)Element.key));
	}
	printf("\n");
	
	return;
}


#else
#define INSERT_ARRAY	{"e", "f", "g", "d", "c", "b", "a", "x", "w", "z"}

int
cb_func(void *key1, void *key2)
{
	char *ikey1 = (char *)key1;
	char *ikey2 = (char *)key2;

	int ret = strcmp(ikey1, ikey2);
	if (ret < 0) {
		return -1;
	} else if (ret == 0) {
		return 0;
	} else {
		return 1;
	}
}

void
print_priorityqueue(ptrtopriorityqueue Q)
{
	if (Q == NULL || priorityqueue_is_empty(Q) == 1) {
		printf("ptrtopriorityqueue is NULL or empty\n");
		return;
	}

	int cnt;
	element_type Element;
	priorityqueue_for_each_element(Q, Element, cnt) {
		printf("%s ", ((char *)Element.key));
	}
	printf("\n");
	
	return;
}

#endif


void 
testpriorityQueueADT()
{
	int cnt;
#if TEST_INT
	int array[INSERT_NUM] = INSERT_ARRAY;
#else
	char array[INSERT_NUM][3] = INSERT_ARRAY;
#endif
	ptrtopriorityqueue Q = NULL;
	Q = priorityqueue_init(MAXELEMENTS, cb_func);

	if (priorityqueue_is_empty(Q) == 1) {
		printf("ptrtopriorityqueue is empty!\n\n");
	} else {
		printf("ptrtopriorityqueue is not empty!\n\n");
	}

	element_type X;
	memset(&X, 0, sizeof(element_type));
	for (cnt = 0; cnt < INSERT_NUM; cnt++) {
		X.key = &array[cnt];
#if TEST_INT
		printf("Insert %d\n", array[cnt]);
#else
		printf("Insert %s\n", array[cnt]);
#endif
		priorityqueue_push(Q, X);
		print_priorityqueue(Q);
	}

	if (priorityqueue_is_empty(Q) == 1) {
		printf("\nptrtopriorityqueue is empty!\n");
	} else {
		printf("\nptrtopriorityqueue is not empty!\n");
	}
#if 1
	printf("\nDeleteMin\n");
	for (cnt = 0; cnt < INSERT_NUM; cnt++) {
		priorityqueue_pop(Q, &X);
#if TEST_INT
		printf("Delete %d\n", (*(int *)X.key));
#else
		printf("Delete %s\n", (char *)X.key);
#endif
		print_priorityqueue(Q);
	}
#else
	printf("MakeEmpty\n");
	PriorityQueueMakeEmpty(Q);
#endif

	if (priorityqueue_is_empty(Q) == 1) {
		printf("\nptrtopriorityqueue is empty!\n");
	} else {
		printf("\nptrtopriorityqueue is not empty!\n");
	}

	priorityqueue_deinit(Q);
}


void main()
{
	testpriorityQueueADT();
}
