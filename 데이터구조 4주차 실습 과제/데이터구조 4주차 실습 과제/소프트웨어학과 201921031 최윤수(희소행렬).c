#define _CRT_SECURE_NO_WARNINGS
#define MAX_TERMS 100
#include <stdio.h>

typedef struct {
	int row; // �� ��ġ
	int col; // �� ��ġ
	int value; // ��
}element;

typedef struct {
	element data[MAX_TERMS];
	int rows; // �� ����
	int cols; // �� ����
	int terms; // �� ����
}SparseMatrix;

SparseMatrix save_matrix(int r, int c, int A[][10]) { // �������� SparseMatrix ������ �����ϴ� �Լ�

	SparseMatrix a;
	int idx = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			if (A[i][j] != 0) {
				a.data[idx].row = i;
				a.data[idx].col = j;
				a.data[idx++].value = A[i][j];
			}
		}
	}
	a.rows = r;
	a.cols = c;
	a.terms = idx;
	return a;
}

SparseMatrix add_matrix(SparseMatrix a, SparseMatrix b) { // �� ���� SparseMatrix �����ϴ� �Լ�
	
	SparseMatrix c;
	int aindex = 0, bindex = 0, cindex = 0;

	if (a.rows != b.rows || a.cols != b.cols) { // �� ����� ��� ���� �ٸ��� ���� �Ұ���
		printf("�� ����� ������ �Ұ����մϴ�.\n");
		exit(1);
	}
	c.rows = a.rows;
	c.cols = a.cols;

	while ((aindex < a.terms) && (bindex < b.terms)) {
		int anum = a.data[aindex].row * a.cols + a.data[aindex].col; // A��ġ
		int bnum = b.data[bindex].row * b.cols + b.data[bindex].col; // B��ġ

		if (anum < bnum) { // A��ġ���� B��ġ�� �� ũ�� ����
			c.data[cindex++] = a.data[aindex++];
		}
		else if (anum == bnum) { // A��ġ�� B��ġ�� ���� ��� �������� ����
			if (a.data[aindex].value + b.data[bindex].value != 0) { // A+B ���� 0�� �ƴϸ� ����
				c.data[cindex].row = a.data[aindex].row;
				c.data[cindex].col = a.data[aindex].col;
				c.data[cindex++].value = a.data[aindex++].value + b.data[bindex++].value;
			}
			else {
				aindex++; bindex++;
			}
		}
		else { // A��ġ���� B��ġ�� �� ũ�� ����
			c.data[cindex++] = b.data[bindex++];
		}
	}
	for (; aindex < a.terms;) // A���� ������ �κ� ����
		c.data[cindex++] = a.data[aindex++];

	for (; bindex < b.terms;) // B���� ������ �κ� ����
		c.data[cindex++] = b.data[bindex++];

	c.terms = cindex;
	return c;
}

void print1_matrix(SparseMatrix a) { // 0�� ������ ������ ��� ����ϴ� �Լ�
	
	int idx = 0;
	int n = 0;
	printf("0�� ������ ������ ��� ���\n\n");

	for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.cols; j++) {
			if (a.data[idx].row == i) {
				if (a.data[idx].col == j)
					printf("%3d", a.data[idx++].value);
				else
					printf("%3d",n);
			}
			else
				printf("%3d",n);
		}
		printf("\n");
	}
	printf("\n");
}

void print2_matrix(SparseMatrix a) { // 0�� �������� ���� ������ ��� ����ϴ� �Լ�
	
	int idx = 0;
	printf("0�� �������� ���� ������ ��� ���\n\n");

	for (int i = 0; i < a.rows; i++) {
		for (int j = 0; j < a.cols; j++) {
			if (a.data[idx].row == i) {
				if (a.data[idx].col == j) {
					printf("row: %d  col: %d  value: %d\n", a.data[idx].row, a.data[idx].col, a.data[idx].value);
					idx++;
				}
			}
		}
	}
	printf("\n");
}

int main(void) {

	int a[8][10] = { { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0,-3, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0,-1, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

	int b[8][10] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0,-1, 0, 0, 0, 0, 0, 0 },
				     { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 2, 0, 0, 0 } };

	int c[8][10] = { { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },
				   	 { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 3 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0,-2, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
					 { 0, 0, 0, 0, 0, 0, 4, 0, 0, 0 } };

	int n;
	int rr = 8, cc = 10;
	SparseMatrix SA, SB, SC, result;

	SA = save_matrix(rr, cc, a);
	SB = save_matrix(rr, cc, b);
	SC = save_matrix(rr, cc, c);

	while (1) {
		printf("0~3�� �� �����ϼ���.\n");
		printf("0. ���α׷� ����\n1. 0�� ������ ������ ��� ���\n2. 0�� �������� ���� ������ ��� ���\n3. �� ���� ������� ���\n");
		scanf("%d", &n);
		switch (n) {
		case 0: { // ���α׷� ����
			printf("���α׷��� �����մϴ�.\n");
			return 0;
		}
		case 1: { // 0�� ������ ������ ��� ����ϴ� �Լ� ����
			printf("A�� "); print1_matrix(SA);
			printf("B�� "); print1_matrix(SB);
			printf("C�� "); print1_matrix(SC);
			break;
		}
		case 2: { // 0�� �������� ���� ������ ��� ����ϴ� �Լ� ����
			printf("A�� "); print2_matrix(SA);
			printf("B�� "); print2_matrix(SB);
			printf("C�� "); print2_matrix(SC);
			break;
		}
		case 3: { // �� ���� ���� ����� ������ ��� ����ϴ� �Լ� ����
			result = add_matrix(SA, SB);
			printf("A+B�� "); print1_matrix(result);
			result = add_matrix(SA, SC);
			printf("A+C�� "); print1_matrix(result);
			result = add_matrix(SB, SC);
			printf("B+C�� "); print1_matrix(result);
			break;
		}
		}
	}
	
	return 0;
}