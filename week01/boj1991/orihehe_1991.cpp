/*
BOJ 1991 - 트리 순회

이진트리이므로 loc[0][노드]에는 왼쪽 자식, loc[1][노드]에는 오른쪽 자식 번호를 저장했습니다.
만약 자식이 없다면 -1을 저장하여 표시해두었습니다.
*/
#include <iostream>
using namespace std;

int n;
char root, l, r, c;
int loc[2][27];
void pre(int rot) { // 전위순회
	if (rot == -1) return;
	c = rot + 'A';
	cout << c;
	pre(loc[0][rot]);
	pre(loc[1][rot]);
}
void post(int rot) { // 후위순회
	if (rot == -1) return;
	post(loc[0][rot]);
	post(loc[1][rot]);
	c = rot + 'A';
	cout << c;
}
void in(int rot) { // 중위순회
	if (rot == -1) return;
	in(loc[0][rot]);
	c = rot + 'A';
	cout << c;
	in(loc[1][rot]);
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> n;
	while (n--) {
		cin >> root >> l >> r;
		if (l != '.')loc[0][root - 'A'] = l-'A';
		else loc[0][root - 'A'] = -1;
		if (r != '.')loc[1][root - 'A'] = r-'A';
		else loc[1][root - 'A'] = -1;
	}
	pre(0);
	cout << "\n";
	in(0);
	cout << "\n";
	post(0);
	return 0;
}