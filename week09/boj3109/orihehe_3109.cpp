/*
BOJ 3109 - 빵집

시간복잡도 : O(NM)
공간복잡도 : O(NM)

윗줄부터 시작하여 최대한 위부터 사용하는것이 가장 많은 파이프를 놓을 수 있습니다.
또한 이미 방문했던 곳에서는 라인이 차있거나, 불가능하단 판단이 되어있으므로 재방문 하지 않아도 됩니다.
*/
#include <cstdio>
using namespace std;

/* 🐣🐥 */
int b[10001][501];
int rgo[3] = { -1,0,1 };
int n, m, cnt, j;
bool suc;
void dfs(int r, int c) {
	b[r][c] = 1;
	if (c == m - 1) {
		suc = true;
		return;
	}
	for (int i = 0; i < 3; i++) {
		int nr = r + rgo[i];
		if (nr < 0 || nr >= n || b[nr][c + 1] == 1) continue;
		dfs(nr, c + 1);
		if (suc) return;
	}
}
int main() {
	char x;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf(" %c", &x);
			if (x == 'x') b[i][j] = 1;
		}
	}
	for (int i = 0; i < n; i++) {
		suc = false;
		dfs(i, 0);
	}
	for (int i = 0; i < n; i++) {
		if (b[i][m - 1]) cnt++;
	}
	printf("%d", cnt);

	return 0;
}