// ����ǥ����� ���ڿ� ���·� ����ǥ������� �����ϱ� ���� 2
// ���þȿ� �����ڸ� �־� ���� �����ڰ� ���ý� ������ ���µ� a+b*c�� ���� ���� ������ �������� �켱������
// �Ŀ� ������ �����ں��� ������� ���� ������ �ȵ�. ex) ab+c* -> X, abc*+ -> O
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100

typedef struct {
	char data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) {
	s->top = -1;
}

int is_empty(StackType* s) {
	return s->top == -1;
}

int is_full(StackType* s) {
	return s->top == (MAX_STACK_SIZE - 1);
}

void push(StackType* s, char ch) {
	if (is_full(&s)) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	s->data[++(s->top)] = ch;
}

char pop(StackType* s) {
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[s->top--];
}

char peek(StackType* s) {
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[s->top];
}

void mid_num(char str[]) {
	StackType s;
	init_stack(&s);

	int len = strlen(str);
	int index = 0;
	char ch;
	char ch2[100];

	for (int i = 0; i < len; i++) {
		ch = str[i];
		if (ch != '+' && ch != '-' && ch != '*' && ch != '/') {
			ch2[index] = ch;
			index++;
		}
		else {
			if (is_empty(&s)) {
				push(&s, ch);
			}
			else {
				ch2[index] = pop(&s);
				index++;
				push(&s, ch);
			}
		}
	}
	while (!is_empty(&s)) ch2[index] = pop(&s);
	for (int i = 0; i <= index; i++) {
		printf("%c", ch2[i]);
	}
}

int main(void) {
	printf("1*2+3�� ����ǥ�������\n");
	mid_num("1*2+3");
	return 0;
}