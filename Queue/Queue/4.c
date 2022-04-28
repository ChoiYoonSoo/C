#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 10

typedef struct {
	int front, rear;
	int data[MAX_QUEUE_SIZE];
} QueueType;

//�����Լ�
void error(const char* message) {
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//�ʱ�ȭ �Լ�
void init_queue(QueueType* q)
{
	q->front = q->rear = 0;
}

// ť ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->rear == q->front);
}

// ť ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return (q->front == (q->rear + 1) % MAX_QUEUE_SIZE);
}

// ť ��� �Լ�
void print_queue(QueueType* q)
{
	printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
	if (!is_empty(q)) {
		int i = q->front;
		do {
			i = (i + 1) % MAX_QUEUE_SIZE;
			printf("%d | ", q->data[i]);
			if (i == q->rear)
				break;
		} while (i != q->front);
	}
	printf("\n");
}

// ť ���� �Լ�
void enqueue(QueueType* q, int item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

// ť ���� �Լ�
int dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

int peek(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�.");
	return q->data[(q->front + 1)] % MAX_QUEUE_SIZE;
}

int fibonachi(QueueType* q, int num) {
	if (num == 0) return 0;
	else if (num == 1) return 1;

	for (int i = 2; i <= num; i++) {
		enqueue(q, dequeue(q) + q->data[q->rear]);
	}
	return q->data[q->rear];
}

int main(void) {
	QueueType q;
	init_queue(&q);
	enqueue(&q, 0);
	enqueue(&q, 1);
	int num;
	printf("����� ���ڸ� �Է��Ͻÿ�: ");
	scanf_s("%d", &num);
	printf("%d", fibonachi(&q, num));
	return 0;
}