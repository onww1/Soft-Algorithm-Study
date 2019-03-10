/*
BOJ 1600 - 말이 되고픈 원숭이

시간복잡도 : O(N*M*K)
공간복잡도 : O(N*M*K)

visited배열을 x,y,k로 설정하고 bfs를 돌리면 됩니다!
bfs과정에서 k횟수가 남아있다면 말처럼 이동을 추가로 해주고 큐에 넣어줍니다.
*/
#include <cstdio>
#include <queue>
using namespace std;

/* 🐣🐥 */
// 일반적인 이동
int rgo[4] = { 1,-1,0,0 };
int cgo[4] = { 0,0,1,-1 };
// 말처럼 이동
int rhgo[8] = { 1,-1,2,-2,1,-1,2,-2 };
int chgo[8] = { 2,-2,1,-1,-2,2,-1,1 };
int b[201][201];
bool visited[201][201][31];
struct node {
	int r, c, cc;
};
queue<node> q;
int main() {
	int k, n, m, s, cnt;
	scanf("%d %d %d", &k, &n, &m);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &b[i][j]);
		}
	}
	q.push({ 0,0,k });
	visited[0][0][k] = true;
	s = 1, cnt = 0;
	while (!q.empty()) {
		if (s == 0) {
			s = q.size();
			cnt++;
		}
		node cur = q.front();
		q.pop();
		// 도착했다면 끝내기
		if (cur.r == m - 1 && cur.c == n - 1) {
			return !printf("%d", cnt);
		}
		if (cur.cc > 0) { // 말처럼 이동 횟수가 남아있다면
			for (int i = 0; i < 8; i++) {
				int nr = cur.r + rhgo[i], nc = cur.c + chgo[i];
				if (nr < 0 || nc < 0 || nr >= m || nc >= n || b[nr][nc]) continue;
				if (visited[nr][nc][cur.cc - 1]) continue;
				visited[nr][nc][cur.cc - 1] = true;
				q.push({ nr,nc,cur.cc - 1 });
			}
		}
		for (int i = 0; i < 4; i++) {
			int nr = cur.r + rgo[i], nc = cur.c + cgo[i];
			if (nr < 0 || nc < 0 || nr >= m || nc >= n || b[nr][nc]) continue;
			if (visited[nr][nc][cur.cc]) continue;
			visited[nr][nc][cur.cc] = true;
			q.push({ nr,nc,cur.cc });
		}
		s--;
	}
	printf("-1");

	return 0;
}