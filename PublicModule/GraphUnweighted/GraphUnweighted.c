// SPDX-License-Identifier: GPL-2.0-only
/*
 *	GraphUnweighted.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file define GraphUnweighted function
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "GraphUnweighted.h"

typedef QuickListNode_T* AdjacencyList;
#define VERTEXNUM	7
#define START_VERTEX	3
#define VERTEX_KNOWN	1
#define VERTEX_UNKNOWN		0

AdjacencyList*
AdjacencyListCreate(int VertexNum)
{
	AdjacencyList *pVlist = (AdjacencyList *)malloc(sizeof(AdjacencyList) * (VertexNum + 1));
	if (pVlist == NULL)
	{
		printf("AdjacencyList create failed!\n");
		return NULL;
	}
	memset(pVlist, 0, sizeof(AdjacencyList) * (VertexNum + 1));

	int cnt;
	for (cnt = 1; cnt <= VertexNum; cnt++)
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
	for (cnt = 1; cnt <= VertexNum; cnt++)
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
AdjacencyListAddNodetoTail(QuickListNode_T *QueueList, int value1)
{
	QuickListNode_T *newNode = NULL;
	newNode = QuickListCreateNode(value1, 0, 0, NULL);
	QuickListAddNodetoTail(QueueList, newNode);
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
	for (cnt = 1; cnt <= VertexNum; cnt++)
	{
		if (oriAdjacencyList[cnt] == NULL)
		{
			printf("Error: oriAdjacencyList[%d] = NULL\n", cnt);
			return;
		}
		printf("Start print oriAdjacencyList[%d]:\n", cnt);
		QuickListPrint(oriAdjacencyList[cnt]);
		printf("It's know=%d, distance=%d, path=%d\n\n", (oriAdjacencyList[cnt])->value1, (oriAdjacencyList[cnt])->value2, (oriAdjacencyList[cnt])->value3);
	}
}

void
AdjacencyListInitialVertex(AdjacencyList *oriAdjacencyList)
{
	/* v1 */
	AdjacencyListAddNodetoTail(oriAdjacencyList[1], 2);
	AdjacencyListAddNodetoTail(oriAdjacencyList[1], 4);

	/* v2 */
	AdjacencyListAddNodetoTail(oriAdjacencyList[2], 4);
	AdjacencyListAddNodetoTail(oriAdjacencyList[2], 5);

	/* v3 */
	AdjacencyListAddNodetoTail(oriAdjacencyList[3], 1);
	AdjacencyListAddNodetoTail(oriAdjacencyList[3], 6);

	/* v4 */
	AdjacencyListAddNodetoTail(oriAdjacencyList[4], 6);
	AdjacencyListAddNodetoTail(oriAdjacencyList[4], 7);
	AdjacencyListAddNodetoTail(oriAdjacencyList[4], 3);
	AdjacencyListAddNodetoTail(oriAdjacencyList[4], 5);

	/* v5 */
	AdjacencyListAddNodetoTail(oriAdjacencyList[5], 7);

	/* v6 */
	

	/* v7 */
	AdjacencyListAddNodetoTail(oriAdjacencyList[7], 6);
}


void
AdjacencyListInitialDisAndPath(AdjacencyList* adList,          QuickListNode_T *QueueList)
{
	int StartVertex;
	QuickListNode_T *fatherNode = NULL;
	QuickListNode_T *node = NULL;
	QuickListNode_T *childNode = NULL;
	
	while (QuickListGetNodeSum(QueueList) > 0)
	{
		fatherNode = QuickListGetNodefromTail(QueueList);
		if (fatherNode != NULL)
		{
			StartVertex = fatherNode->value1;
			QuickListDeleteNodefromTail(QueueList);
		}
		
		if (adList[StartVertex]->value1 == VERTEX_UNKNOWN)
			adList[StartVertex]->value1 = VERTEX_KNOWN;	

		printf("StartVertex=%d\n", StartVertex);
		QuickList_for_each_entry(adList[StartVertex], node)
		{
			if (adList[node->value1]->value1 == VERTEX_UNKNOWN)
			{
				adList[node->value1]->value1 = VERTEX_KNOWN;
				adList[node->value1]->value2 = adList[StartVertex]->value2 + 1;
				adList[node->value1]->value3 = StartVertex;
				childNode = QuickListCreateNode(node->value1, 0, 0, NULL);
				QuickListAddNodetoHead(QueueList, childNode);
				printf("subnode: %d is unknown, distance=%d\n", node->value1, adList[node->value1]->value2);
			}
		}
	}
}

void
AdjacencyListInitial(AdjacencyList *oriAdjacencyList, int StartVertex, QuickListNode_T *QueueList)
{
	AdjacencyListInitialVertex(oriAdjacencyList);
	AdjacencyListAddNodetoTail(QueueList, StartVertex);
	AdjacencyListInitialDisAndPath(oriAdjacencyList, QueueList);
}


void
main(int argc, char *argv[])
{
	QuickListNode_T *QueueList = NULL;
	AdjacencyList* adList = NULL;

	QueueList = QuickListCreateList();
	adList = AdjacencyListCreate(VERTEXNUM);
	AdjacencyListInitial(adList, START_VERTEX, QueueList);
	AdjacencyListPrint(adList, VERTEXNUM);
	AdjacencyListDestroy(adList, VERTEXNUM);
	QuickListDeleteList(QueueList);
}

