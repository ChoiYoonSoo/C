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

LinkNode* insert_node(LinkNode* head, char m[], char s[], char g, int y) { // �������� ��� ����
	LinkNode* node = head;
	LinkNode* nextnode = (LinkNode*)malloc(sizeof(LinkNode));

	strcpy(nextnode->data.music, m);
	strcpy(nextnode->data.singer, s);
	nextnode->data.genre = g;
	nextnode->data.year = y;

	if (head == NULL || strcmp(node->data.music, nextnode->data.music) >= 0) {
		// �� �����̰ų� node�� ������ nextnode�� ���Ǻ��� ���ų� Ŭ��� �� ������ ����
		nextnode->link = head;
		head = nextnode;
		return head;
	}
	else { // ������� �ƴϰ� node�� ������ nextnode�� ���Ǻ��� �������
		while (node != NULL) {
			if (strcmp(node->data.music, nextnode->data.music) < 0) {
				// node�� ������ nextnode ���Ǻ��� �������
				if (node->link == NULL || strcmp(node->link, nextnode->data.music) >= 0) {
					// node�� ������ nextnode ���Ǻ��� �۰� node�� ������ NULL�̰ų� node ������ ������ nextnode ���Ǻ��� Ŭ��� �� ���� ����
					nextnode->link = node->link;
					node->link = nextnode;
					return head;
				}
				node = node->link; // �ƴҰ�� node�� �������� �̵����� �����Ҷ����� ��
			}
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

int list_length2(LinkNode* head) { // ����� ����� ���� ��ȯȣ�� ���
	if (head == NULL) return 0;
	else return 1 + list_length2(head->link);
}

void list_display(LinkNode* head) { // ���� ����Ʈ�� ����� ��� ������ ���

	LinkNode* p = head;

	while (p != NULL) {
		printf("%s %s %c %d -> ", p->data.music, p->data.singer, p->data.genre, p->data.year);
		p = p->link;
	}
	printf("NULL\n");
}

void list_display2(LinkNode* head) { // ��ȯȣ���� �̿��Ͽ� ��� ������ ���
	if (head != NULL) {
		printf("%s %s %c %d -> ", head->data.music, head->data.singer, head->data.genre, head->data.year);
		return list_display2(head->link);
	}
	printf("NULL\n");
}

void list_display3(LinkNode* head) { // ��ȯȣ���� �̿��Ͽ� ��� ������ �������� ���
	if (head != NULL) {
		list_display3(head->link);
		printf("%s %s %c %d -> ", head->data.music, head->data.singer, head->data.genre, head->data.year);
	}
}

LinkNode* delete_node(LinkNode* head, char name[]) { // ���� ���� ���� �Լ�
	LinkNode* removed;
	LinkNode* dnode = head;
	int n = 0;

	if (head == NULL) return NULL;
	if (strcmp(dnode->data.music, name) == 0) { // ��� ��� �κ� ����
		removed = head;
		head = removed->link;
		free(removed);
		printf("'%s'�� �����Ͽ����ϴ�.\n", name);
		return head;
	}

	while (dnode->link != NULL) { // �߰� ��� �κ� ����
		if (strcmp(dnode->link, name) == 0) {
			removed = dnode->link;
			dnode->link = removed->link;
			free(removed);
			printf("'%s'�� �����Ͽ����ϴ�.\n", name);
			n++;
			continue; // ���� ������ �� �����ϱ�����
		}
		dnode = dnode->link;
	}
	if (n == 0) printf("\n���� �̸��� ������ �����ϴ�.\n");
	return head;
}

LinkNode* search_node(LinkNode* head,char name[]) { // ���� �������� �˻�
	LinkNode* p = head;
	while (p != NULL) {
		if (strcmp(p->data.music, name) == 0) {
			return p;
		}
		p = p->link;
	}
	return NULL;
}

void Recently_music(LinkNode* head) { // �ֱ� �߸��� ��������
	int music = head->data.year;
	LinkNode* p = head;

	while (p != NULL) {
		if (music <= p->data.year) {
			music = p->data.year;
		}
		p = p->link;
	}

	printf("\n========�ֱ� �߸��� ���� ========\n\n");
	for (LinkNode* p = head; p != NULL; p = p->link) {
		if (music == p->data.year) {
			printf("%s %s %c %d\n", p->data.music, p->data.singer, p->data.genre, p->data.year);
		}
	}
}

void search_genre(LinkNode* head, char c) { // Ư�� �帣 ���� �˻�
	LinkNode* p = head;
	while (p != NULL) {
		if (c == p->data.genre) {
			printf("%s %s %c %d\n", p->data.music, p->data.singer, p->data.genre, p->data.year);
		}
		p = p->link;
	}
}

int main(void) {
	LinkNode* head = NULL;
	char m[10];
	char s[10];
	char g;
	int y, n;

	while (1) {
		printf("\n1. �Է�\n2. ��� ���\n3. ���� ���\n4. ��� ����\n5. ����\n6. ��ȯ ����Ʈ\n7. ��ȯ ���� ����Ʈ\n8. ��ȯ ��尹��\n9. ���ǰ˻�\n10. �ֱ� �߸��� ��������\n11. ���� �帣�˻�\n");
		scanf("%d", &n);

		switch (n) {
		case 1: {
			printf("��������, ����, �帣, ��ǥ�⵵ �Է�: ");
			scanf("%s %s %c %d", m, s, &g, &y);

			if (g != 'B' && g != 'C' && g != 'H' && g != 'J' && g != 'T') {
				printf("\n\n�帣�� �߸� �Է��Ͽ����ϴ�.\n");
			}
			else {
				head = insert_node(head, m, s, g, y);
			}
			break;
		}
		case 2: {
			printf("\n========���� ���� ���========\n\n");
			list_display(head);
			break;
		}
		case 3: {
			printf("����� ���� : %d\n", list_length(head));
			break;
		}
		case 4: {
			char name[10];
			printf("������ ���� ������ �Է��ϼ���. : ");
			scanf("%s", name);

			head = delete_node(head, name);
			break;
		}
		case 5: {
			printf("���α׷��� �����մϴ�.\n");
			return 0;
		}
		case 6: {
			printf("\n========��ȯȣ���� �̿��� �������� ���========\n\n");
			list_display2(head);
			break;
		}
		case 7: {
			printf("\n========��ȯȣ���� �̿��� �������� ���� ���========\n\n");
			list_display3(head);
			printf("NULL\n");
			break;
		}
		case 8: {
			printf("��ȯȣ���� �̿��� ����� ���� : %d\n", list_length2(head));
			break;
		}
		case 9: {
			LinkNode* sm;
			char search_music[10];
			printf("ã�� ���� ���� �Է�:\n");
			scanf("%s", search_music);

			sm = search_node(head, search_music);
			if (sm == NULL) {
				printf("\nã�� ������ �����ϴ�.\n");
				break;
			}
			printf("\nã�� ������ ���� : %s %s %c %d\n",sm->data.music,sm->data.singer,sm->data.genre,sm->data.year);
			break;
		}
		case 10: {
			Recently_music(head);
			break;
		}
		case 11: {
			char c;
			printf("ã���� ������ �帣�� �Է��ϼ���. : ");
			getchar();
			scanf("%c", &c);

			if (c != 'B' && c != 'C' && c != 'H' && c != 'J' && c != 'T') {
				printf("�帣�� �߸� �Է��Ͽ����ϴ�.\n");
				break;
			}
			printf("\n========ã���� �帣�� ���� ����========\n\n");
			search_genre(head, c);
			break;
		}
		}
	}
	return 0;
}