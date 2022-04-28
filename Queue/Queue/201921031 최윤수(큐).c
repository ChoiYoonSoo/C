#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100
typedef int element;

typedef struct { // ���� ť Ÿ��
	element  data[MAX_QUEUE_SIZE];
	int front, rear;
} QueueType;

void error(char* message) // ���� �Լ�
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init_queue(QueueType* q) // ť �ʱⰪ ����
{
	q->front = q->rear = 0;
}

int is_empty(QueueType* q) // ť ���� ���� �˻�
{
	return (q->front == q->rear);
}

int is_full(QueueType* q) // ť ��ȭ ���� �˻�
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void queue_print(QueueType* q) // ����ť ��� �Լ�
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % (MAX_QUEUE_SIZE);
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

void enqueue(QueueType* q, element item) // ť ���� �Լ�
{
	if (is_full(q))
		error("Queue is full");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) // ť ���� �Լ�
{
	if (is_empty(q))
		error("Queue is empty");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element peek(QueueType* q) // ť ���� �Լ�
{
	if (is_empty(q))
		error("Queue is empty");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main(void) {
	QueueType man;
	init_queue(&man);

	QueueType woman;
	init_queue(&woman);

	int m = 0, w = 0, i = 0;
	int student, random;

	printf("�л��� �� : ");
	scanf("%d", &student);

	while (i++ < student) {
		random = (rand() % 100 + 1);
		printf("��ȣǥ: %d\n", random);
		if ((random % 2) == 1) {
			w++;
			enqueue(&woman, w);
			printf("����%d ���� - ", w);
		}
		else {
			m++;
			enqueue(&man, m);
			printf("����%d ���� - ", m);
		}
		if (!is_empty(&woman) && !is_empty(&man)) {
			printf("����%d <--> ����%d ��Ī\n", dequeue(&woman), dequeue(&man));
		}
		else
			printf("���\n");
		printf("���� ���� ť front : %d  |  rear : %d\n", woman.front, woman.rear);
		printf("���� ���� ť front : %d  |  rear : %d\n", man.front, man.rear);
		printf("======================================\n");
	}
	return 0;
}