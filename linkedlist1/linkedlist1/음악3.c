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

typedef struct DLinkNode{ // ���� ���� ��� Ÿ��
	element data;
	struct DLinkNode* llink;
	struct DLinkNode* rlink;
}DLinkNode;

void error(char* message) { // ���� �Լ�
	fprintf(stderr, "%s", message);
	exit(1);
}

void init(DLinkNode* phead) { // ���� ���� ����Ʈ �ʱ�ȭ
	phead->llink = phead;
	phead->rlink = phead;
}

void dinsert_node(DLinkNode* phead, char m[], char s[], char g, int y) { // �������� ��� ����
	DLinkNode* node = phead->rlink;
	DLinkNode* nextnode = (DLinkNode*)malloc(sizeof(DLinkNode));

	strcpy(nextnode->data.music, m);
	strcpy(nextnode->data.singer, s);
	nextnode->data.genre = g;
	nextnode->data.year = y;

	if (phead->rlink == phead || strcmp(node->data.music, nextnode->data.music) >= 0) {
		// �����Ͱ� �ƹ��͵� ���ų� node�� ������ nextnode�� ���Ǻ��� ���ų� Ŭ��� �� ������ ����
		nextnode->llink = phead;
		nextnode->rlink = phead->rlink;
		phead->rlink->llink = nextnode;
		phead->rlink = nextnode;
	}
	else { // �����Ͱ� �ְ� node�� ������ nextnode�� ���Ǻ��� �������
		while (node != phead) {
			if (strcmp(node->data.music, nextnode->data.music) < 0) {
				// node�� ������ nextnode ���Ǻ��� �������
				if (node->rlink == phead || strcmp(node->rlink->data.music, nextnode->data.music) >= 0) {
					// node�� ���� ��ũ�� ���� ó���̰ų� node ������ ������ nextnode ���Ǻ��� Ŭ��� �� ���� ����
					nextnode->rlink = node->rlink;
					nextnode->llink = node;
					node->rlink->llink = nextnode;
					node->rlink = nextnode;
					return;
				}
				node = node->rlink; // �ƴҰ�� node�� �������� �̵����� �����Ҷ����� ��
			}
		}
	}
}

int dlist_length(DLinkNode* phead) { // ����� ����� ���� ��� �Լ�
	int cnt = 0;
	DLinkNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		cnt++;
	}
	return cnt;
}

/*int dlist_length2(DLinkNode* phead) { // ����� ����� ���� ��ȯȣ�� ���
	phead = phead->rlink;
	if (phead->rlink == phead) return 0;
	else return 1 + dlist_length2(phead);
}*/

void dlist_display(DLinkNode* phead) { // ���� ����Ʈ�� ����� ��� ������ ���

	DLinkNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<- %s %s %c %d -> ", p->data.music, p->data.singer, p->data.genre, p->data.year);
	}
	printf("\n");
}

/*void dlist_display2(DLinkNode* phead) { // ��ȯȣ���� �̿��Ͽ� ��� ������ ���
	DLinkNode* p = phead->rlink;
	if (p != phead) {
		printf("<- %s %s %c %d -> ", p->data.music, p->data.singer, p->data.genre, p->data.year);
		return dlist_display2(phead->rlink);
	}
	printf("\n");
}

void dlist_display3(DLinkNode* phead) { // ��ȯȣ���� �̿��Ͽ� ��� ������ �������� ���
	if (phead->rlink != phead) {
		dlist_display3(phead->rlink);
		printf("%s %s %c %d -> ", phead->data.music, phead->data.singer, phead->data.genre, phead->data.year);
	}
}*/

void delete_node(DLinkNode* phead, char name[]) { // ���� ���� ���� �Լ�
	DLinkNode* removed = phead->rlink;
	int n = 0;

	if (removed == phead) return;
	while (removed != phead) {
		if (strcmp(removed->data.music, name) == 0) {
			removed->llink->rlink = removed->rlink;
			removed->rlink->llink = removed->llink;
			free(removed);
			printf("'%s'�� �����Ͽ����ϴ�.\n", name);
			n++;
			return;
		}
		removed = removed->rlink;
	}
	if (n == 0) printf("\n���� �̸��� ������ �����ϴ�.\n");
}

void search_node(DLinkNode* phead, char name[]) { // ���� �������� �˻�
	DLinkNode* p = phead->rlink;
	int n = 0;

	while (p != phead) {
		if (strcmp(p->data.music, name) == 0) {
			printf("\n%s %s %c %d\n", p->data.music, p->data.singer, p->data.genre, p->data.year);
			n++;
		}
		p = p->rlink;
	}
	if (n == 0) printf("\n���� �̸��� ������ �����ϴ�.\n");
}

void Recently_music(DLinkNode* phead) { // �ֱ� �߸��� ��������
	int music = phead->rlink->data.year;
	DLinkNode* p = phead->rlink;

	while (p != phead) {
		if (music <= p->data.year) {
			music = p->data.year;
		}
		p = p->rlink;
	}

	printf("\n========�ֱ� �߸��� ���� ========\n\n");
	for (DLinkNode* p = phead->rlink; p != phead; p = p->rlink) {
		if (music == p->data.year) {
			printf("%s %s %c %d\n", p->data.music, p->data.singer, p->data.genre, p->data.year);
		}
	}
}

void search_genre(DLinkNode* phead, char c) { // Ư�� �帣 ���� �˻�
	DLinkNode* p = phead->rlink;
	while (p != phead) {
		if (c == p->data.genre) {
			printf("%s %s %c %d\n", p->data.music, p->data.singer, p->data.genre, p->data.year);
		}
		p = p->rlink;
	}
}

int main(void) {
	DLinkNode* head = (DLinkNode*)malloc(sizeof(DLinkNode));
	init(head);
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
				dinsert_node(head, m, s, g, y);
			}
			break;
		}
		case 2: {
			printf("\n========���� ���� ���========\n\n");
			dlist_display(head);
			break;
		}
		case 3: {
			printf("����� ���� : %d\n", dlist_length(head));
			break;
		}
		case 4: {
			char name[10];
			printf("������ ���� ������ �Է��ϼ���. : ");
			scanf("%s", name);

			delete_node(head, name);
			break;
		}
		case 5: {
			printf("���α׷��� �����մϴ�.\n");
			return 0;
		}
		/*case 6: {
			printf("\n========��ȯȣ���� �̿��� �������� ���========\n\n");
			dlist_display2(head);
			break;
		}
		case 7: {
			printf("\n========��ȯȣ���� �̿��� �������� ���� ���========\n\n");
			dlist_display3(head);
			printf("NULL\n");
			break;
		}
		case 8: {
			printf("��ȯȣ���� �̿��� ����� ���� : %d\n", dlist_length2(head));
			break;
		}*/
		case 9: {
			char search_music[10];
			printf("ã�� ���� ���� �Է�:\n");
			scanf("%s", search_music);
			search_node(head, search_music);
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