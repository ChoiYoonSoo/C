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

void init_stack(StackType* s) { // ���� ����
	s->top = -1;
}

int is_empty(StackType* s) { // ���� ���� ���� Ȯ��
	return s->top == -1;
}

int is_full(StackType* s) { // ���� ��ȭ ���� Ȯ��
	return s->top == (MAX_STACK_SIZE - 1);
}

void push(StackType* s, element item) { // ���� ����
	if (is_full(&s)) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	s->data[++(s->top)] = item;
}

element pop(StackType* s) { // ���� ����
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	return s->data[(s->top)--];
}

element peek(StackType* s) { // ���� top��ġ
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	return s->data[s->top];
}

int prec(char ch) { // ������ �켱���� (��ȯ���� Ŭ���� �������)

	switch (ch)
	{
	case'|': return 1;
	case'&': return 2;
	case'<': case'>': return 3;
	case'+': case'-': return 4;
	case'*': case'/': case'%': return 5;
	case'^': return 6;
	}
	return -1;
}

void infix_to_postfix(char str[], char str2[]) { // ����ǥ��� -> ����ǥ��� ��ȯ
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
		case'|': case'&': case'<': case'>': case'+': case'-': case'*': case'/': case'%': case'^': { // �������� ��� ����
			if (!is_empty(&s) && ch == '^' && ch == peek(&s, ch)) {
				printf("\n%d�� ���� PUSH -> [ %c ]\n", npu++, ch);
				push(&s, ch);
				break;
			}
			while (!is_empty(&s) && prec(ch) <= prec(peek(&s))) { // ���ÿ� �ִ� �������� �켱������ �� �������
				printf("\n%d�� ���� POP -> [ %c ]  \n", --npu, peek(&s));
				str2[idx++] = pop(&s);
			}
			printf("\n%d�� ���� PUSH -> [ %c ]\n",npu++, ch);
			push(&s, ch);
			break;
		}
		case'(': { // ������ȣ�� ���
			printf("\n%d�� ���� PUSH -> [ %c ]\n",npu++, ch);
			push(&s, ch);
			break;
		}
		case')': { // ������ȣ�� ���
			printf("\n[ ) ] ������ �߰�\n");
			topch = pop(&s);
			printf("\n%d�� ���� POP- > [ %c ]\n",--npu, topch);

			while (topch != '(') { // '('���ڰ� ���ö����� ��� pop
				str2[idx++] = topch;
				topch = pop(&s);
				printf("\n%d�� ���� POP -> [ %c ]\n",--npu, topch);
			}
			break;
		}
		default: // �ǿ������ϰ�� �迭�� ����
			printf("\n�ǿ����� %c ����\n", ch);
			str2[idx++] = ch;
			break;
		}
	}

	while (!is_empty(&s)) { // ���ÿ� �����������
		endch = pop(&s);
		printf("\n%d�� ���� POP -> [ %c ]\n",--npu, endch);
		str2[idx++] = endch;
	}

	str2[idx] = NULL;
	printf("\ninfix to postfix: ");

	for (int i = 0; i < idx; i++) {
		printf("%c", str2[i]);
	}
	printf("\n");
}

void postfix_eval(char str[]) { // ����ǥ��� ���
	StackType s;
	init_stack(&s);

	char ch;
	int len = strlen(str);
	int n1, n2, result, n=1;

	printf("\n\n=========== ����ǥ��� ��� ==========\n\n");
	for (int i = 0; i < len; i++) {
		ch = str[i];
		// �����ڰ� �ƴ� ���
		if (ch != '+' && ch != '-' && ch != '/' && ch != '*' && ch != '^' && ch != '>' && ch != '<' && ch != '=' && ch != '&' && ch != '|' && ch != '%') {
			result = ch - '0';
			printf("\n%d�� ���� PUSH -> %d\n",n++, result);
			push(&s, result);
		}
		else { // �������� ��� �� ���� �ǿ����� �����ͼ� ��� �� push
			n2 = pop(&s);
			n1 = pop(&s);
			printf("\n[ %c ������ �߰� �� ���� �ǿ����� POP]\n",ch);
			printf("\n%d�� ���� POP -> %d\n",--n, n2);
			printf("\n%d�� ���� POP -> %d\n",--n, n1);
			switch (ch) {
			case'+': // +���� ����
				push(&s, n1 + n2);
				printf("\n%d + %d ����� PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'-': // -���� ����
				push(&s, n1 - n2);
				printf("\n%d - %d ����� PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'/': // /���� ����
				push(&s, n1 / n2);
				printf("\n%d / %d ����� PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'*': // *���� ����
				push(&s, n1 * n2);
				printf("\n%d * %d ����� PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'^': // �ŵ����� ���� ����
				push(&s, pow(n1, n2));
				printf("\n%d ^ %d ����� PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'>': // ��Һ�
				push(&s, n1 > n2);
				printf("\n%d > %d ����� PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'<': // ��Һ�
				push(&s, n1 < n2);
				printf("\n%d < %d ����� PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'=': // ==���� ����
				push(&s, n1);
				printf("\n%d == %d ����� PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'&': // &&���� ����
				push(&s, n1 && n2);
				printf("\n%d && %d ����� PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'|': // ||���� ����
				push(&s, n1 || n2);
				printf("\n%d || %d ����� PUSH -> %d\n", n1, n2, peek(&s));
				n++;
				break;
			case'%': // %���� ����
				push(&s, n1 % n2);
				printf("\n%d %c %d ����� PUSH -> %d\n", n1, 37, n2, peek(&s));
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
		infix_to_postfix(str, str2);
		postfix_eval(str2);

		printf("\n1.���\n");
		printf("2.����\n");
		scanf("%d", &n);

		if (n == 2) {
			printf("\n���α׷��� �����մϴ�.\n");
			break;
		}
	} while (1);

	return 0;
}