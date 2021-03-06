// 이진 트리 안의 값을 찾아서 그 값을 가지고 있는 노드의
// 왼쪽과 오른쪽에 값을 집어 넣어 준다.
// 그것을 전위, 중위, 후위 순회하면서 값을 출력해준다.

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;

class Node {
public:
	char c;
	Node *l, *r;
	Node(char _c) : c(_c), l(NULL), r(NULL) {}
};

int N;
bool f;

void pre(Node *c) {
	if (c == NULL) return;
	cout << c->c;
	pre(c->l);
	pre(c->r);
}

void ino(Node *c) {
	if (c == NULL) return;
	ino(c->l);
	cout << c->c;
	ino(c->r);
}

void post(Node *c) {
	if (c == NULL) return;
	post(c->l);
	post(c->r);
	cout << c->c;
}

Node *insert(Node *c, char a, char b, char d) {
	if (c == NULL) return NULL;
	if (c->c == a) {
		f = true;
		if (b != '.') c->l = new Node(b);
		if (d != '.') c->r = new Node(d);
		return c;
	}
	// c = insert(c->l, a, b, d); 이렇게 해서 자꾸 틀린다!! 주의하자!!
	c->l = insert(c->l, a, b, d);
	if (f) return c; // 시간 절약을 위해 사용
	c->r = insert(c->r, a, b, d);
	return c;
}

int main() {
	fastio();
	char a, b, d;
	cin >> N;
	Node *root = new Node('A');
	for (int i = 0; i < N; i++) {
		cin >> a >> b >> d;
		f = false;// a값을 찾았는지 체크하는 flag이다.
		root = insert(root, a, b, d);
	}
	pre(root);
	cout << '\n';
	ino(root);
	cout << '\n';
	post(root);
	cout << '\n';
	return 0;
}