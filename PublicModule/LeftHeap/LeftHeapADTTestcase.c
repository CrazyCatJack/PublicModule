// SPDX-License-Identifier: GPL-2.0-only
/*
 *	LeftHeapADTTestcase.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file declare LeftHeapADT testcase
 */
#include "LeftHeapADT.h"

#define ARRAY {2, 10, 33, 4, 1, 8, 6, 7, 44, 30}
#define ORIGIN_VALUE 0
static void
testLeftHeapADT()
{
	int cnt;
	int array[] = ARRAY;
	
	PriorityQueue H = NULL;
	H = Initialize(ORIGIN_VALUE);

	for (cnt = 0; cnt < sizeof(array) / sizeof(array[0]); cnt++) {
		H = Insert1(H, array[cnt]);
		PrintHeap(H);
		printf("\n");
	}

	for (cnt = 0; cnt < sizeof(array) / sizeof(array[0]); cnt++) {
		H = DeleteMin1(H);
		PrintHeap(H);
		printf("\n");
	}	
	
	Destroy(H);
}

void main()
{
	testLeftHeapADT();
}