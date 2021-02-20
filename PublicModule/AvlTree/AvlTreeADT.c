// SPDX-License-Identifier: GPL-2.0-only
/*
 *	AvlTreeADT.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file define AvlTree function
 */
#include "AvlTreeADT.h"


static int Max(int a, int b)
{
	return (a > b ? a : b);
}


static int Height(AvlTree T)
{
	if (T == NULL) {
		
		return -1;
	}
	return (T->Height);
}

static AvlTree SingleRotateWithLeft(Position P)
{
	Position P1 = NULL;
	P1 = P->Left;
	P->Left = P1->Right;
	P1->Right = P;
	P->Height = Max(Height(P->Left), Height(P->Right)) + 1;
	P1->Height = Max(Height(P1->Left), Height(P1->Right)) + 1;
	return P1;
}

static AvlTree SingleRotateWithRight(Position P)
{
	Position P1 = NULL;
	P1 = P->Right;
	P->Right = P1->Left;
	P1->Left = P;
	P->Height = Max(Height(P->Left), Height(P->Right)) + 1;
	P1->Height = Max(Height(P1->Left), Height(P1->Right)) + 1;
	return P1;
}

static AvlTree DoubleRotateWithLeft(Position P)
{
	P->Left = SingleRotateWithRight(P->Left);
	return SingleRotateWithLeft(P);
}

static AvlTree DoubleRotateWithRight(Position P)
{
	P->Right = SingleRotateWithLeft(P->Right);
	return SingleRotateWithRight(P);
}



void MakeEmpty(AvlTree T)
{
	if (T == NULL) {
		return;
	}
	
	if (T->Left) {
		MakeEmpty(T->Left);
	}
	if (T->Right) {
		MakeEmpty(T->Right);
	}
	if (T != NULL) {
		free(T);
	}
}

Position Find(AvlTree T, ElementType X)
{
	if (T == NULL) {
		return T;
	}

	if (X < T->Element) {
		return Find(T->Left, X);
	} else if (X > T->Element) {
		return Find(T->Right, X);
	} else {
		return T;
	}
}

Position FindMin(AvlTree T)
{
	if (T == NULL) {
		return T;
	}

	if (T->Left) {
		return FindMin(T->Left);
	} else {
		return T;
	}
}

Position FindMax(AvlTree T)
{
	if (T == NULL) {
		return T;
	}

	if (T->Right) {
		return FindMax(T->Right);
	} else {
		return T;
	}

}

AvlTree Insert(AvlTree T, ElementType X)
{
	if (T == NULL) {
		T = (struct AvlNode *)malloc(sizeof(struct AvlNode));
		if (T == NULL) {
			return T;
		}
		memset(T, 0, sizeof(struct AvlNode));
		T->Element = X;
		T->Height = 0;
		T->Left = T->Right = NULL;
	} else if (X < T->Element) {
		T->Left = Insert(T->Left, X);
		if (Height(T->Left) - Height(T->Right) == 2) {
			if (X < T->Left->Element) {
				T = SingleRotateWithLeft(T);
			} else {
				T = DoubleRotateWithLeft(T);
			}
		}
	} else if (X > T->Element) {
		T->Right = Insert(T->Right, X);
		if (Height(T->Right) - Height(T->Left) == 2) {
			if (X > T->Right->Element) {
				T = SingleRotateWithRight(T);
			} else {
				T = DoubleRotateWithRight(T);
			}
		}
	}

	T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
	return T;
}

AvlTree Delete(AvlTree T, ElementType X)
{
	if (T == NULL) {
		return T;
	}

	Position tmp = NULL;
	if (X < T->Element) {
		T->Left = Delete(T->Left, X);
		if (Height(T->Right) - Height(T->Left) == 2) {
			T = SingleRotateWithRight(T);
		}
	} else if (X > T->Element) {
		T->Right = Delete(T->Right, X);
		if (Height(T->Left) - Height(T->Right) == 2) {
			T = SingleRotateWithLeft(T);
		}
	} else if (T->Left && T->Right){
		tmp = FindMin(T);
		T->Element = tmp->Element;
		T->Right = Delete(T->Right, X);
	} else {
		tmp = T;
		if (T->Left) {
			T = T->Left;
		}
		if (T->Right) {
			T = T->Right;
		}
		free(tmp);
	}

	return T;
}


void
PrintTree(AvlTree root)
{
	if (root->Left != NULL) {
		PrintTree(root->Left);
	}
	
	if (root != NULL) {
		printf("%d ", root->Element);
	}	

	if (root->Right != NULL) {
		PrintTree(root->Right);
	}
}


