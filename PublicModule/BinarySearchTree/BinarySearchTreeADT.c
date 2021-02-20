// SPDX-License-Identifier: GPL-2.0-only
/*
 *	BinarySearchTreeADT.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file define BinarySearchTreeADT function
 */
#include "BinarySearchTreeADT.h"

void
MakeEmpty(PtrToTreeHead treeHead)
{
    if (treeHead == NULL) {
        return;
    }
    if (treeHead->LeftChild != NULL) {
        MakeEmpty(treeHead->LeftChild);
    }
    if (treeHead->RightChild != NULL) {
        MakeEmpty(treeHead->RightChild);
    }
    if (treeHead != NULL) {
        free(treeHead);
    }
}

PtrToTreeHead
Find(PtrToTreeHead treeHead, ElementType Element)
{
    if (treeHead == NULL) {
        return NULL;
    }
    if (Element < treeHead->Element) {
        return Find(treeHead->LeftChild, Element);
    } else if (Element > treeHead->Element) {
        return Find(treeHead->RightChild, Element);
    } else {
        return treeHead;
    }
}

PtrToTreeHead
FindMin(PtrToTreeHead treeHead)
{
    if (treeHead == NULL) {
        return NULL;
    }
    if (treeHead->LeftChild != NULL) {
        return FindMin(treeHead->LeftChild);
    } else {
        return treeHead;
    }
}

PtrToTreeHead
FindMax(PtrToTreeHead treeHead)
{
    if (treeHead == NULL) {
        return NULL;
    }
    if (treeHead->RightChild != NULL) {
        return FindMax(treeHead->RightChild);
    } else {
        return treeHead;
    }
}

PtrToTreeHead
Insert(PtrToTreeHead treeHead, ElementType element)
{
    if (treeHead == NULL) {
        treeHead = (PtrToTreeHead)malloc(sizeof(struct TreeNode));
        if (treeHead == NULL) {
            return NULL;
        }
        memset(treeHead, 0, sizeof(struct TreeNode));
        treeHead->Element = element;
        treeHead->LeftChild = treeHead->RightChild = NULL;
    } else if (element < treeHead->Element) {
        treeHead->LeftChild = Insert(treeHead->LeftChild, element);    
    } else if (element > treeHead->Element) {
        treeHead->RightChild = Insert(treeHead->RightChild, element);
    }
    
    return treeHead;
}


PtrToTreeHead
Delete(PtrToTreeHead T, ElementType element)
{
    PtrToTreeHead tmp;
    
    if (T == NULL) {
        printf("Couldn't find element\n");
        return NULL;
    } else if (element < T->Element) {
        T->LeftChild = Delete(T->LeftChild, element);
    } else if (element > T->Element) {
        T->RightChild = Delete(T->RightChild, element);
    } else if (T->LeftChild && T->RightChild) {
        tmp = FindMin(T->RightChild);
        T->Element = tmp->Element;
        T->RightChild = Delete(T->RightChild, tmp->Element); 
    } else {
        tmp = T;
        if (T->LeftChild) {
            T = T->LeftChild;
        } else if (T->RightChild) {
            T = T->RightChild;
        }
        free(tmp);
    }

	return T;
}


