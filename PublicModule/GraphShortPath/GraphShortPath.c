// SPDX-License-Identifier: GPL-2.0-only
/*
 *	GraphShortPath.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file define GraphShortPath function
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "GraphShortPath.h"

typedef QuickListNode_T* AdjacencyList;
#define VERTEXNUM	7

AdjacencyList*
AdjacencyListCreate(int VertexNum)
{
	AdjacencyList *pVlist = (AdjacencyList *)malloc(sizeof(AdjacencyList) * VertexNum);
	if (pVlist == NULL)
	{
		printf("AdjacencyList create failed!\n");
		return NULL;
	}
	memset(pVlist, 0, sizeof(AdjacencyList) * VertexNum);

	int cnt;
	for (cnt = 0; cnt < VertexNum; cnt++)
	{
		pVlist[cnt] = QuickListCreateList();
		if (pVlist[cnt] == NULL)
		{
			printf("quick list create failed. start free\n");
			
			int freeCnt;
			for (freeCnt = 0; freeCnt < cnt; freeCnt++)
			{
				if (pVlist[freeCnt] != NULL)
				{
					free(pVlist[freeCnt]);
				}
			}
			if (pVlist != NULL)
			{
				free(pVlist);
			}
			printf("free finish\n");
			return NULL;
		}
	}

	return pVlist;
}

void
AdjacencyListDestroy(AdjacencyList* oriAdjacencyList, int VertexNum)
{
	if (oriAdjacencyList == NULL)
	{
		printf("oriAdjacencyList = NULL\n");
		return;		
	}

	int cnt;
	for (cnt = 0; cnt < VertexNum; cnt++)
	{
		if (oriAdjacencyList[cnt] == NULL)
		{
			printf("oriAdjacencyList[%d] = NULL\n", cnt);
		}
		else
		{
			QuickListDeleteList(oriAdjacencyList[cnt]);
		}
	}

	if (oriAdjacencyList != NULL)
	{
		free(oriAdjacencyList);
	}
}

void
AdjacencyListAddNodetoTail(AdjacencyList *oriAdjacencyList, int oriAdjacencyListSuffix, int value1)
{
	QuickListNode_T *newNode = NULL;
	newNode = QuickListCreateNode(value1, 0, NULL);
	QuickListAddNodetoTail(oriAdjacencyList[oriAdjacencyListSuffix], newNode);
	(oriAdjacencyList[value1 - 1]->value2)++;
}


void
AdjacencyListPrint(AdjacencyList *oriAdjacencyList, int VertexNum)
{
	if (oriAdjacencyList == NULL)
	{
		printf("Error: oriAdjacencyList = NULL\n");
		return;
	}

	int cnt;
	for (cnt = 0; cnt < VertexNum; cnt++)
	{
		if (oriAdjacencyList[cnt] == NULL)
		{
			printf("Error: oriAdjacencyList[%d] = NULL\n", cnt);
			return;
		}
		printf("Start print oriAdjacencyList[%d]:\n", cnt);
		QuickListPrint(oriAdjacencyList[cnt]);
		printf("It's indegree:%d\n\n", (oriAdjacencyList[cnt])->value2);
	}
}

void
AdjacencyListInitialVertex(AdjacencyList *oriAdjacencyList)
{
	AdjacencyListAddNodetoTail(oriAdjacencyList, 0, 2);
	AdjacencyListAddNodetoTail(oriAdjacencyList, 0, 4);
	AdjacencyListAddNodetoTail(oriAdjacencyList, 0, 3);
	
	AdjacencyListAddNodetoTail(oriAdjacencyList, 1, 4);
	AdjacencyListAddNodetoTail(oriAdjacencyList, 1, 5);
	
	AdjacencyListAddNodetoTail(oriAdjacencyList, 2, 6);
	
	AdjacencyListAddNodetoTail(oriAdjacencyList, 3, 6);
	AdjacencyListAddNodetoTail(oriAdjacencyList, 3, 7);
	AdjacencyListAddNodetoTail(oriAdjacencyList, 3, 3);
	
	AdjacencyListAddNodetoTail(oriAdjacencyList, 4, 4);
	AdjacencyListAddNodetoTail(oriAdjacencyList, 4, 7);

	AdjacencyListAddNodetoTail(oriAdjacencyList, 6, 6);
}

void
AdjacencyListInitialIndegreeStack(AdjacencyList *oriAdjacencyList, int VertexNum, Stack s)
{
	int cnt;
	for (cnt = 0; cnt < VertexNum; cnt++)
	{
		if (oriAdjacencyList[cnt] != NULL && (oriAdjacencyList[cnt])->value2 == 0)
		{
			Push(cnt, s);
		}
	}
}


void
AdjacencyListInitial(AdjacencyList *oriAdjacencyList, int VertexNum, Stack s)
{
	int cnt;
	for (cnt = 0; cnt < VertexNum; cnt++)
	{
		(oriAdjacencyList[cnt])->value1 = cnt + 1;
	}
	AdjacencyListInitialVertex(oriAdjacencyList);
	AdjacencyListInitialIndegreeStack(oriAdjacencyList, VertexNum, s);
}


void
TopSort(AdjacencyList *oriAdjacencyList, int VertexNum, Stack s)
{
	int deleteVertex;
	int Counter = 0;

	if (oriAdjacencyList == NULL)
	{
		printf("Error: oriAdjacencyList = NULL\n");
		return;
	}

	while (!IsEmpty(s))
	{
		Counter++;
		deleteVertex = Top(s);
		Pop(s);
		printf("%d ", deleteVertex + 1);
		AdjacencyList pHead = oriAdjacencyList[deleteVertex];
		AdjacencyList tmp = pHead->next;
		while (tmp != pHead)
		{
			if (--((oriAdjacencyList[tmp->value1 - 1])->value2) == 0)
			{
				Push(tmp->value1 - 1, s);
			}
			tmp = tmp->next;
		}
	}
	printf("\n");
	
	if (Counter != VertexNum)
	{
		printf("Counter = %d, Graph has a cycle\n", Counter);
	}
}



void
main(int argc, char *argv[])
{
	Stack stk = CreateStack();
	AdjacencyList* adList = NULL;
	adList = AdjacencyListCreate(VERTEXNUM);
	
	AdjacencyListInitial(adList, VERTEXNUM, stk);
	AdjacencyListPrint(adList, VERTEXNUM);
	TopSort(adList, VERTEXNUM, stk);
	AdjacencyListDestroy(adList, VERTEXNUM);

	DistroyStack(stk);
}
