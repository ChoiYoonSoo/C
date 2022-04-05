#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STACK_SIZE 100

typedef int element;
element stack[MAX_STACK_SIZE];
int top = -1;

int empty() { //������ ��������� 1, �ƴϸ� 0��ȯ 
	return (top == -1);
}

int full() { //������ ���� �������� 1, �ƴϸ� 0��ȯ
	return (top == MAX_STACK_SIZE - 1);
}

void push(element item) { //���ÿ� ��� �߰�
	if (full()) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	else {
		stack[++top] = item;
	}
}

element pop() { //���� ��� ����
	if (empty()) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else {
		return stack[top--];
	}
}

element peek() { //���� ��� ��������
	if (empty()) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else {
		return stack[top];
	}
}
int main(void) {
	push(1);
	push(2);
	push(3);
	pop();
	printf("%d\n", peek());
	return 0;
}