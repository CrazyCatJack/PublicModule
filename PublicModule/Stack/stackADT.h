// SPDX-License-Identifier: GPL-2.0-only
/*
 *	stackADT.h
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file declare stackADT structure & function prototypes
 */
#ifndef __STACKADT_H
#define __STACKADT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "treeADT.h"

typedef int ElementType;
struct node;
typedef struct node *PtrToNode;
typedef PtrToNode Stack;

struct node {
    ElementType Element;
    PtrToNode Next;
};

Stack CreateStack(void);

void MakeEmpty(Stack s);

int Push(ElementType X, Stack s);

void DeleteNode(ElementType X, Stack s);

void Pop(Stack s);

ElementType Top(Stack s);

int IsEmpty(Stack s);

void DistroyStack(Stack s);

void PrintStack(Stack s);

#ifdef __cplusplus
}
#endif


#endif
