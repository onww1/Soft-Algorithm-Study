/*
 *  BOJ 1991. 트리 순회
 * 
 *  Node라는 구조체를 만들고, 그 안에 left child, right child와 
 *  value를 저장했습니다. 그렇게 입력을 받으면서 Node를 연결하여 Tree를 만들고,
 *  순차적으로 preorder, inorder, postorder 순회를 했습니다.
 */

#include <cstdio>
using namespace std;

struct Node { 
	char val;
	Node *left, *right;

	Node(char val): val(val), left(0), right(0){}
};

void preorder(Node *node);
void inorder(Node *node);
void postorder(Node *node);

// val을 가지고 있는 node를 찾아서 반환해주는 함수
Node *find(Node *node, char val) {
	if (node == 0 || node->val == '.') return NULL; // node가 0이면 없는 것이고, val이 '.'이면 그것도 없는 것이므로
	if (node->val == val) return node;              // val이 node의 value와 같으면 이 node를 반환
	
	Node *ret = find(node->left, val);              // 왼쪽부터 탐색
	if (ret == NULL) ret = find(node->right, val);  // 왼쪽에 없으면 오른쪽 탐색
	return ret;                                     // 탐색 결과를 리턴
}

// memory leak 방지를 위한 deleteNode 함수
void deleteNode(Node *node) { 
	if (node == 0) return;      // 없는 node면 그냥 return

	deleteNode(node->left);     // 왼쪽부터 지워나감
	deleteNode(node->right);    // 그 다음에는 오른쪽
	delete(node);               // 마지막으로 현재 노드를 제거
}

int main(int argc, char *argv[]) {
	int n, i;
	char val, left, right;

	Node *root = 0;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		scanf(" %c %c %c", &val, &left, &right);
		if (i) {  // root가 존재하는 상황
			Node *node = find(root, val);
			node->left = new Node(left);
			node->right = new Node(right);
		} else {  // root가 없으므로 root로 만들어주는 상황
			root = new Node(val);
			root->left = new Node(left);
			root->right = new Node(right);
		}
	}

	preorder(root);		puts(""); // 전위순회
	inorder(root);		puts(""); // 중위순회
	postorder(root);	puts(""); // 후위순회

	deleteNode(root);  // 모든 노드 제거
	return 0;
}

// 전위 순회 (current -> left -> right)
void preorder(Node *node) {
	if (node->val == '.') return;

	printf("%c", node->val);
	preorder(node->left);
	preorder(node->right);
}

// 중위 순회 (left -> current -> right)
void inorder(Node *node) {
	if (node->val == '.') return;

	inorder(node->left);
	printf("%c", node->val);
	inorder(node->right);
}

// 후위 순회 (left -> right -> current)
void postorder(Node *node) {
	if (node->val == '.') return;

	postorder(node->left);
	postorder(node->right);
	printf("%c", node->val);
}