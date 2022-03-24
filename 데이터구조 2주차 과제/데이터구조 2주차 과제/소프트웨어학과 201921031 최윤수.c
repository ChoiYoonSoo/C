#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct {
	double x;
	double y;
}number;

void strjud(char* str){
	int i=0;
	int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;
	int ncnt = 0;
	while (str[i] != '\0') {
		if (str[i] >= 65 && str[i] <= 90) { // ���� ���� �빮������ �Ǻ�
			cnt1++;
		}
		else if (str[i] >= 97 && str[i] <= 122) { // ���� ���� �ҹ������� �Ǻ�
			cnt2++;
		}
		else if (str[i] == '!' || str[i] == '?' || str[i] == '#' || str[i] == '*' || str[i] == '$') { // ���� Ư���������� �Ǻ�
			cnt3++;
		}
		else if (str[i] >= 48 && str[i] <= 57) { // ���� ���� 0~9�������� �Ǻ�
			cnt4++;
		}
		else // ���ǿ� �ش���� �ʴ°��
			ncnt++;
		i++;
	}

	if (cnt1 >= 1 && cnt2 >=1 && cnt3 >= 1 && cnt4 >= 1) { // ������ ��� �����Ǵ°��
		printf("���ڿ����� ���ĺ� �빮��, �ҹ���, ����, Ư������(!,?,*,#,$)�� ��� ���ԵǾ��ֽ��ϴ�\n");
		if (1 <= ncnt) { // ������ ��� ���������� �ٸ����ڵ� ���Ե��ִ� ���
			printf("�ش����� �ʴ� ���ڵ� ���ԵǾ��ֽ��ϴ�.\n");
		}
	}
	if (cnt1 == 0) { // �빮�ڰ� ���ԵǾ����� �ʴ� ���
		printf("�빮�ڰ� ���ԵǾ����� �ʽ��ϴ�\n");
	}
	if (cnt2 == 0) { // �ҹ��ڰ� ���ԵǾ����� �ʴ� ���
		printf("�ҹ��ڰ� ���ԵǾ����� �ʽ��ϴ�\n");
	}
	if (cnt3 == 0) { // Ư�����ڰ� ���ԵǾ����� �ʴ°��
		printf("Ư������(!,?,*,#,$)�� ���ԵǾ����� �ʽ��ϴ�\n");
	}
	if (cnt4 == 0) { // ���ڰ� ���ԵǾ����� �ʴ� ���
		printf("���ڰ� ���ԵǾ����� �ʽ��ϴ�\n");
	}
	if (i == ncnt) { // ������ �������� �ʴ� ���
		printf("���ڿ����� ���ĺ� �빮��, �ҹ���, ����, Ư������(!,?,*,#,$)�� ��� ���ԵǾ����� �ʽ��ϴ�\n");
	}

	if (i < 10) { // ���ڿ� ���� �Ǻ�
		printf("���ڿ��� ���̰� 10�����Դϴ�.\n");
	}
	else printf("���ڿ��� ���̰� 10�̻��Դϴ�.\n");
}
void sum(number* ptr,int n,double resultx, double resulty) {
	if (n == 0) {
		printf("%.1f + %.1fi\n", resultx, resulty);
		return 0;
	}
	else {
		resultx +=(*ptr).x; // �Ǽ��κ��� ��
		resulty +=(*ptr).y; // ����κ��� ��
		ptr++; // ������° ������ �̵�
		sum(ptr, n - 1, resultx, resulty);
	}
}
int length(char *str) {
	if (*str == '\0') return 0;
	else return 1 + length(str + 1);
}
int Binsearch(int * arr, int bottom, int top, int n,int idx) {
	int mid = (bottom + top) / 2;
	idx++;
	printf("%d��° ��ġ arr[%d] �� %d\n",idx, mid, arr[mid]);
	if (n == arr[mid]) {
		return printf("���������� ��ġ: arr[%d] �� : %d \n", mid, arr[mid]);
	}
	else if (n < arr[mid])
		return Binsearch(arr, bottom, mid, n,idx);
	else
		return Binsearch(arr, mid, top, n,idx);
}
int main(void)
{
	int n;
	while (1) {
		printf("\n1~4���� �����ϼ���. (0���� ������ ���α׷� ����!): ");
		scanf("%d", &n);

		switch (n) {
		case 0: { // 0���� ������ ���α׷� ����
			printf("���α׷� ����!");
			return 0;
		}
		case 1: { // 1���� ������ 1�� ����Ǯ��
			char str[100];
			printf("\n���� 100���� ���ڿ� �Է�: ");
			scanf("%s", str);
			strjud(str);
			break;
		}
		case 2: { // 2���� ������ 2�� ����Ǯ��
			int n;
			double resultx = 0;
			double resulty = 0;
			printf("n�� �Է��ϼ���\n");
			scanf("%d", &n);
			number * ptr = (number*)malloc(sizeof(number) * n);
			for (int i = 0; i < n; i++) {
				printf("%d��° ���Ҽ� �Է�: ",i+1);
				scanf("%lf %lf", &ptr[i].x, &ptr[i].y);
			}
			sum(ptr,n,resultx,resulty);
			free(ptr);
			break;
		}
		case 3: { // 3���� ������ 3�� ����Ǯ��
			char str[100];
			int len = 1;
			printf("���� 100���� ���ڿ� �Է�: ");
			scanf("%s", str);
			printf("�Է¹��� ���ڿ��� ���� %d\n",length(str,len));
			break;
			
		}
		case 4: { // 4���� ������ 4�� ����Ǯ��
			int arr[10];
			int n;
			int temp = 0;
			int a = 0;
			int idx = 0;
			printf("10���� ���� �Է�: \n");
			for (int i = 0; i < 10; i++) {
				scanf("%d", &arr[i]);
			}

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10-1; j++) {
					if (arr[j] > arr[j + 1]) {
						temp = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = temp;
					}
				}
			}
			for (int i = 0; i < 10; i++) {
				printf("%d ", arr[i]);
			}
			int bottom = 0; // �迭�� ù��° �ε��� ����
			int top = 10; // �迭�� ������ �ε��� ����
			printf("\nã����� ���� �Է�: ");
			scanf("%d", &n);
			for (int i = 0; i < 10; i++) { // �迭�� ã�� ���ڰ� �ִ��� �Ǻ�
				if (n == arr[i])
					a += 1;
			}
			if (a >= 1)
				Binsearch(arr, bottom, top, n,idx);
			else
				printf("ã�¼��ڰ� �迭�� �����ϴ�.\n");

			break;
		}
		}
	}
	return 0;
}