/*
 * 인접 배열에 왼쪽 자식은 1, 오른쪽 자식은 2로 저장
 * 인접 배열을 순회하며 결과를 출력하는 전형적인 트리 순회 알고리즘
 */
#include <cstdio>
using namespace std;

int tree[26][26] = { 0, };

// 왼쪽, 오른쪽 자식 노드 설정
void setChild(int* left, int* right, int idx, int n) {

    // 1이나 2인 값이 있으면 찾아서 자식으로 등록한다.
	for (int i = 0; i < n; ++i) {
		*left = (tree[idx][i] == 1) ? i : *left;
		*right = (tree[idx][i] == 2) ? i : *right;
	}
}

// 전위순회
void preOrder(int idx, int n) {

	if (idx == -1) {
		return;
	}

	int left, right;
	left = right = -1;

	setChild(&left, &right, idx, n);

	printf("%c", idx + 'A');
	preOrder(left, n);
	preOrder(right, n);
}

// 중위순회
void inOrder(int idx, int n) {

	if (idx == -1) {
		return;

	}

	int left, right;
	left = right = -1;

	setChild(&left, &right, idx, n);

	inOrder(left, n);
	printf("%c", idx + 'A');
	inOrder(right, n);
}

// 후위순회
void postOrder(int idx, int n) {

	if (idx == -1) {
		return;
	}

	int left, right;
	left = right = -1;

	setChild(&left, &right, idx, n);

	postOrder(left, n);
	postOrder(right, n);
	printf("%c", idx + 'A');
}

int main() {

	int n;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i) {
		char node, left, right;
		scanf(" %c %c %c", &node, &left, &right);

        // 왼쪽 자식 노드는 1로 저장
		if (left != '.') {
			tree[node - 'A'][left - 'A'] = 1;
		}

        // 오른쪽 자식 노드는 2로 저장
		if (right != '.') {
			tree[node - 'A'][right - 'A'] = 2;
		}
	}

	preOrder(0, n);		printf("\n");
	inOrder(0, n);		printf("\n");
	postOrder(0, n);	printf("\n");

	return 0;
}