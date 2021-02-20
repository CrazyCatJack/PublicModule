// SPDX-License-Identifier: GPL-2.0-only
/*
 *	OpenAddressingHashingADTTestcase.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file declare OpenAddressingHashingADT testcase
 */
#include "OpenAddressingHashingADT.h"

#define TABLESIZE 20
#define INSERT_CNT 10
#define INSERT_ARRAY {1, 11, 21, 31, 22, 23, 26, 0, 14, 27}

void testOpenAddressingHashingADT()
{
	int insertArray[INSERT_CNT] = INSERT_ARRAY;
	HashTable H = NULL;
	H = InitializeTable(TABLESIZE);

	int cnt;
	printf("Start insert:\n");
	for (cnt = 0; cnt < INSERT_CNT; cnt++) {
		Insert(H, insertArray[cnt]);
		PrintTable(H);
		printf("\n");
	}

#if 0
	printf("Start delete:\n");
	for (cnt = 0; cnt < INSERT_CNT; cnt++) {
		Delete(H, insertArray[cnt]);
		PrintTable(H);
		printf("\n");
	}
	DestroyTable(H);
#else
	printf("Start rehash\n");
	HashTable newTable = ReHash(H);
	PrintTable(newTable);
	printf("\n");
	DestroyTable(newTable);
#endif
}

void main()
{
	testOpenAddressingHashingADT();
}