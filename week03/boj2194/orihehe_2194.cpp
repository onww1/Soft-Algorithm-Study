/*
BOJ 2194 - ���� �̵���Ű��

bfs ������� ���� ������ ���� �� ��ǥ�� ť�� �־� Ž��������ϴ�.
�����¿� �� ���⿡ ���� ������ �̵���Ű��, ��ֹ��� ���ٸ� �̵������ϹǷ� ť�� ��ǥ�� �־��ݴϴ�.
���� �̹� �湮�� ���� �ٽ� �־ �ּ� �̵� Ƚ���� �� �� ������ �־����� �ʽ��ϴ�.

������ �̵����� �� ��ֹ��� �ִ��� ���δ� igo�Լ����� üũ�մϴ�.
������ �� ĭ�� �̵��ϹǷ� ���� ��ü�� üũ�ϴ� �ͺ��ٴ�
�׵θ��� ���� ���� ȿ������ �� ���� �׵θ��� üũ������ϴ�.
*/
#include <cstdio>
#include <queue>
#define P pair<int,int>
using namespace std;

int bo[501][501]; // ��ֹ� -1, �湮 1
int rgo[4] = { -1,0,1,0 }; // �� �� �� ��
int cgo[4] = { 0,1,0,-1 };
int n, m, a, b, k, r, c, cnt = 0, s = 1;

bool igo(int rr, int cc) {  // ������ �׵θ� �˻�
	// ���簢�� ���� �� �˻�
	for (int i = rr; i < rr + a; i++) {
		if (bo[i][cc] == -1) return false;
		if (bo[i][cc + b-1] == -1) return false;
	}
	// ���簢�� ���� �� �˻�
	for (int i = cc; i < cc + b; i++) {
		if (bo[rr][i] == -1) return false;
		if (bo[rr+a-1][i] == -1) return false;
	}
	return true;
}
int main() {
	queue<P> q;
	scanf("%d %d %d %d %d", &n, &m, &a, &b, &k);
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &r, &c);
		bo[r][c] = -1;
	}
	scanf("%d %d", &r, &c);
	q.push({ r,c });
	bo[r][c] = 1;
	scanf("%d %d", &r, &c);

	bool suc = false;
	while (!q.empty()) {
		if (s == 0) {
			cnt++;
			s = q.size();
		}
		int cr = q.front().first, cc = q.front().second;
		q.pop();
		if (cr==r && cc==c) {  // ����
			suc = true; break;
		}
		for (int i = 0; i < 4; i++) {
			int nr = cr + rgo[i], nc = cc + cgo[i];
			if (nr <= 0 || nc <= 0 || nr + a - 1 > n || nc + b - 1 > m) 
				continue;
			// �湮���� �ʾҰ�, ��ֹ��� ���ٸ�
			if (bo[nr][nc]!=1 && igo(nr, nc)) {
				q.push({ nr, nc });
				bo[nr][nc] = 1; // �湮 ������ ǥ��
			}
		}
		s--;
	}
	if (suc) printf("%d", cnt);
	else printf("-1");

	return 0;
}