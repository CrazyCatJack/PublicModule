// SPDX-License-Identifier: GPL-2.0-only
/*
 *	hashingADT.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file define hashingADT function
 */
#include "hashingADT.h"

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
    if (TableSize < MINTABLESIZE) {
        printf("TableSize too small\n");
        return NULL;
    }
    
    HashTable H = NULL;
    H = (HashTable)malloc(sizeof(struct HashTbl));
    if (H == NULL) {
        printf("HashTable malloc failed\n");
        return NULL;
    }
    memset(H, 0, sizeof(struct HashTbl));
    
    H->TableSize = GetNextPrime(TableSize);
    H->TheLists = (List *)malloc(sizeof(List) * H->TableSize);
    if (H->TheLists == NULL) {
        printf("HashTable TheLists malloc failed\n");
        free(H);
        H = NULL;
        return NULL;
    }
    memset(H->TheLists, 0, sizeof(List) * H->TableSize);
    
    int cnt, cnt2;
    for (cnt = 0; cnt < H->TableSize; cnt++) {
        H->TheLists[cnt] = CreateStack();
        if (H->TheLists[cnt] == NULL) {
            printf("H->TheLists[%d]malloc failed\n", cnt);
            for (cnt2 = 0; cnt2 < cnt; cnt2++) {
                if (H->TheLists[cnt2] != NULL) {
                    DistroyStack(H->TheLists[cnt2]);
                    H->TheLists[cnt2] = NULL;
                }
            }
            if (H->TheLists != NULL) {
                free(H->TheLists);
                H->TheLists = NULL;
            }
            if (H != NULL) {
                free(H);
                H = NULL;
            }
            return NULL;
        }
    }
    
    return H;
}


PtrToNode
Find(ElementType Key, HashTable H)
{
    if (H == NULL) {
        printf("ERROR: H is NULL\n");
        return NULL;
    }
    
    PtrToNode tmp = NULL;
	tmp = H->TheLists[GetHashSubmit(Key, H->TableSize)]->Next;
	while (tmp != NULL && tmp->Element != Key) {
		tmp = tmp->Next;
	}
    return tmp;
}

void
Insert(ElementType Key, HashTable H)
{
	if (H == NULL) {
		printf("HashTable is NULL\n");
		return;
	}
	
	if (0 != Push(Key, H->TheLists[GetHashSubmit(Key, H->TableSize)])) {
		printf("Insert Key failed\n");
	}
}

void
Delete(ElementType Key, HashTable H)
{
	if (H == NULL) {
		printf("HashTable is NULL\n");
		return;
	}

	DeleteNode(Key, H->TheLists[GetHashSubmit(Key, H->TableSize)]);
}

void
DestroyTable(HashTable H)
{
	if (H == NULL) {
		return;
	}

	int cnt;
	if (H->TheLists != NULL) {
		for (cnt = 0; cnt < H->TableSize; cnt++) {
			if (H->TheLists[cnt] != NULL) {
				DistroyStack(H->TheLists[cnt]);
				H->TheLists[cnt] = NULL;
			}
		}
		free(H->TheLists);
		H->TheLists = NULL;
	}
	if (H != NULL) {
		free(H);
		H = NULL;
	}
}


void
PrintTable(HashTable H)
{
	if (H == NULL) {
		return;
	}

	int cnt;
	for (cnt = 0; cnt < H->TableSize; cnt++) {
		PrintStack(H->TheLists[cnt]);
		printf("\n");
	}
}
