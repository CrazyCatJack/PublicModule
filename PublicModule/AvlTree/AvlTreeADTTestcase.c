// SPDX-License-Identifier: GPL-2.0-only
/*
 *	AvlTreeADTTestcase.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file declare AvlTreeADT testcase
 */
#include "AvlTreeADT.h"

#define ROOT_ELEMENT 5
#define INSERT_NUM	10
#define INSERT_ELEMENT {2, 9, 1, 3, 4, 6, 5, 7, 0, 8}
#define DELETE_NUM	3
#define DELETE_ELEMENT {3, 5, 7}

void testAVLTree()
{
	int cnt;
	int insertArray[] = INSERT_ELEMENT;
	int delArray[] = DELETE_ELEMENT;
	Position pHead = NULL;

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

	MakeEmpty(pHead);
}

void main()
{
	testAVLTree();
}

