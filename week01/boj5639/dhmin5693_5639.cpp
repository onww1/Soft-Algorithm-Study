/*
 * 입력이 들어오는 순서대로 이진 트리를 포인터로 구성
 * 트리 구성이 완료되면 시작점부터 후위순회 시작
 */
#include <cstdio>
using namespace std;

typedef struct Node {
	int num;
	Node *left;
	Node *right;
} Node;

void postOrder(Node *node) {

	if (node == NULL) {
		return;
	}

	postOrder(node->left);
	postOrder(node->right);
	printf("%d\n", node->num);
}

int main() {

	int n;
	scanf("%d", &n);

	// 시작 노드
	Node *start = new Node;
	start->num = n;
	start->left = start->right = NULL;

	// End Of File까지 입력받는다.
	while (scanf("%d", &n) != EOF) {
		Node *node = new Node;
		node->num = n;
		node->left = node->right = NULL;

		Node *cur = start;
		while (true) {
			if (cur->num > node->num) {
				if (cur->left == NULL) {
					cur->left = node;
					break;
				} else {
					cur = cur->left;
				}
			} else {
				if (cur->right == NULL) {
					cur->right = node;
					break;
				}
				else {
					cur = cur->right;
				}
			}
		}
	}

	postOrder(start);

	return 0;
}