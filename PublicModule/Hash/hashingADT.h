// SPDX-License-Identifier: GPL-2.0-only
/*
 *	hashingADT.h
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file declare hashingADT structure & function prototypes
 */
#ifndef __HASHINGADT_H__
#define __HASHINGADT_H__

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stackADT.h"

#define MINTABLESIZE 11
struct HashTbl;
typedef struct HashTbl *HashTable;

typedef Stack List;
struct HashTbl
{
    int TableSize;
    List *TheLists;
};

HashTable
InitializeTable(int TableSize);

PtrToNode
Find(ElementType Key, HashTable H);

void
Insert(ElementType Key, HashTable H);

void
Delete(ElementType Key, HashTable H);

void
DestroyTable(HashTable H);

void
PrintTable(HashTable H);


#ifdef __cplusplus
}
#endif

#endif