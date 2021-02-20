// SPDX-License-Identifier: GPL-2.0-only
/*
 *	AvlTreeADT.h
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file declare AvlTreeADT structure & function prototypes
 */
#ifndef _AVLTREEADT_H_
#define _AVLTREEADT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElementType;
struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;


struct AvlNode {
    ElementType Element;
    AvlTree Left;
    AvlTree Right;
    int Height;
};


void MakeEmpty(AvlTree T);
Position Find(AvlTree T, ElementType X);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree Insert(AvlTree T, ElementType X);
AvlTree Delete(AvlTree T, ElementType X);
void PrintTree(AvlTree root);


#ifdef __cpluscplus
}
#endif

#endif
