/*
BOJ 2636 - 치즈

시간복잡도 : O(NM)
공간복잡도 : O(NM)

판의 가장자리는 치즈가 놓이지 않으니 0,0부터 먼저 dfs로 이어진 0을 탐색합니다.
탐색중 현재 위치의 사방을 보아 치즈가 있을 시 큐에 넣어줍니다.

큐에 들어있는 위치가 녹을 치즈의 위치가 되고, 그 치즈가 녹은 뒤 주위도 녹게 되니
큐에서 하나씩 봐주며 녹을 치즈를 다시 넣어줍니다.
그리고 치즈안에 공기를 만나면 다시 녹을 부위가 생기니 큐를 봐주는 과정에서 dfs를 해줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <queue>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
int b[101][101];
int rgo[4] = { 1,0,-1,0 }, cgo[4] = { 0,-1,0,1 };
// 공기는 visited에서, 치즈는 cz에서 방문을 기록합니다.
bool visited[101][101], cz[101][101];
int n, m;
queue<pii> q; 
// 이어진 공기를 탐색
void dfs(int r, int c) {
	visited[r][c] = true;
	for (int i = 0; i < 4; i++) {
		int nr = r + rgo[i], nc = c + cgo[i];
		if (nr < 0 || nc < 0 || nr >= n || nc >= m || visited[nr][nc]) continue;
		if (b[nr][nc] == 0) dfs(nr, nc);
		else if (b[nr][nc] == 1 && !cz[nr][nc]) {
			q.push({ nr,nc });
			cz[nr][nc] = true;
		}
	}
}
int main() {
	int s, last, cnt = 1;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &b[i][j]);
		}
	}
	dfs(0, 0);
	s = q.size();
	last = s;
	while (!q.empty()) {
		if (s == 0) {
			s = q.size();
			last = s;
			cnt++;
		}
		pii cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nr = cur.first + rgo[i], nc = cur.second + cgo[i];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			// 주위가 치즈인데 cz에 방문기록 없다면
			if (b[nr][nc] == 1 && !cz[nr][nc]) {
				q.push({ nr,nc });
				cz[nr][nc] = true;
			}
		}
		dfs(cur.first, cur.second);
		s--;
	}
	printf("%d\n%d", cnt, last);

	return 0;
}