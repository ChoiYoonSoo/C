#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

int convert(char str[]) {
	int n=0;
	int len = strlen(str);
	if (str[0] == '-') {
		for (int i = 1; i < len; i++)
			n += (str[i] - '0') * pow(10, len - i - 1);
		n *= -1;
	}
	else {
		for (int i = 0; i < len; i++)
			n += (str[i] - '0') * pow(10, len - i - 1);
	}
	return n;
}

typedef struct {
	int xpos;
	int ypos;
}Point;

int distance(Point* po) {
	int idx;
	double arr[5];
	for (int i = 0; i < 5; i++) {
		arr[i] = sqrt((double)(po[i].xpos * po[i].xpos) + (po[i].ypos * po[i].ypos));
	}

	double max = arr[0];
	for (int i = 1; i < 5; i++) {
		if (max < arr[i]) {
			max = arr[i];
			idx = i;
		}
	}
	return idx;
}

int Birth_date(char **birth) {
	int month[10];
	int m, i;
	int sameday = 0, person = 0;

	for (int i = 0; i < 10; i++) {
		month[i] = atoi(birth[i]); 
	}
	printf("\n�� ��?: ");
	scanf("%d", &m);

	for (int i = 0; i < 10; i++) {
		sameday = (month[i] / 100) % 100;
		if (sameday == m)
			person += 1;
	}
	return person;
}
int repeat(int m, int n) {
	int sum = 0;
	for (int i = m; i <= n; i++) {
		sum += i;
	}
	return sum;
}

int rotation(int m, int n) {
	if (m > n) return 0;
	else return m + rotation(m + 1, n);
}

int main(void) {
	int n;
	while (1) {    // ���ѷ���
		printf("\n1~4�� �� �����ϼ���.(0���� ������ ���α׷��� �����մϴ�)\n");
		scanf("%d", &n);   // n�ǰ� �Է�
		switch(n) {   //switch�� ����

		case 0: {   // n == 0�̸� �Ʒ����� ����
			printf("\n���α׷� ����!\n");
			return 0;
		}
		case 1: {   // n == 1�̸� �Ʒ����� ����
			 char str[10];
			  printf("���� �Է�: ");
			  scanf("%s", str);
			  printf("��ȯ��Ų ����: %d\n",convert(str));
			  break;
		  }
		case 2: {   // n == 2�̸� �Ʒ����� ����
			Point po[5];
			for (int i = 0; i < 5; i++) {
				printf("%d��° x��ǥ y��ǥ �Է�: ", i + 1);
				scanf("%d %d", &po[i].xpos, &po[i].ypos);
			}
			int idx = distance(&po);
			printf("\n������������ ���� �� ��ǥ: %d %d\n", po[idx].xpos, po[idx].ypos);
			break;
		}
		case 3: {    // n == 3�̸� �Ʒ����� ����
			char* birth[10]= { "20000901", "20100900", "20100304", "19970519", "20030814",
				"19801102", "20181204", "20170607", "20000504", "20180402" };
			printf("���� �� ���� ��: %d\n", Birth_date(&birth));
			break;
		}
		case 4: {    // n == 4�̸� �Ʒ����� ����
			int m, n;
			printf("m�Է�: ");
			scanf("%d", &m);
			printf("n�Է� (m���� Ŀ����): ");
			scanf("%d", &n);
			if (m > n) {
				printf("m���� n�� ���� �� Ŀ���մϴ�.");
				break;
			}
			printf("�ݺ��Լ� m���� n������ ��: %d \n��ȯ�Լ� m���� n������ ��: %d\n", repeat(m, n), rotation(m, n));
			break;
		}
		}
	}
	return 0;
}