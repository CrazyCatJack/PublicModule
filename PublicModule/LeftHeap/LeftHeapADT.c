// SPDX-License-Identifier: GPL-2.0-only
/*
 *	LeftHeapADT.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file define LeftHeapADT function
 */
#include "LeftHeapADT.h"

static void
SwapChild(PriorityQueue H)
{
	PriorityQueue tmp;
	tmp = H->Left;
	H->Left = H->Right;
	H->Right = tmp;
	H->Npl = H->Right->Npl + 1;
}

PriorityQueue
Merge1(PriorityQueue H1, PriorityQueue H2)
{
	if (H1->Left == NULL) {
		H1->Left = H2;
	} else {
		H1->Right = Merge(H1->Right, H2);
		if (H1->Left->Npl < H1->Right->Npl) {
			SwapChild(H1);
		}
		H1->Npl = H1->Right->Npl + 1;
	}
	return H1;
}



PriorityQueue
Merge(PriorityQueue H1, PriorityQueue H2)
{
	if (H1 == NULL) {
		return H2;
	}
	if (H2 == NULL) {
		return H1;
	}

	if (H1->Element < H2->Element) {
		return Merge1(H1, H2);
	} else {
		return Merge1(H2, H1);
	}
}


PriorityQueue
Insert1(PriorityQueue H, ElementType X)
{
	if (H == NULL) {
		return NULL;
	}

	PriorityQueue SingleNode;
	SingleNode = (PriorityQueue)malloc(sizeof(struct TreeNode));
	if (SingleNode == NULL) {
		printf("SingleNode malloc failed\n");
	} else {
		memset(SingleNode, 0, sizeof(struct TreeNode));
		SingleNode->Element = X;
		SingleNode->Npl = 0;
		SingleNode->Left = SingleNode->Right = NULL;
		H = Merge(SingleNode, H);
	}

	return H;
}

int
IsEmpty(PriorityQueue H)
{
	return (H->Left == NULL && H->Right == NULL);
}


PriorityQueue
DeleteMin1(PriorityQueue H)
{
	if (H == NULL || IsEmpty(H)) {
		return H;
	}

	PriorityQueue Left, Right;
	Left = H->Left;
	Right = H->Right;
	free(H);
	return Merge(Left, Right);
}

ElementType
FindMin(PriorityQueue H)
{
	if (H == NULL) {
		printf("H is NULL\n");
	}
	return H->Element;
}

PriorityQueue
Initialize(ElementType X)
{
	PriorityQueue H = NULL;
	H = (PriorityQueue)malloc(sizeof(struct TreeNode));
	memset(H, 0, sizeof(struct TreeNode));

	H->Element = X;
	H->Left = H->Right = NULL;
	H->Npl = 0;

	return H;
}

void
Destroy(PriorityQueue H)
{
	if (H->Left) {
		Destroy(H->Left);
	}
	if (H->Right) {
		Destroy(H->Right);
	}
	if (H) {
		free(H);
	}
}

void
PrintHeap(PriorityQueue H)
{
	if (H == NULL) {
		return;
	}

	if (H->Left) {
		PrintHeap(H->Left);
	}
	if (H->Right) {
		PrintHeap(H->Right);
	}
	if (H) {
		printf("%d ", H->Element);
	}
}



