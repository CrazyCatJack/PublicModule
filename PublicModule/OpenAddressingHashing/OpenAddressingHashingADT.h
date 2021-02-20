// SPDX-License-Identifier: GPL-2.0-only
/*
 *	OpenAddressingHashingADT.h
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file declare OpenAddressingHashingADT structure & function prototypes
 */
#ifndef __OPENADDRESSINGHASHINGADT_H__
#define __OPENADDRESSINGHASHINGADT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLEMINSIZE 11
typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl *HashTable;
typedef int ElementType;

enum KindOfEntry {
	Empty = 0,
	Legitimate,
	Deleted
};

struct HashEntry {
	ElementType Element;
	enum KindOfEntry Info;
};

typedef struct HashEntry Cell;

struct HashTbl {
	int TableSize;
	Cell *TheCells;
};

HashTable
InitializeTable(int TableSize);

void
DestroyTable(HashTable H);

HashTable
ReHash(HashTable H);

Position
Find(HashTable H, ElementType Key);

void
Insert(HashTable H, ElementType Key);

void
Delete(HashTable H, ElementType Key);

void
PrintTable(HashTable H);

#ifdef __cplusplus
}
#endif

#endif