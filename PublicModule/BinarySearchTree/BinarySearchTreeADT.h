// SPDX-License-Identifier: GPL-2.0-only
/*
 *	BinarySearchTreeADT.h
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file declare BinarySearchTreeADT structure & function prototypes
 */
#ifndef __BINARYSEARCHTREEADT_H
#define __BINARYSEARCHTREEADT_H


#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "treeADT.h"



void
MakeEmpty(PtrToTreeHead treeHead);

PtrToTreeHead
Find(PtrToTreeHead treeHead, ElementType Element);

PtrToTreeHead
FindMin(PtrToTreeHead treeHead);

PtrToTreeHead
FindMax(PtrToTreeHead treeHead);

PtrToTreeHead
Insert(PtrToTreeHead treeHead, ElementType element);

PtrToTreeHead
Delete(PtrToTreeHead T, ElementType element);


#ifdef __cplusplus
}
#endif


#endif

