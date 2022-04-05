//��ġ���(2)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 100

typedef struct
{
	int row; //��
	int col; //��
	int value; //��
}element;

typedef struct
{
	element data[SIZE]; //���� ������ �迭
	int rows; //���� ����
	int cols; //���� ����
	int terms; //���� ����
}SparseMatrix;

SparseMatrix input_Matrix(SparseMatrix a) // ��� �Է�
{
	printf("���� ���� �Է�: ");
	scanf("%d", &a.rows);
	printf("���� ���� �Է�: ");
	scanf("%d", &a.cols);
	printf("���� ���� �Է�: ");
	scanf("%d", &a.terms);

	for (int i = 0; i < a.terms; i++) {
		printf("%d�� �� �� �� �Է� :",i+1);
		scanf("%d %d %d", &a.data[i].row, &a.data[i].col, &a.data[i].value);
	}

	return a;
}

SparseMatrix matrix_transpose2(SparseMatrix p) // ��ġ���
{
	SparseMatrix b;

	int bidx;
	b.rows = p.cols;
	b.cols = p.rows;
	b.terms = p.terms;

	if (p.terms > 0) {

		bidx = 0;
		for (int c = 0; c < p.cols; c++) {
			for (int i = 0; i < p.terms; i++) {
				if (p.data[i].col == c) {

					b.data[bidx].row = p.data[i].col;
					b.data[bidx].col = p.data[i].row;
					b.data[bidx].value = p.data[i].value;
					bidx++;
				}
			}
		}
	}
	return b;

}
void print_matrix(SparseMatrix p)
{
	printf("\n=======================\n");
	for (int i = 0; i < p.terms; i++)
		printf("(%d, %d, %d)\n", p.data[i].row, p.data[i].col, p.data[i].value);
	printf("\n=======================\n");
}
int main(void)
{	
	SparseMatrix a={0,};
	SparseMatrix b={0,};

	a = input_Matrix(a);
	print_matrix(a);
	b = matrix_transpose2(a);
	print_matrix(b);
	return 0;
}