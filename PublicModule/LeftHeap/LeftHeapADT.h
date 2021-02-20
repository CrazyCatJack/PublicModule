// SPDX-License-Identifier: GPL-2.0-only
/*
 *	LeftHeapADT.h
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file declare LeftHeapADT structure & function prototypes
 */
#ifndef __LEFTHEAPADT_H__
#define __LEFTHEAPADT_H__

#ifdef __cpluscplus
extern "C" {
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef int ElementType;
struct TreeNode;
typedef struct TreeNode *PriorityQueue;

struct TreeNode {
	ElementType Element;
	PriorityQueue Left;
	PriorityQueue Right;
	int Npl;
};

#define Insert(X, H) (H = Insert1((X), H))
#define DeleteMin(H) do {ElementType Q = FindMin(H); DeleteMin1(H); return Q;} while(1)

PriorityQueue
Initialize(ElementType X);

PriorityQueue
Merge(PriorityQueue H1, PriorityQueue H2);

PriorityQueue
Insert1(PriorityQueue H, ElementType X);

int
IsEmpty(PriorityQueue H);

PriorityQueue
DeleteMin1(PriorityQueue H);

ElementType
FindMin(PriorityQueue H);

void
Destroy(PriorityQueue H);

void
PrintHeap(PriorityQueue H);


#ifdef __cplusplus
}
#endif

#endif
