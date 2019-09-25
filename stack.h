/*
 * This file contains the following stack operations:
 * push, pop, peek, isEmpty, emptyStack
 * */

#include <stdlib.h>

typedef struct Node {
	struct Node* next;
	char data;
} Node;

void push(Node** top, char elem) {
	Node* temp = (Node*)malloc(sizeof(Node));
	temp->data = elem;
	temp->next = *top;
	*top = temp;
}

char pop(Node** top) {
	char elem = (*top)->data;
	Node* temp = (Node*)malloc(sizeof(Node));
	temp = *top;
	*top = (*top)->next;
	free(temp);
	return elem;
}

char peek(Node* top) {
	return top->data;
}

int isEmpty(Node* top) {
	return top == NULL;
}

void emptyStack(Node** top) {
	while(!isEmpty(*top)) {
		pop(top);
	}
}
