#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

typedef struct {
	char music[10]; // ��������
	char singer[10]; // ����
	char genre; // �帣
	int year; // ��ǥ�⵵
	int time; // ����ð�
}element;

typedef struct DLinkNode { // ���� ���� ��� Ÿ��
	element data;
	struct DLinkNode* llink;
	struct DLinkNode* rlink;
}DLinkNode;

DLinkNode* song;

void error(char* message) { // ���� �Լ�
	fprintf(stderr, "%s", message);
	exit(1);
}

void init(DLinkNode* phead) { // ���� ���� ����Ʈ �ʱ�ȭ
	phead->llink = phead;
	phead->rlink = phead;
}

void dinsert_node(DLinkNode* phead, char m[], char s[], char g, int y, int t) { // �������� ��� ����
	DLinkNode* node = phead->rlink;
	DLinkNode* nextnode = (DLinkNode*)malloc(sizeof(DLinkNode));

	strcpy(nextnode->data.music, m);
	strcpy(nextnode->data.singer, s);
	nextnode->data.genre = g;
	nextnode->data.year = y;
	nextnode->data.time = t;

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

void dlist_display(DLinkNode* phead) { // ���� ����Ʈ�� ����� ��� ������ ���

	DLinkNode* p;
	if (phead->rlink == phead) {
		printf("�������� ����ֽ��ϴ�.\n");
		return;
	}
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("<- %s %s %c %d %d -> ", p->data.music, p->data.singer, p->data.genre, p->data.year, p->data.time);
	}
	printf("\n");
}

void delete_node(DLinkNode* phead, char name[]) { // ���� ���� ���� �Լ�
	DLinkNode* removed = phead->rlink;
	int n = 0;

	if (removed == phead) {
		printf("�������� ����ֽ��ϴ�.\n");
		return;
	}

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

DLinkNode* search_node(DLinkNode* phead, char name[]) { // ���� �������� �˻�
	DLinkNode* p = phead->rlink;
	int n = 0;

	while (p != phead) {
		if (strcmp(p->data.music, name) == 0) {
			return p;
		}
		p = p->rlink;
	}
	return NULL;
}

DLinkNode* Recently_music(DLinkNode* phead) { // �ֱ� �߸��� ��������
	DLinkNode* p = phead->rlink;
	DLinkNode* music = phead->rlink;

	if (p == phead) return NULL;

	printf("\n========�ֱ� �߸��� ���� ========\n\n");
	for (; p != phead; p = p->rlink) {
		if (p->data.year >= music->data.year) {
			music = p;
		}
	}
	return music;
}

void search_genre(DLinkNode* phead, char c) { // Ư�� �帣 ���� �˻�
	DLinkNode* p = phead->rlink;
	int n = 0;
	if (p == phead) {
		printf("�������� ����ֽ��ϴ�.\n");
		return;
	}
	while (p != phead) {
		if (c == p->data.genre) {
			printf("%s %s %c %d %d\n", p->data.music, p->data.singer, p->data.genre, p->data.year, p->data.time);
			n++;
		}
		p = p->rlink;
	}
	if (n == 0) printf("�Է��� �帣�� ������ �����ϴ�.\n");
}

void play_music(DLinkNode* phead) { // ���� ���� ���
	DLinkNode* p;
	int cnt = song->data.time;

	for (p = phead->rlink; p != phead; p = p->rlink) {
		if (p == song) {
			printf(" <- playing ~ %s ����ð�: %d�� -> ", p->data.music, p->data.time);
		}
		else
			printf(" <- %s %d -> ", p->data.music, p->data.time);
	}

	for (int i = 1; i <= cnt; i++) {
		printf("\n������ %d...\n", i);
		Sleep(1000);
	}
	printf("\n����Ϸ�\n");
}

void start_music(DLinkNode* phead, char ch) { // ���� �̵�
	switch (ch) {
	case 'P':
		song = song->rlink;
		if (song == phead) {
			song = song->rlink;
		}
		play_music(phead);
		break;
	case '>':
		song = song->rlink;
		if (song == phead) {
			song = song->rlink;
		}
		play_music(phead);
		break;
	case '<':
		song = song->llink;
		if (song == phead) {
			song = song->llink;
		}
		play_music(phead);
		break;
	case 'F': case 'f':
		song = phead->rlink;
		play_music(phead);
		break;
	case 'L': case 'l':
		song = phead->llink;
		play_music(phead);
		break;
	}
}

void all_free(DLinkNode* phead) {
	DLinkNode* removed = phead->rlink;

	while (removed != phead) {
		phead->rlink = removed->rlink;
		removed->rlink->llink = phead;
		free(removed);
		removed = phead->rlink;
	}
	printf("\nAll Free!\n");
}

int main(void) {
	DLinkNode* head = (DLinkNode*)malloc(sizeof(DLinkNode));
	init(head);
	song = head;
	char m[10];
	char s[10];
	char g;
	int y, n, t;

	while (1) {
		printf("\n0. ����\n");
		printf("1. �Է�\n");
		printf("2. ��� ���\n");
		printf("3. ���� ���\n");
		printf("4. ��� ����\n");
		printf("5. ���ǰ˻�\n");
		printf("6. �ֱ� �߸��� ��������\n");
		printf("7. ���� �帣�˻�\n");
		printf("8. ����޴�\n");
		scanf("%d", &n);

		switch (n) {
		case 0: {
			all_free(head);
			printf("���α׷��� �����մϴ�.\n");
			return 0;
		}
		case 1: {
			printf("��������, ����, �帣, ��ǥ�⵵, ����ð� �Է�: ");
			scanf("%s %s %c %d %d", m, s, &g, &y, &t);

			if (g != 'B' && g != 'C' && g != 'H' && g != 'J' && g != 'T') {
				printf("\n\n�帣�� �߸� �Է��Ͽ����ϴ�.\n");
			}
			else {
				dinsert_node(head, m, s, g, y, t);
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
			DLinkNode* p;
			char search_music[10];
			printf("ã�� ���� ���� �Է�:\n");
			scanf("%s", search_music);
			p = search_node(head, search_music);

			if (p != NULL) {
				printf("\n%s %s %c %d %d\n", p->data.music, p->data.singer, p->data.genre, p->data.year, p->data.time);
			}
			else printf("������ ������ �����ϴ�.\n");
			break;
		}
		case 6: {
			DLinkNode* p;
			p = Recently_music(head);
			if (p != NULL) {
				printf("%s %s %c %d %d\n", p->data.music, p->data.singer, p->data.genre, p->data.year, p->data.time);
			}
			else printf("������ ������ �����ϴ�.\n");
			break;
		}
		case 7: {
			char c;
			printf("ã���� ������ �帣�� �Է��ϼ���.(B,C,H,J,T) : ");
			getchar();
			scanf("%c", &c);

			if (c != 'B' && c != 'C' && c != 'H' && c != 'J' && c != 'T') {
				printf("\n�帣�� �߸� �Է��Ͽ����ϴ�.\n");
				break;
			}
			printf("\n========ã���� �帣�� ���� ����========\n\n");
			search_genre(head, c);
			break;
		}
		case 8: {
			char ch;
			printf("\n=========����޴�========\n");
			printf("P ���\n");
			printf("> ������\n");
			printf("< ������\n");
			printf("L/l ��������\n");
			printf("F/f ó����\n");
			getchar();
			scanf("%c", &ch);
			
			start_music(head, ch);
			break;
		}
		}
	}
	return 0;
}