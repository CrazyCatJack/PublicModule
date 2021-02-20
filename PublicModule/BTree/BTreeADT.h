// SPDX-License-Identifier: GPL-2.0-only
/*
 *	BTreeADT.h
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file declare BTreeADT structure & function prototypes
 */
#ifndef __BTREEADT_H__
#define __BTREEADT_H__

#ifdef __cpluscplus
extern "C" {
#endif

#define BTREEORDER	3

typedef int ElementType;

typedef struct BTreeNode {
	int childNum;
	struct BTreeNode *father;
	struct BTreeNode **PtrChildArray;	// size BTREEORDER
	int *childMinVal;	// size BTREEORDER - 1 
	ElementType *keyVal;	// size BTREEORDER
} BTreeNode_T;

typedef struct BTreeNode *PtrTreeNode;


void
MakeEmpty(PtrTreeNode BTreeHead);

PtrTreeNode
Find(PtrTreeNode BTreeHead, ElementType X);

PtrTreeNode
FindMin(PtrTreeNode BTreeHead);

PtrTreeNode
FindMax(PtrTreeNode BTreeHead);

PtrTreeNode
Delete(PtrTreeNode BTreeHead, ElementType X);

PtrTreeNode
Insert(PtrTreeNode BTreeHead, ElementType X);



#ifdef __cpluscplus
}
#endif

#endif