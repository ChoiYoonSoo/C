// ��ġ���(1)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define ROWS 3
#define COLS 3

void matrix_transpose1(int matrix[ROWS][COLS], int matrix_t[ROWS][COLS]) // ��ġ���
{
	printf("\n===========��ġ���============\n");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++)
			matrix_t[j][i] = matrix[i][j];
	}
}

int input_matrix(int matrix[ROWS][COLS]) // ����Է�
{
	printf("��� �Է�:\n");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printf("%d %d ��ġ �� �Է�",i,j);
			scanf("%d", &matrix[i][j]);
		}
	}
	return **matrix;
}

void print_matrix(int matrix[ROWS][COLS]) // ������
{
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			printf("[%d] ",matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void add_matrix(int A[ROWS][COLS], int B[ROWS][COLS],int C[ROWS][COLS]) // ��� ����
{
	printf("\n==========��� ����==============\n");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			C[i][j] = A[i][j] + B[i][j];
		}
	}
	
}
void multi_matrix(int A[ROWS][COLS], int B[ROWS][COLS], int C[ROWS][COLS]) // ��� ���� (ù ��° ��� ���� �� ��° ��� ���� ������쿡�� ����)
{
	printf("\n============��� ����============\n");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			for (int c = 0; c < 3; c++) {
				C[i][j] += A[i][c] * B[c][j];
			}
		}
	}

}
int main(void)
{
	int matrix[ROWS][COLS]={0,};
	int matrix_t[ROWS][COLS]={0,};
	int matrix_Add[ROWS][COLS] = {0,};
	int matrix_multi[ROWS][COLS] = { 0, };

	matrix[ROWS][COLS] = input_matrix(&matrix);
	matrix_transpose1(&matrix,&matrix_t);
	print_matrix(&matrix);
	print_matrix(&matrix_t);

	add_matrix(&matrix, &matrix_t,&matrix_Add);
	print_matrix(&matrix_Add);

	multi_matrix(&matrix, &matrix_t, &matrix_multi);
	print_matrix(&matrix_multi);
	return 0;
}