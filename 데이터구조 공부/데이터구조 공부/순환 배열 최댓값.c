#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int max(int* arr,int n,int maxn)
{
	if (n < 0) return maxn;
	else if (maxn < *arr) {
		maxn = *arr;
	}
	arr++;
	max(arr, n - 1,maxn);
}

int main(void)
{	
	int arr[5];
	int n=5;
	for (int i = 0; i < 5; i++) {
		printf("%d��° ���� �Է�: ", i + 1);
		scanf("%d", &arr[i]);
	}
	int maxn = arr[0];
	printf("�迭 �� �ִ�: %d",max(arr, n,maxn));
	return 0;
}