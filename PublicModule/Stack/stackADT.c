// SPDX-License-Identifier: GPL-2.0-only
/*
 *	stackADT.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file define stackADT function
 */
#include "stackADT.h"

Stack
CreateStack(void)
{
    Stack s = NULL;
    s = (Stack)malloc(sizeof(struct node));
    if (s == NULL) {
        printf("stack malloc failed\n");
        return s;
    }
    memset(s, 0, sizeof(struct node));
    s->Next = NULL;
    return s;
}

void
MakeEmpty(Stack s)
{
    PtrToNode p = NULL, tmp = NULL;
    p = s->Next;
    while (p != NULL) {
        tmp = p->Next;
        free(p);
        p = tmp;
    }
}

int
Push(ElementType X, Stack s)
{
    PtrToNode tmp = NULL;
    tmp = (PtrToNode)malloc(sizeof(struct node)); 
	if (tmp == NULL) {
        return -1;
    }
    memset(tmp, 0, sizeof(struct node));
    tmp->Element = X;
    tmp->Next = s->Next;
    s->Next = tmp;
    return 0;
}

void
Pop(Stack s)
{
    if (s == NULL || s->Next == NULL) {
        return;
    }
    PtrToNode tmp = NULL;
    tmp = s->Next;
    s->Next = tmp->Next;
    free(tmp);
}


void 
DeleteNode(ElementType X, Stack s)
{
	if (s == NULL || s->Next == NULL) {
		return;
	}
    PtrToNode tmp = NULL, tmpNext = NULL;
	for (tmp = s, tmpNext = tmp->Next; tmpNext != NULL; tmp = tmpNext, tmpNext = tmp->Next) {
		if (tmpNext->Element == X) {
			printf("Find delete node: %d\n", tmpNext->Element);
			tmp->Next = tmpNext->Next;
			free(tmpNext);
		}
	}
}


ElementType
Top(Stack s)
{
    return s->Next->Element;
}

int
IsEmpty(Stack s)
{
    return (s->Next == NULL);
}

void
DistroyStack(Stack s)
{
	if (s == NULL) {
		return;
	}
	MakeEmpty(s);
	free(s);
}

void
PrintStack(Stack s)
{
	if (s == NULL) {
		return;
	}
	
	Stack tmp;
	for (tmp = s->Next; tmp != NULL; tmp = tmp->Next) {
		printf("%d ", tmp->Element);
	}
}
