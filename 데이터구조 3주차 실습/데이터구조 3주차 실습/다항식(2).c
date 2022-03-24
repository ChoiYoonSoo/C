#define _CRT_SECURE_NO_WARNINGS
#define MAX_TERMS 101
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
	float coef; // ���
	int expon; // ����
} polynomial;

polynomial terms[MAX_TERMS] = { 0,{0,} };
int avail;

char compare(int a, int b)
{
	if (a > b) return '>'; // b�� �������� a�� ������ Ŭ ��� '>' ��ȯ
	else if (a == b) return '='; // a�װ� b���� ������ ������� '=' ��ȯ
	else return '<'; // a�� �������� b�� ������ Ŭ ��� '<' ��ȯ
}
//C�� �ִ� �Լ�
void attach(float coef, int expon)
{
	if (avail > MAX_TERMS) {
		fprintf(stderr, "���� ������ �ʹ� ����\n");
		exit(1);
	}
	terms[avail].coef = coef; // A,B���� ����� ���� �ں��� C�� ����
	terms[avail].expon = expon;
	avail++;
}
void poly_sub(int As, int Ae, int Bs, int Be, int* Cs,int* Ce)
{
	float tempcoef;
	*Cs = avail;
	while (As <= Ae && Bs <= Be)
		switch (compare(terms[As].expon, terms[Bs].expon)) {
		case '>': // A�� ���� > B�� ����
			attach(terms[As].coef, terms[As].expon);
			As++; break;
		case '=': // A�� ���� == B�� ����
			tempcoef = terms[As].coef - terms[Bs].coef;
			if (tempcoef)
				attach(tempcoef, terms[As].expon);
			As++; Bs++; break;
		case '<': // A�� ���� < B�� ����
			attach(terms[Bs].coef, terms[Bs].expon);
			Bs++; break;
		}
	// A�� ������ �׵��� �̵���
	for (; As <= Ae; As++)
		attach(terms[As].coef, terms[As].expon);
	// B�� ������ �׵��� �̵���
	for (; Bs <= Be; Bs++)
		attach(terms[Bs].coef, terms[Bs].expon);
	*Ce = avail - 1;
}

void print_poly(int s, int e) // ���׽� ����Լ�
{
	for (int i = s; i < e; i++) {
		if(terms[i].coef < 0)
			printf(" %3.1fx^%d ", terms[i].coef, terms[i].expon);
		else 
			printf(" + %3.1fx^%d ", terms[i].coef, terms[i].expon);
	}
	if(terms[e].coef < 0)
		printf(" %3.1fx^%d\n", terms[e].coef, terms[e].expon);
	else
		printf(" + %3.1fx^%d\n", terms[e].coef, terms[e].expon);
}
// a���� ����� ����, b���� ����� ���� �Է�
void input_poly(int Ae, int Be)
{
	for (int i = 0; i <= Ae; i++)
	{
		printf("A���� ����� ���� �Է�: ");
		scanf("%f %d", &terms[i].coef, &terms[i].expon);
	}
	for (int i = Ae+1; i <= Be; i++)
	{
		printf("B���� ����� ���� �Է�: ");
		scanf("%f %d", &terms[i].coef, &terms[i].expon);
	}

}
void poly_x(int s, int e) // X�� ����
{
	int x;
	float sum = 0;
	printf("x�� �� �Է�: ");
	scanf("%d", &x);
	for (int i = s; i <= e; i++) {
		sum += terms[i].coef * pow(x, terms[i].expon);
	}
	printf("A(%d) = %.1f\n", x, sum);
}
int main(void)
{
	int As = 0;
	int Ae, Bs, Be, Cs, Ce;
	printf("A���� ���� �Է�: ");
	scanf("%d", &Ae);
	printf("B���� ���� �Է�: ");
	scanf("%d", &Be);
	Ae = Ae - 1;
	Bs = Ae + 1;
	Be = Ae + Be;
	input_poly(Ae, Be);
	avail = Be + 1;
	poly_sub(As, Ae, Bs, Be, &Cs, &Ce);
	print_poly(As, Ae);
	print_poly(Bs, Be);
	printf("\n----------------------------------------------------------------------------- \n");
	print_poly(Cs, Ce);
	poly_x(Cs, Ce);
	return 0;
}