#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_STACK_SIZE 100
typedef int element;

typedef struct { // ���� ����
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) { // top��ġ �ʱ�ȭ
	s->top = -1;
}

int is_empty(StackType* s) { // ���� ���� �˻�
	return s->top == -1;
}

int is_full(StackType* s) { // ���� ��ȭ �˻�
	return s->top == (MAX_STACK_SIZE - 1);
}

void push(StackType* s, element item) { // ���� ����ֱ�
	if (is_full(&s)) {
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	s->data[++(s->top)] = item;
}

element pop(StackType* s) { // ���� �ֻ�� ��ġ �� ������ ����
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s) { // ���� �ֻ�� ��ġ �� ������
	if (is_empty(&s)) {
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)];
}

int check_matching(char str[]) { // ��ȣ ���� �˻� �Լ�
	StackType s;
	StackType n;

	char ch, popch;
	int len = strlen(str);
	int number = 1;

	init_stack(&s);
	init_stack(&n);

	printf("��ȣ ��: ");
	for (int i = 0; i < len; i++) {
		ch = str[i];

		switch (ch) {
		case'[': case'(':  case'{': { // ���� ��ȣ ������ ���ÿ� ����, ���ڵ� ���ÿ� ����
			push(&s, ch);
			push(&n, number);
			printf("%d ", number);
			number++;
			break;
		}
		case']': case')': case'}': { // ���� ��ȣ ������ ������ ��� �� ������ ��
			if (is_empty(&s)) return 0;
			popch = pop(&s);
			if ((popch == '[' && ch != ']') ||
				(popch == '(' && ch != ')') ||
				(popch == '{' && ch != '}')) {
				return 0;
			}
			printf("%d ", pop(&n));
			break;
		}
		}
	}
	if (!is_empty(&s)) return 0; // ���ÿ� �����ִ� ���� Ȯ��
	return 1;
}

void runLength(char str[]) { // ���ڿ� ���� ����
	StackType s;
	init_stack(&s);

	int i = 0, n = 0;
	int cnt = 1;
	int len = strlen(str);
	char ch;

	while (str[len - i] >= 0) { // �빮�� -> �ҹ��� ��ȯ �� ���� ����
		ch = str[len - i];
		if (ch >= 65 && ch <= 90) {
			ch = ch + 32;
		}
		push(&s, ch);
		i++;
	}

	while (n < len) { // pop�ؼ� ���� ���� peek ���� ���ؼ� ������ count ����
		ch = pop(&s);
		if (ch == peek(&s)) {
			cnt++;
		}
		else { // ���� �ٸ��� count�� ���� ���
			printf("%d%c", cnt, ch);
			cnt = 1;
		}
		n++;
	}

}

void palindrome(char str[]) { // ���ڿ� ȸ�� �˻�
	StackType s;
	init_stack(&s);

	char str2[100];
	char ch;

	int idx = 0;
	int cnt = 0;
	int len = strlen(str);

	for (int i = 0; i < len; i++) { // str�迭�� ���ĺ��ҹ��ڸ� str2�� ������� ����
		ch = str[i];
		if (ch >= 65 && ch <= 90) {
			ch = ch + 32;
		}
		if (ch >= 'a' && ch <= 'z') {
			str2[idx++] = ch;
		}
	}

	for (int i = 0; i < idx; i++) { // str2�迭 ��ҵ��� ������� ���ÿ� ����
		ch = str2[i];
		push(&s, ch);
	}

	for (int i = 0; i < idx; i++) { // str2�迭�� ����ִ� ���ڵ�� ���ÿ� �׿��ִ� ���ڵ� ��
		if (str2[i] == pop(&s)) {
			cnt++;
		}
		printf("%c ", str2[i]);
	}

	if (cnt == idx) { // count ���� index���� ������ ���ڿ� ��ġ 
		printf("ȸ���Դϴ�\n");
	}
	else
		printf("ȸ���̾ƴմϴ�.");
}

void result_stack(char str[]) { // ����ǥ��� ����ϴ� �Լ�
	StackType s;
	init_stack(&s);

	char ch;
	int len = strlen(str);
	int n1, n2, result;

	for (int i = 0; i < len; i++) {
		ch = str[i];

		//���ڹ��ڸ� ���ڷ� ��ȯ�Ͽ� ���ÿ� ����
		if (ch != '+' && ch != '-' && ch != '/' && ch != '*' && ch != '^' && ch != '>' && ch != '<' && ch != '=' && ch != '&' && ch != '|') {
			result = ch - '0';
			push(&s, result);
		}
		else { // ���ڹ��ڰ� �ƴ� �������ϰ�� ���� ����
			n2 = pop(&s);
			n1 = pop(&s);
			if (ch == '+') { // +����
				push(&s, n1 + n2);
				printf("\n%d + %d �����: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '-') { // -����
				push(&s, n1 - n2);
				printf("\n%d - %d �����: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '/') { // /����
				push(&s, n1 / n2);
				printf("\n%d / %d �����: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '*') { // *����
				push(&s, n1 * n2);
				printf("\n%d * %d �����: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '^') { // �ŵ����� ����
				push(&s,pow(n1,n2));
				printf("\n%d ^ %d �����: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '>') { // ��Һ�
				push(&s, n1 > n2);
				printf("\n%d > %d �����: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '<') { // ��Һ�
				push(&s, n1 < n2);
				printf("\n%d < %d �����: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '=') { // ���� �������
				push(&s, n1);
				printf("\n%d == %d �����: %d\n",n1,n2, peek(&s));
			}
			else if (ch == '&') { // AND����
				push(&s, n1 && n2);
				printf("\n%d && %d �����: %d\n",n1,n2, peek(&s));
			}
			else { // OR����
				push(&s, n1 || n2);
				printf("\n%d || %d �����: %d\n",n1,n2, peek(&s));
			}
		}
	}
	printf("\n��� ��: %d\n", pop(&s));
}


int main(void) {
	int n;
	while (1) {
		printf("\n1~4�� �� �����ϼ���.(0�� ������ ����): ");
		scanf("%d", &n);

		switch (n)
		{

		case 0: {
			printf("���α׷��� �����մϴ�\n");
			return 0;
		}

		case 1: {
			printf("\n��ȣ ��Ī ��ȣ �ű��\n");
			char str[100];
			printf("���� �Է�: ");
			scanf("%s", str);

			printf("����: ");
			printf("%s\n", str);

			if (check_matching(str) == 1) {
				printf("\n��ȣ �˻� ����\n");
			}
			else {
				printf("\n��ȣ �˻� ����\n");
			}
			break;
		}

		case 2: {
			printf("\nrun-length ����\n");
			char str[100];
			printf("���ڿ��� �Է��Ͻÿ�: ");
			scanf("%s", str);
			runLength(str);
			break;
		}

		case 3: {
			printf("\npalindrome\n");
			char str[100];
			printf("���ڿ��� �Է��Ͻÿ�: ");
			getchar();
			scanf("%[^\n]s", str);
			palindrome(str);
			break;
		}
		case 4: {
			printf("\n����ǥ��İ��\n");
			char str[100];
			printf("�����Է�: ");
			scanf("%s", str);
			result_stack(str);
		}
		}
	}
	return 0;
}