  
// SPDX-License-Identifier: GPL-2.0-only
/*
 *	QuickList.h
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file declare QuickList structure & function prototypes
 */


#ifndef __QUICKLIST_H_
#define __QUICKLIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct QuickListNode{
	void *userdata;	// user data
	struct QuickListNode *previous; // point to previous node
	struct QuickListNode *next;	// point to next node
} QuickListNode_T;


/**
 * QuickList_for_each_entry - traverse all QuickList
 * @pHead[in]:	QuickList HEAD node
 * @node[in]:	QuickList node pointer
 *
 * traverse all QuickList
 *
 */
#define QuickList_for_each_entry(pHead, node) \
	for (node = pHead->next; node != pHead; node = node->next)


/**
 * QuickList_for_each_entry_safe - traverse all QuickList on safe status
 * @pHead[in]:	QuickList HEAD node
 * @node[in]:	QuickList node pointer
 * @node2[in]:  QuickList node pointer2
 *
 * traverse all QuickList, could delete or detach node in this loop
 *
 */
#define QuickList_for_each_entry_safe(pHead, node, node2) \
	for (node = pHead->next, node2 = node->next; node != pHead; node = node2, node2 = node->next)



/**
 * QuickList_entry - get QuickList node userdata
 * @type[in]:	userdata type
 * @node[in]:	QuickList node pointer
 *
 * get QuickList node userdata
 *
 */
#define QuickList_entry(type, node) \
	(type *)node->userdata


/**
 * QuickListCreateList - create QuickList head
 *
 * create QuickList head
 *
 * Return: !=NULL on success, Head ponter; NULL on malloc failed
 */
QuickListNode_T *QuickListCreateList();


/**
 * QuickListCreateNode - create QuickList node
 * @userdata[in]:	the node userdata
 *
 * create QuickList node
 *
 * Return: !=NULL on success, QuickList node ponter; NULL on malloc failed
 */
QuickListNode_T *QuickListCreateNode(void *userdata);


/**
 * QuickListGetNodeSum - get QuickList node sum
 * @pHead[in]:	the QuickList HEAD node
 *
 * get QuickList node sum
 *
 * Return: >=0 on success, QuickList node sum; -1 on parameter failed
 */
int QuickListGetNodeSum(QuickListNode_T *pHead);


/**
 * QuickListAddNodePos - add QuickList node after pos
 * @newNode[in]:	the node need to be added
 * @pos[in]:	add  @newNode after pos node
 *
 * add QuickList node after pos
 *
 * Return: 0 on success; -1 on parameter failed
 */
int QuickListAddNodePos(QuickListNode_T *pos, QuickListNode_T *newNode);


/**
 * QuickListAddNodetoTail - add QuickList node after tail node
 * @newNode[in]:	the node need to be added
 * @pHead[in]:	the QuickList HEAD node
 *
 * add QuickList node after tail node
 *
 * Return: 0 on success; -1 on parameter failed
 */
int QuickListAddNodetoTail(QuickListNode_T *pHead, QuickListNode_T *newNode);


/**
 * QuickListAddNodetoHead - add QuickList node after head node
 * @newNode[in]:	the node need to be added
 * @pHead[in]:	the QuickList HEAD node
 *
 * add QuickList node after head node
 *
 * Return: 0 on success; -1 on parameter failed
 */
int QuickListAddNodetoHead(QuickListNode_T *pHead, QuickListNode_T *newNode);


/**
 * QuickListDeleteNode - delete the specify QuickList node 
 * @delNode[in]:	the node need to be deleted
 *
 * delete the specify QuickList node
 *
 * Return: 0 on success; -1 on parameter failed
 */
int QuickListDeleteNode(QuickListNode_T *delNode);


/**
 * QuickListDeleteNodefromHead - delete the QuickList node after HEAD
 * @pHead[in]:	the QuickList HEAD node 
 *
 * delete the QuickList node after HEAD
 *
 * Return: 0 on success; -1 on parameter failed
 */
int QuickListDeleteNodefromHead(QuickListNode_T *pHead);


/**
 * QuickListDeleteNodefromTail - delete the QuickList node after tail
 * @pHead[in]:	the QuickList HEAD node 
 *
 * delete the QuickList node after tail
 *
 * Return: 0 on success; -1 on parameter failed
 */
int QuickListDeleteNodefromTail(QuickListNode_T *pHead);


/**
 * QuickListDetachNode - detach the specify QuickList node 
 * @detNode[in]:	the node need to be detachd
 * NOTE: @detNode Couldn't be pHead node
 *
 * just detach the specify QuickList node, do not free it memory
 *
 * Return: !=NULL on success, the specify detached node; NULL on parameter failed
 */
QuickListNode_T *QuickListDetachNode(QuickListNode_T *pHead, QuickListNode_T *detNode);



/**
 * QuickListDetachNodefromHead - detach the QuickList node after HEAD
 * @pHead[in]:	the QuickList HEAD node 
 *
 * detach the QuickList node after HEAD, do not free it memory
 *
 * Return: !=NULL on success, the specify detached node; NULL on parameter failed
 */
QuickListNode_T *QuickListDetachNodefromHead(QuickListNode_T *pHead);



/**
 * QuickListDetachNodefromTail - detach the QuickList node after tail
 * @pHead[in]:	the QuickList HEAD node 
 *
 * detach the QuickList node after tail, do not free it memory
 *
 * Return: !=NULL on success, the specify detached node; NULL on parameter failed
 */
QuickListNode_T *QuickListDetachNodefromTail(QuickListNode_T *pHead);



/**
 * QuickListMakeEmptyList - make QuickList empty, reserve HEAD node
 * @pHead[in]:	the QuickList HEAD node 
 *
 * make QuickList empty, reserve HEAD node
 *
 * Return: 0 on success; -1 on parameter failed
 */
int QuickListMakeEmptyList(QuickListNode_T *pHead);


/**
 * QuickListDeleteList - delete all QuickList, include HEAD node
 * @pHead[in]:	the QuickList HEAD node 
 *
 * delete all QuickList, include HEAD node
 *
 * Return: 0 on success; -1 on parameter failed
 */
int QuickListDeleteList(QuickListNode_T *pHead);





#ifdef __cplusplus
}
#endif


#endif
