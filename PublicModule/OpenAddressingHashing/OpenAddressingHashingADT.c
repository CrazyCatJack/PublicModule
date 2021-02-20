// SPDX-License-Identifier: GPL-2.0-only
/*
 *	OpenAddressingHashingADT.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file define OpenAddressingHashingADT function
 */
#include "OpenAddressingHashingADT.h"

static int
PrimeJudge(int number)
{
	int cnt;
	for (cnt = 2; cnt < number; cnt++) {
		if (number % cnt == 0) {
			break;
		}
	}	

	if (cnt == number) {
		return 1;
	} else {
		return 0;
	}
}


static int 
GetNextPrime(int TableSize)
{
	if (PrimeJudge(TableSize) == 1) {
		return TableSize;
	} else {
		return GetNextPrime(++TableSize);
	}
}


static int
GetHashSubmit(ElementType Key, int TableSize)
{
	return (Key % TableSize);
}



HashTable
InitializeTable(int TableSize)
{
	if (TableSize < TABLEMINSIZE) {
		printf("TableSize is too small\n");
		return NULL;
	}

	HashTable H = NULL;
	H = (HashTable)malloc(sizeof(struct HashTbl));
	if (H == NULL) {
		return NULL;
	}
	memset(H, 0, sizeof(struct HashTbl));

	H->TableSize = GetNextPrime(TableSize);;
	H->TheCells = (Cell *)malloc(sizeof(struct HashEntry) * (H->TableSize));
	if (H->TheCells == NULL) {
		free(H);
		return NULL;
	}
	memset(H->TheCells, 0, sizeof(struct HashEntry) * (H->TableSize));
	
	return H;
}

HashTable
ReHash(HashTable H)
{
	if (H == NULL) {
		printf("H is NULL!\n");
		return NULL;
	}

	int cnt;
	
	int OldTableSize = H->TableSize;
	Cell *OldCells = H->TheCells;
	HashTable newTable = InitializeTable(2 * OldTableSize);
	for (cnt = 0; cnt < OldTableSize; cnt++) {
		if (OldCells[cnt].Info == Legitimate) {
			Insert(newTable, OldCells[cnt].Element);
		}
	}
	DestroyTable(H);
	return newTable;
}


void
DestroyTable(HashTable H)
{
	if (H == NULL) {
		printf("H is NULL!\n");
		return;
	}	

	if (H->TheCells != NULL) {
		free(H->TheCells);
	}
	if (H != NULL) {
		free(H);
	}
}

void
PrintTable(HashTable H)
{
	if (H == NULL) {
		printf("H is NULL!\n");
		return;
	}	
	
	int cnt;
	for (cnt = 0; cnt < H->TableSize; cnt++) {
		if (H->TheCells[cnt].Info == Legitimate) {
			printf("%d ", H->TheCells[cnt].Element);
		}
	}
}


Position
Find(HashTable H, ElementType Key)
{
	if (H == NULL) {
		printf("H is NULL!\n");
		return 0;
	}

	Position currentPos = GetHashSubmit(Key, H->TableSize);
	Position findSummit = 0;
	while (H->TheCells[currentPos].Info == Legitimate && H->TheCells[currentPos].Element != Key) {
		currentPos += 2 * (++findSummit) - 1;
		if (currentPos >= H->TableSize) {
			currentPos -= H->TableSize;
		}
	}

	return currentPos;
}

void
Insert(HashTable H, ElementType Key)
{
	if (H == NULL) {
		printf("H is NULL!\n");
		return;
	}

	Position insertPos = Find(H, Key);
	if (H->TheCells[insertPos].Info != Legitimate) {
		H->TheCells[insertPos].Element = Key;
		H->TheCells[insertPos].Info = Legitimate;
	}
}

void
Delete(HashTable H, ElementType Key)
{
	if (H == NULL) {
		printf("H is NULL!\n");
		return;
	}

	Position currentPos = GetHashSubmit(Key, H->TableSize);
	Position findSubmit = 0;
	while (H->TheCells[currentPos].Info != Legitimate || (H->TheCells[currentPos].Info == Legitimate && H->TheCells[currentPos].Element != Key)) {
		currentPos += 2 * (++findSubmit) - 1;
	}
	if (H->TheCells[currentPos].Info == Legitimate) {
		H->TheCells[currentPos].Info = Deleted;
	}
}



