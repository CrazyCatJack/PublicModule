// SPDX-License-Identifier: GPL-2.0-only
/*
 *	QuickListTestcase.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file declare QuickList testcase
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "QuickList.h"

#define QUICKLIST_NODE_NUM 10

int main(int argc, char *argv)
{
	int ret = -1;
	int nodeSum = -1;
	
	/* initialize userdata array */
	int userdata[QUICKLIST_NODE_NUM];
	int cnt;
	for (cnt = 0; cnt < QUICKLIST_NODE_NUM; cnt++) {
		userdata[cnt] = cnt;
	}
	printf("Start QuickList test\n");
	
	/* initialize QuickList */
	QuickListNode_T *pHead = QuickListCreateList();
	if (pHead == NULL) {
		printf("create QuickList fail!\n");
		goto __exit;
	}

	/* add node to QuickList */
	QuickListNode_T *newNode = NULL;
	for (cnt = 0; cnt < QUICKLIST_NODE_NUM; cnt++) {
		newNode = QuickListCreateNode(&userdata[cnt]);
		if (newNode == NULL) {
			printf("create QuickList node fail!\n");
			goto __exit;
		}
		if (0 != QuickListAddNodetoTail(newNode, pHead)) {
			printf("add QuickList node to list fail!\n");
			goto __exit;
		}
		if (-1 == (nodeSum = QuickListGetNodeSum(pHead))) {
			printf("get QuickList node sum fail!\n");
			goto __exit;
		}
		printf("add userdata(%d) node, node sum = %d\n", userdata[cnt], nodeSum);
	}

	/* print QuickList */
	int *recvuserdata = NULL;
	QuickListNode_T *node = NULL;
	printf("after add, print QuickList:\n");
	QuickList_for_each_entry(pHead, node)
	{
		recvuserdata = QuickList_entry(int, node);
		printf("%d ", *recvuserdata);
	}
	printf("\n");
	recvuserdata = NULL;
	node = NULL;
	ret = 0;
__exit:

	#if 0
	/* make QuickList empty */
	if (0 != QuickListMakeEmptyList(pHead)) {
		printf("QuickList delete list fail!\n");
		ret = -1;
	}
	if (-1 == (nodeSum = QuickListGetNodeSum(pHead))) {
		printf("get QuickList node sum fail!\n");
		ret = -1;
	}
	printf("after make list empty, node sum = %d\n", nodeSum);
	#else
	/* delete one node from head */
	if (0 != QuickListDeleteNodefromHead(pHead)) {
		printf("QuickList delete node fail!\n");
		ret = -1;
	}
	printf("after delete node from head, print QuickList:\n");
	QuickList_for_each_entry(pHead, node)
	{
		recvuserdata = QuickList_entry(int, node);
		printf("%d ", *recvuserdata);
	}
	printf("\n");
	if (-1 == (nodeSum = QuickListGetNodeSum(pHead))) {
		printf("get QuickList node sum fail!\n");
		ret = -1;
	}
	printf("after delete, node sum = %d\n", nodeSum);
	#endif

	/* delete QuickList */
	if (0 != QuickListDeleteList(pHead)) {
		printf("delete QuickList fail!\n");
		ret = -1;
	} else {
		pHead = NULL;
	}
	
	if (ret == 0) {
		printf("\ntest QuickList success!\n");
	} else {
		printf("\ntest QuickList fail!\n");
	}
	return ret;
}
