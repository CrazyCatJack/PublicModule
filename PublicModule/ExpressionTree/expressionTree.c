// SPDX-License-Identifier: GPL-2.0-only
/*
 *	expressionTree.c
 *
 * Copyright (C) 2020  xuri
 */

/*
 * This file define expressionTree function
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "treeADT.h"
#include "stackADT.h"

#define OPERATOR_TYPE 4
char Operator[OPERATOR_TYPE] = {'+', '-', '*', '/'};
char *Expression = "12+3*85-/";


void suffixExpression(char *inputStr)
{
	int cnt, cnt2;
	Stack s = CreateStack();	
	
	for (cnt = 0; inputStr[cnt] != '\0'; cnt++) {
		if ((inputStr[cnt] >= '0') && (inputStr[cnt] <= '9')) {
			PtrToTreeHead numTree = CreateTreeNode();
			numTree->Element = inputStr[cnt];
			printf("Push %c\n", numTree->Element);
			Push(numTree, s);
		}

		for (cnt2 = 0; cnt2 < OPERATOR_TYPE; cnt2++) {
			if (inputStr[cnt] == Operator[cnt2]) {
				PtrToTreeHead operatorTree = CreateTreeNode();
				operatorTree->Element = inputStr[cnt];
				PtrToTreeHead num2Tree = Top(s);
				Pop(s);
				PtrToTreeHead num1Tree = Top(s);;
				Pop(s);
				
				operatorTree->LeftChild = num1Tree;
				operatorTree->RightChild = num2Tree;
				Push(operatorTree, s);
				printf("operator=%c, num1=%c, num2=%c\n", operatorTree->Element, num1Tree->Element, num2Tree->Element);
			}
		}
	}
	
	PtrToTreeHead printTree = Top(s);
	PrintTree(printTree);
	DrstroyTree(printTree);
	DistroyStack(s);
}

void main()
{
	suffixExpression(Expression);
}
