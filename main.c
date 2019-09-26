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
			if (ch == '\n') *line = *line + 1;
			else if (ch == '#') {
				while(getc(file) != '\n');
				*line = *line + 1;
			}
			else if (ch == '{') {
				emptyStack(&top);
			}
			else if (ch == 'r' && peek(top) == 'o' && peekFromTop(top, 1) == 'f') {
				while(getc(file) != '\n');
				*line = *line + 1;
			}
			else push(&top, ch);
		}
		else {
			if (((peek(top) < 'A' || peek(top) > 'Z') &&
				(peek(top) < 'a' || peek(top) > 'z') && (peek(top) < '0' || peek(top) > '9')) && peek(top) != ')') {
				return 0;
			}
		}
	}
	return 1;
}
