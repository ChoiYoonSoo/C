#define _CRT_SECURE_NO_WARNINGS
#define MAX(a,b) ((a)>(b))?(a):(b)
#define MAX_DEGREE 101
#include <stdio.h>
#include <math.h>

typedef struct
{
	int degree; // ����
	float coef[MAX_DEGREE]; // ���
}Polynomial;

Polynomial input_poly(Polynomial p) // A��, B���� ���� ��� �Է�
{
	printf("���� ���� �Է�: ");
	scanf("%d", &p.degree);
	for (int i = 0; i <= p.degree; i++) {
		printf("���� ��� �Է�: ");
		scanf("%f", &p.coef[i]);
	}
	printf("\n");
	return p;
}
void print_poly(Polynomial p) // �Է¹��� ���׽� ���
{
	for (int i = p.degree; i > 0; i--) {
		if (p.coef[p.degree - i] != 0) {
			if (p.coef[p.degree - i] >= 0)
				printf(" + %3.1fx^%d", p.coef[p.degree - i], i);
			else
				printf(" %3.1fx^%d", p.coef[p.degree - i], i);
		}
	}
	if (p.coef[p.degree] != 0) {
		if (p.coef[p.degree] >= 0)
			printf(" + %3.1f\n", p.coef[p.degree]);
		else
			printf(" %3.1f\n", p.coef[p.degree]);
	}
}
void poly_x(Polynomial p) // x�� ����
{
	int x;
	float sum = 0;
	int degree = p.degree;
	printf("\nx�� �� �Է� : ");
	scanf("%d", &x);


	for (int i = 0; i <= p.degree; i++)
	{
		sum += p.coef[i] * pow(x, degree--);
	}
	printf("A(%d) = %.1f\n", x, sum);
}
Polynomial poly_sub(Polynomial A, Polynomial B) // �� ���׽��� ����
{
	Polynomial C;
	int Apos = 0, Bpos = 0, Cpos = 0;
	int degree_a = A.degree;
	int degree_b = B.degree;
	C.degree = MAX(A.degree, B.degree);
	while (degree_a == degree_b) { // �� ���׽��� ������ �������
		if (A.coef[Apos] == B.coef[Bpos]) { // �� ���׽��� ����� ������� 0�̱� ������ ���� x
			Apos++; Bpos++;
			degree_a--; degree_b--; // ���� ���̱�
			C.degree--; // C���� ���� ���̱� (�ְ����� ��갪�� 0�̸� ������ϱ⶧��)
		}
		else
			break;
	}
	while (Apos <= A.degree && Bpos <= B.degree) 
	{
		if (degree_a > degree_b) { // a���� ������ b���� �������� Ŭ ��� c�׿� a�� ����
			C.coef[Cpos++] = A.coef[Apos++];
			degree_a--;
		}
		else if (degree_a == degree_b) { // a�װ� b���� ������ ������� �� �� c�׿� ����
			C.coef[Cpos++] = A.coef[Apos++] - B.coef[Bpos++];
			degree_a--; degree_b--;
		}
		else { // b���� ������ a���� �������� Ŭ ��� c�׿� b�� ����
			C.coef[Cpos++] = B.coef[Bpos++];
			degree_b--;
		}
	}
	return C;
}
int main(void)
{
	Polynomial a = { 0,{0,} };
	Polynomial b = { 0,{0,} };
	Polynomial c;
	a = input_poly(a);
	b = input_poly(b);
	c = poly_sub(a, b);
	print_poly(a);
	print_poly(b);
	printf("\n------------------------\n");
	print_poly(c);
	poly_x(c);
	return 0;

}