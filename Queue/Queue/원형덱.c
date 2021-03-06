#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5
typedef int element;

typedef struct
{
	element data[MAX_QUEUE_SIZE];
	int rear, front;
}DequeType;

void error(char* massage)
{
	fprintf(stderr, "%s\n", massage);
	exit(1);
}

void init_queue(DequeType* q)
{
	q->rear = q->front = 0;
}

int is_empty(DequeType* q)
{
	return q->rear == q->front;
}

int is_full(DequeType* q)
{
	return (q->rear+1) % MAX_QUEUE_SIZE == q->front;
}

void deque_print(DequeType* q)
{
	printf("DEQUE(front=%d rear=%d) = ", q->front, q->rear);
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

void add_rear(DequeType* q, element item)
{
	if (is_full(q))
		error("Deque is full");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element delete_front(DequeType* q)
{
	if (is_empty(q))
		error("Deque is empty");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

element get_front(DequeType* q)
{
	if (is_empty(q))
		error("Deque is empty");
	return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

void add_front(DequeType* q, element val)
{
	if (is_full(q))
		error("Deque is full");
	q->data[q->front] = val;
	q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(DequeType* q) {
	int prev = q->rear;
	if (is_empty(q))
		error("Deque is empty");
	q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
	return q->data[prev];
}

element get_rear(DequeType* q) {
	if (is_empty(q))
		error("Deque is empty");
	return q->data[q->rear];
}

int main(void) {
	DequeType queue;
	init_queue(&queue);

	for (int i = 0; i < 3; i++) {
		add_front(&queue, i);
		deque_print(&queue);
	}
	for (int i = 0; i < 3; i++) {
		delete_rear(&queue);
		deque_print(&queue);
	}
	return 0;
}