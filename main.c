#include <stdio.h>
#include "stack.h"

int validateSemicolons(FILE*, Node*, int*);

int main() {
	FILE *file;
	int line = 1;
	Node top;
	file = fopen("./test.c", "r");
	if (validateSemicolons(file, &top, &line)) {
		printf("No semicolon errors detected");
	}
	else {
		printf("Semicolon error detected at line %d", line);
	}
	fclose(file);
	return 0;
}

int validateSemicolons(FILE *file, Node* top, int* line) {
	char ch;
	top = NULL;
	while((ch = getc(file)) != EOF) {
		if (ch != ';') {
			if (ch == '\n') (*line)++; //increase line number
			/* semicolon should be present before function invocation */
			else if (ch == '(') {
				/* ignore function name (all characters except whitespace) */
				while(!isEmpty(top) && (peek(top) != ' ' && peek(top) != '\t' && peek(top) != '\n')) pop(&top);
				/* now ignore whitespace */
				while(!isEmpty(top) && (peek(top) == ' ' || peek(top) == '\t' || peek(top) == '\n')) pop(&top);
				if (!isEmpty(top) && peek(top) != ';' && peek(top) != '{' && peek(top) != '}' &&
				/* ignoring int of int main */
				 peek(top) != 't' && peekFromTop(top, 1) != 'n' && peekFromTop(top, 2) != 'i') {
					return 0;
				}
			}
			/* function invocations must end with semicolon */
			else if (ch == ')') {
				//ignore whitespace
				while((ch = getc(file)) == ' ' || ch == '\n' || ch == '\t') {
					if (ch == '\n') (*line)++;
				}
				if (ch != ';' && ch != '{') return 0;
				else push(&top, ch);
			}
			/* ignore all preprocessor statments */
			else if (ch == '#') {
				while(getc(file) != '\n');
				(*line)++;
			}
			/* ignore for loop */
			else if (ch == 'r' && peek(top) == 'o' && peekFromTop(top, 1) == 'f') {
				while(getc(file) != '\n');
				(*line)++;
			}
			/* ignore if statement */
			else if (ch == 'f' && peek(top) == 'i') {
				while(getc(file) != '\n');
				(*line)++;
			}
			/* push to stack */
			else push(&top, ch);
		}
		else {
			/* semicolons cant be anywhere other than identifiers and function invocations */
			/* eg: a = a + ; is invalid */
			/* ignore whitespace */
			while(!isEmpty(top) && (peek(top) == ' ' || peek(top) == '\t' || peek(top) == '\n')) pop(&top);
			
			if (((peek(top) < 'A' || peek(top) > 'Z') &&
				(peek(top) < 'a' || peek(top) > 'z') && (peek(top) < '0' || peek(top) > '9')) && peek(top) != ')') {
				return 0;
			}
			else {
				//no errors, empty stack
				emptyStack(&top);
				push(&top, ';');
			}
		}
	}
	return 1;
}
