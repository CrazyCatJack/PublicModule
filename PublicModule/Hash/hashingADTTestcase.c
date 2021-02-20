// SPDX-License-Identifier: GPL-2.0-only
/*
 *	hashingADTTestcase.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file declare hashingADT testcase
 */
#include "hashingADT.h"

#define TABLESIZE 12
#define INSERT_CNT	8
#define INSERT_ARRAY	{13, 26, 23, 33, 43, 45, 66, 39}
#define DELETE_CNT	3
#define DELETE_ARRAY	{26, 33, 43}

void testhashingADT()
{
	int cnt;
	HashTable H = NULL;
	int insertArray[] = INSERT_ARRAY;
	int deleteArray[] = DELETE_ARRAY;
	H = InitializeTable(TABLESIZE);

	printf("Start insert:\n");
	for (cnt = 0; cnt < INSERT_CNT; cnt++) {
		Insert(insertArray[cnt], H);
		PrintTable(H);
	}

	printf("Start delete:\n");
	for (cnt = 0; cnt < DELETE_CNT; cnt++) {
		Delete(deleteArray[cnt], H);
		PrintTable(H);
	}

	DestroyTable(H);
}

void main()
{
	testhashingADT();
}
