#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char music[10]; // ��������
	char singer[10]; // ����
	char genre; // �帣
	int year; // ��ǥ�⵵
}element;

typedef struct {
	element data;
	struct LinkNode* link;
}LinkNode;

void error(char* message) { // ���� �Լ�
	fprintf(stderr, "%s", message);
	exit(1);
}

LinkNode* insert_node(LinkNode* head, char m[],char s[], char g,int y) { // �������� ��� ����
	LinkNode* node = head;
	LinkNode* nextnode = (LinkNode*)malloc(sizeof(LinkNode));

	strcpy(nextnode->data.music, m);
	strcpy(nextnode->data.singer, s);
	nextnode->data.genre = g;
	nextnode->data.year = y;

	if (head == NULL || strcmp(node->data.music, nextnode->data.music) >= 0) {
		nextnode->link = head;
		head = nextnode;
		return head;
	}
	else {
		while (node != NULL){
			if (strcmp(node->data.music, nextnode->data.music) <= 0) {
				if (node->link == NULL || strcmp(node->data.music, nextnode->data.music) >= 0) {
					nextnode->link = node->link;
					node->link = nextnode;
					return head;
				}
			}
			node = node->link;
		}
	}
}

int list_length(LinkNode* head) { // ����� ����� ���� ��� �Լ�
	int cnt = 0;
	while (head != NULL) {
		head = head->link;
		cnt++;
	}
	return cnt;
}

void list_display(LinkNode* head) { // ���� ����Ʈ�� ����� ��� ������ ���

	LinkNode* p = head;

	while (p != NULL) {
		printf("%s %s %c %d -> ", p->data.music, p->data.singer, p->data.genre, p->data.year);
		p = p->link;
	}
	printf("NULL\n");
}

int main(void) {
    LinkNode* head = NULL;
    char m[10];
    char s[10];
    char g;
    int y,n;

	while (1) {
		printf("\n1. �Է� 2. ��� ��� 3. ���� ��� 4. ����\n");
		scanf("%d", &n);

		switch (n) {
		case 1: {
			printf("��������, ����, �帣, ��ǥ�⵵ �Է�: ");
			scanf("%s %s %c %d", m, s, &g, &y);

			if (g != 'B' && g != 'C' && g != 'H' && g != 'J' && g != 'T') {
				printf("�帣�� �߸� �Է��Ͽ����ϴ�.\n");
				break;
			}
			else {
				head = insert_node(head, m, s, g, y);
			}
			break;
		}
		case 2: {
			list_display(head);
			break;
		}
		case 3: {
			printf("����� ���� : %d\n", list_length(head));
			break;
		}
		case 4: {
			printf("���α׷��� �����մϴ�.\n");
			return 0;
		}
		}
	}
	return 0;
}