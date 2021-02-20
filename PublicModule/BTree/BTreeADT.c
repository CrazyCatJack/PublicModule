// SPDX-License-Identifier: GPL-2.0-only
/*
 *	BTreeADT.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file define BTreeADT function
 */
#include "BTreeADT.h"

void
MakeEmpty(PtrTreeNode BTreeHead)
{
	if (BTreeHead == NULL) {
		return;
	}
	
	int cnt;
	for (cnt = 0; cnt < BTreeHead->childNum; cnt++) {
		if (BTreeHead->PtrChildArray[cnt] != NULL) {
			MakeEmpty(BTreeHead->PtrChildArray[cnt]);
		}
	}
	if (BTreeHead != NULL) {
		free(BTreeHead);
	}
}

PtrTreeNode
Find(PtrTreeNode BTreeHead, ElementType X)
{
	if (BTreeHead == NULL) {
		return NULL;
	}

	int cnt;
	if (BTreeHead->PtrChildArray == NULL) {
		for (cnt = 0; cnt < BTreeHead->childNum; cnt++) {
			if (X < BTreeHead->keyVal[cnt]) {
				return NULL;
			} else if (X == BTreeHead->keyVal[cnt]) {
				return PtrTreeNode;
			}
		}
		return NULL;
	}

	
	for (cnt = 0; cnt < BTreeHead->childNum - 1; cnt++) {
		if (X < BTreeHead->childMinVal[cnt]) {
			return Find(BTreeHead->PtrChildArray[cnt]);
		} else if (X == BTreeHead->childMinVal[cnt]) {
			return Find(BTreeHead->PtrChildArray[cnt + 1]);
		}
	}
	return Find(BTreeHead->PtrChildArray[cnt]);;
}

PtrTreeNode
FindMin(PtrTreeNode BTreeHead)
{
	if (BTreeHead == NULL) {
		return NULL;
	}
	
	if (BTreeHead->PtrChildArray == NULL) {
		return BTreeHead;
	} else {
		return FindMin(BTreeHead->PtrChildArray[0]);
	}
}

PtrTreeNode
FindMax(PtrTreeNode BTreeHead)
{
	if (BTreeHead == NULL) {
		return NULL;
	}

	if (BTreeHead->PtrChildArray == NULL) {
		return BTreeHead;
	} else {
		int cnt;
		for (cnt = 0; cnt < BTreeHead->childNum; cnt++) {
			if (BTreeHead->PtrChildArray[cnt] == NULL) {
				break;
			}
		}

		if (cnt == BTreeHead->childNum) {
			return FindMax(BTreeHead->PtrChildArray[BTreeHead->childNum - 1]);
		} else {
			return FindMax(BTreeHead->PtrChildArray[cnt]);
		}
	}
}


static void ArrayInsert(ElementType *array, int arrayNum, int MaxNum, ElementType X)
{
	int cnt;
	int cnt2;
	for (cnt = 0; cnt < arrayNum; cnt++) {
		if (X < array[cnt]) {
			for (cnt2 = cnt + 1; cnt2 < arrayNum; cnt2++) {
				array[cnt2] = array[cnt];
			}
			array[cnt] = X;
			break;
		}
	}
	if (cnt == arrayNum && arrayNum < MaxNum) {
		array[cnt] = X;
	}
}


PtrTreeNode
Delete(PtrTreeNode BTreeHead, ElementType X)
{
	if (BTreeHead == NULL) {
		return NULL;
	}

}

PtrTreeNode
Insert(PtrTreeNode BTreeHead, ElementType X)
{
	if (BTreeHead == NULL) {
		
	}

	if (BTreeHead->PtrChildArray == NULL) {
		/* could insert node to current node */
		if (BTreeHead->childNum + 1 <= BTREEORDER) {
			ArrayInsert(BTreeHead->keyVal, BTreeHead->childNum, BTREEORDER, X);
			BTreeHead->childNum += 1;
		} else {
		/* could not insert node to current node */
			if (BTreeHead->father->childNum + 1 <= BTREEORDER) {
				PtrTreeNode newChild = NULL;
				newChild = (PtrTreeNode)malloc(sizeof(struct BTreeNode));
				if (newChild == NULL) {
					printf("newChild malloc failed\n");
				}
				memset(newChild, 0, sizeof(struct BTreeNode));
				newChild->father = BTreeHead->father;
				newChild->PtrChildArray 
			} else {
				return Insert(BTreeHead->father, X);
			}
		}
	}
	
	int cnt;
	for (cnt = 0; cnt < BTreeHead->childNum; cnt++) {
		if (X < BTreeHead->childMinVal[cnt]) {
			BTreeHead->PtrChildArray[cnt] = Insert(BTreeHead->PtrChildArray[cnt], X);
			break;
		} else if (X == BTreeHead->childMinVal[cnt])	{
			BTreeHead->PtrChildArray[cnt + 1] = Insert(BTreeHead->PtrChildArray[cnt + 1], X);
			break;
		}	
	}
	if (cnt == BTreeHead->childNum) {
		BTreeHead->PtrChildArray[BTreeHead->childNum - 1] = Insert(BTreeHead->PtrChildArray[BTreeHead->childNum - 1], X);
	}
	return BTreeHead;
}

