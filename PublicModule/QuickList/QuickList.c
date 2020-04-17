// SPDX-License-Identifier: GPL-2.0-only
/*
 *	QuickList.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file define QuickList function
 */


#include "QuickList.h"

QuickListNode_T *QuickListCreateList()
{
	QuickListNode_T *pHead = NULL;
	pHead = (QuickListNode_T *)malloc(sizeof(QuickListNode_T));
	memset(pHead, 0, sizeof(QuickListNode_T));
	pHead->next = pHead;
	pHead->previous = pHead;

	return pHead;
}

QuickListNode_T *QuickListCreateNode(void *userdata)
{
	QuickListNode_T *newNode = NULL;
	newNode = (QuickListNode_T *)malloc(sizeof(QuickListNode_T));
	memset(newNode, 0, sizeof(QuickListNode_T));
	newNode->userdata = userdata;
	newNode->next = newNode;
	newNode->previous = newNode;

	return newNode;
}


int QuickListGetNodeSum(QuickListNode_T *pHead)
{
	if (pHead == NULL) {
		return -1;
	}

	int cnt = 0;
	QuickListNode_T *tmp = pHead->next;
	while (tmp != pHead) {
		tmp = tmp->next;
		cnt++;
	}
	return cnt;
}



int QuickListAddNodePos(QuickListNode_T *newNode, QuickListNode_T *pos)
{
	if (newNode == NULL || pos == NULL) {
		return -1;
	}
	
	QuickListNode_T *tmp = NULL;
	tmp = pos->next;
	pos->next = newNode;
	newNode->next = tmp;
	newNode->previous = pos;
	tmp->previous = newNode;
	
	return 0;
}

int QuickListAddNodetoTail(QuickListNode_T *newNode, QuickListNode_T *pHead)
{
	if (newNode == NULL || pHead == NULL) {
		return -1;
	}

	QuickListNode_T *tmp = NULL;
	tmp = pHead->previous;
	tmp->next = newNode;
	newNode->next = pHead;
	pHead->previous = newNode;
	newNode->previous = tmp;

	return 0;
}

int QuickListAddNodetoHead(QuickListNode_T *newNode, QuickListNode_T *pHead)
{
	if (newNode == NULL || pHead == NULL) {
		return -1;
	}

	QuickListNode_T *tmp = NULL;
	tmp = pHead->next;
	pHead->next = newNode;
	newNode->next = tmp;
	tmp->previous = newNode;
	newNode->previous = pHead;
	
	return 0;
}

int QuickListDeleteNode(QuickListNode_T *delNode)
{
	if (delNode == NULL) {
		return -1;
	}

	delNode->previous->next = delNode->next;
	delNode->next->previous = delNode->previous;
	if (delNode != NULL) {
		free(delNode);
	}	

	return 0;
}


int QuickListDeleteNodefromHead(QuickListNode_T *pHead)
{
	if (pHead == NULL || pHead->next == pHead) {
		return -1;
	}
	
	return QuickListDeleteNode(pHead->next);
}

int QuickListDeleteNodefromTail(QuickListNode_T *pHead)
{
	if (pHead == NULL || pHead->previous == pHead) {
		return -1;
	}
	
	return QuickListDeleteNode(pHead->previous);
}

int QuickListMakeEmptyList(QuickListNode_T *pHead)
{
	if (pHead == NULL || pHead->next == pHead) {
		return -1;
	}
	
	QuickListNode_T *tmp = NULL;
	while ((tmp = pHead->next)!= pHead) {
		QuickListDeleteNode(tmp);
	}

	return 0;
}

int QuickListDeleteList(QuickListNode_T *pHead)
{
	if (pHead == NULL) {
		return -1;
	}
	
	QuickListMakeEmptyList(pHead);
	free(pHead);

	return 0;	
}

