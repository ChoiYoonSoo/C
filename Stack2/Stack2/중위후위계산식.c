#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_STACK_SIZE 100
typedef int element;

typedef struct {
	element data[MAX_STACK_SIZE];
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

void push(StackType* s, element item) {
	if (is_full(&s)) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	s->data[++(s->top)] = item;
}

element pop(StackType* s) {
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	return s->data[(s->top)--];
}

element peek(StackType* s) {
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	return s->data[s->top];
}

int prec(char ch) { // ������ �켱����

	switch (ch)
	{
	case'(': case')': return 0;
	case'|': return 1;
	case'&': return 2;
	case'<': case'>': return 3;
	case'+': case'-': return 4;
	case'*': case'/': case'%': return 5;
	case'^': return 6;
	}
}

void infix_to_postpix(char str[], char str2[]) { // ����ǥ��� -> ����ǥ��� ��ȯ
	StackType s;
	init_stack(&s);

	char ch, topch, endch;
	int len = strlen(str);
	int idx = 0;
	int npu = 1;
	printf("\n\n===================����ǥ��� -> ����ǥ���=================\n\n");
	for (int i = 0; i < len; i++) {
		ch = str[i];
		switch (ch)
		{
		case'|': case'&': case'<': case'>': case'+': case'-': case'*': case'/': case'%': case'^': {
			if (!is_empty(&s) && prec(ch) <= prec(peek(&s))) {
				printf("\n%d��° ���ÿ��� pop: %c\n", --npu, peek(&s));
				str2[idx++] = pop(&s);
			}
			printf("\n%d��° �������� push: %c\n",npu++, ch);
			push(&s, ch);
			break;
		}
		case'(': {
			printf("\n ( ���� �߰�\n");
			printf("\n%d��° �������� push: %c\n",npu++, ch);
			push(&s, ch);
			break;
		}
		case')': {
			printf("\n ) ���� �߰�\n");
			topch = pop(&s);
			printf("\n%d��° ���ÿ��� pop: %c\n",--npu, topch);

			while (topch != '(') {
				str2[idx++] = topch;
				topch = pop(&s);
				printf("\n%d��° ���ÿ��� pop: %c\n",--npu, topch);
			}
			break;
		}
		default:
			str2[idx++] = ch;
			break;
		}
	}

	while (!is_empty(&s)) {
		endch = pop(&s);
		printf("\n%d��° ���ÿ��� pop: %c\n",--npu, endch);
		str2[idx++] = endch;
	}

	str2[idx] = NULL;
	printf("\ninfix to postfix: ");

	for (int i = 0; i < idx; i++) {
		printf("%c", str2[i]);
	}
	printf("\n");
}

void postpix_result(char str[]) {
	StackType s;
	init_stack(&s);

	char ch;
	int len = strlen(str);
	int n1, n2, result, n=1;
	printf("\n\n=========== ����ǥ��� ���: ");
	for (int i = 0; i < len; i++) {
		printf("%c", str[i]);
	}
	printf(" =============\n");
	for (int i = 0; i < len; i++) {
		ch = str[i];
		if (ch != '+' && ch != '-' && ch != '/' && ch != '*' && ch != '^' && ch != '>' && ch != '<' && ch != '=' && ch != '&' && ch != '|' && ch != '%') {
			result = ch - '0';
			printf("\n%d��° �������� push: %d\n",n++, result);
			push(&s, result);
		}
		else {
			n2 = pop(&s);
			n1 = pop(&s);
			printf("\n[ %c ������ �߰� �� ���� �ǿ����� pop]\n",ch);
			printf("\n%d��° ���ÿ��� pop: %d\n",--n, n2);
			printf("\n%d��° ���ÿ��� pop: %d\n",--n, n1);
			switch (ch) {
			case'+':
				push(&s, n1 + n2);
				printf("\n%d + %d ����� push: %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'-':
				push(&s, n1 - n2);
				printf("\n%d - %d ����� push: %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'/':
				push(&s, n1 / n2);
				printf("\n%d / %d ����� push: %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'*':
				push(&s, n1 * n2);
				printf("\n%d * %d ����� push: %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'^':
				push(&s, pow(n1, n2));
				printf("\n%d ^ %d ����� push: %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'>':
				push(&s, n1 > n2);
				printf("\n%d > %d ����� push: %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'<':
				push(&s, n1 < n2);
				printf("\n%d < %d ����� push: %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'=':
				push(&s, n1);
				printf("\n%d == %d ����� push: %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'&&':
				push(&s, n1 && n2);
				printf("\n%d && %d ����� push: %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'|':
				push(&s, n1 || n2);
				printf("\n%d || %d ����� push: %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'%':
				push(&s, n1 % n2);
				printf("\n%d  %d ����� push: %d\n", n1, n2, peek(&s));
				n++;
				break;
			}
		}
	}
	printf("\n�����: %d\n", pop(&s));
}
int main(void) {
	char str[100];
	char str2[100];
	int n;

	do {
		printf("����ǥ��� ���� �Է�: ");
		scanf("%s", str);
		infix_to_postpix(str, str2);
		postpix_result(str2);

		printf("\n\n1.���\n2.����\n");
		scanf("%d", &n);
		if (n == 2) {
			printf("\n���α׷� ����\n");
			break;
		}
	} while (1);
	return 0;
}