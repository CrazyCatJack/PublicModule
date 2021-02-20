// SPDX-License-Identifier: GPL-2.0-only
/*
 *	BinarySearchTreeTestcase.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file declare BinarySearchTreeADT testcase
 */

#include "BinarySearchTreeADT.h"

#define ROOT_ELEMENT 5
#define INSERT_NUM	10
#define INSERT_ELEMENT {2, 9, 1, 3, 4, 6, 5, 7, 0, 8}
#define DELETE_NUM	3
#define DELETE_ELEMENT {3, 5, 7}

void testSrchTree()
{
	int cnt;
	int insertArray[] = INSERT_ELEMENT;
	int delArray[] = DELETE_ELEMENT;
	PtrToTreeHead pHead = NULL;

	/* create tree head */
	pHead = CreateTreeNode();
	if (pHead == NULL) {
		printf("Create tree node fail\n");
		return;
	}
	pHead->Element = ROOT_ELEMENT;

	/* start insert tree node */
	for (cnt = 0; cnt < INSERT_NUM; cnt++) {
		pHead = Insert(pHead, insertArray[cnt]);
		printf("insert:%d\n", insertArray[cnt]);
		PrintTree(pHead);
		printf("\n\n");
	}

	/* start delete tree node */
	for (cnt = 0; cnt < DELETE_NUM; cnt++) {
		pHead = Delete(pHead, delArray[cnt]);
		printf("delete:%d\n", delArray[cnt]);
		PrintTree(pHead);
		printf("\n\n");
	}

	DrstroyTree(pHead);
}

void main()
{
	testSrchTree();
}
