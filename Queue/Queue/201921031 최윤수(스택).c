#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAZE_SIZE 10
#define MAX_STACK_SIZE 100

typedef struct // �� �� ����
{
	short r;
	short c;
}element;

typedef struct // ����Ÿ��
{
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

void init_stack(StackType* s) // ���û���
{
	s->top = -1;
}

int is_full(StackType* s) // ���� ��ȭ���� �˻�
{
	return s->top == (MAX_STACK_SIZE - 1);
}

int is_empty(StackType* s) // ���� ������� �˻�
{
	return s->top == -1;
}

void push(StackType* s, element item) // ���� ���� �Լ�
{
	if (is_full(&s))
	{
		fprintf(stderr, "Stack is full");
		exit(1);
	}
	else s->data[++(s->top)] = item;
}

element pop(StackType* s) // ���� ���� �Լ�
{
	if (is_empty(&s))
	{
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[(s->top)--];
}

element peek(StackType* s) // ���� ��ܿ�� ��ȯ
{
	if (is_empty(&s))
	{
		fprintf(stderr, "Stack is empty");
		exit(1);
	}
	else return s->data[s->top];
}


char maze[MAZE_SIZE][MAZE_SIZE] = { // �̷ι迭 ����
	{'0','0','0','0','0','0','1','1','1','1'},
	{'e','0','0','0','0','1','1','1','1','1'},
	{'0','1','0','1','0','0','0','0','1','1'},
	{'0','0','0','0','1','1','1','0','0','1'},
	{'1','1','1','0','0','0','0','1','0','0'},
	{'1','1','1','1','1','1','0','0','1','0'},
	{'1','1','1','1','1','1','1','0','1','0'},
	{'1','1','1','1','1','1','1','0','0','x'},
	{'1','1','1','1','1','1','1','1','1','1'},
	{'1','1','1','1','1','1','1','1','1','1'},
};

void push_loc(StackType* s, int r, int c) // �̷ΰ� '1'�̰ų� '.'�� �ƴҰ�� push
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.')
	{
		element temp;
		temp.r = r;
		temp.c = c;
		push(s, temp);
	}
}

void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) // �̷� ��� �Լ�
{
	for (int r = 0; r < MAZE_SIZE; r++)
	{
		for (int c = 0; c < MAZE_SIZE; c++)
		{
			printf("%c", maze[r][c]);
		}printf("\n");
	}
}

int main(void)
{
	StackType s;
	while (1) {
		init_stack(&s);

		element here = { 1,0 };
		element rec[MAZE_SIZE * MAZE_SIZE];

		int r, c;
		int num = 2;
		int idx = 0;
		rec[idx++] = here;

		printf("\n\n1��° �̷��� �̵���� -> (%d, %d)\n\n", here.r, here.c);
		while (maze[here.r][here.c] != 'x')
		{
			r = here.r;
			c = here.c;
			maze[r][c] = '.';
			maze_print(maze);
			push_loc(&s, r - 1, c);
			push_loc(&s, r + 1, c);
			push_loc(&s, r, c - 1);
			push_loc(&s, r, c + 1);
			if (is_empty(&s))
			{
				printf("\n�ٸ� �̵���ΰ� �����ϴ�.\n");
				return 0;
			}
			else {
				here = pop(&s);
				rec[idx++] = here;
				printf("\n%d��° �̷��� ������ -> (%d, %d)\n\n", num++, here.r, here.c);
			}
		}

		printf("\nŻ�⼺��\n\n");
		printf("\n========== �̷��� �� �̵���� ==========\n\n");
		for (int i = 0; i < idx; i++) {
			printf("(%d, %d) -> ", rec[i].r, rec[i].c);
		}
		printf("����");
	}
	return 0;
}
