/*
BOJ 2573 - 빙산

시간복잡도 : O(NM)
공간복잡도 : O(NM)

각 칸의 높이를 큐에 모두 넣고 하나씩 보며 사방의 0의 개수를 세줍니다.
만약 이 칸이 다음 턴에 완전히 녹는다면 좌표를 다른 큐에 넣어줍니다.
한 턴이 모두 끝나면 다른 큐에 넣어둔 좌표들의 값을 모두 0으로 바꿔준 뒤,
dfs로 덩어리의 개수를 세줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
int b[301][301], ans = 15;
int n, m, s, cnt = 0;
bool visited[1001][1001];
int rgo[4] = { 1,-1,0,0 }, cgo[4] = { 0,0,1,-1 };
queue<pii> q, tt;
// 이어진 빙하 탐색
void dfs(int r, int c) {
	visited[r][c] = true;
	for (int i = 0; i < 4; i++) {
		int nr = r + rgo[i], nc = c + cgo[i];
		if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
		if (b[nr][nc] != 0 && !visited[nr][nc]) dfs(nr, nc);
	}
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &b[i][j]);
			if (b[i][j] != 0) q.push({ i,j });
		}
	}
	int rr = 0;
	s = q.size();
	while (!q.empty()) {
		if (s == 0) {
			s = q.size();
			cnt++;
			// 완전히 녹은 좌표 0으로
			while (!tt.empty()) {
				b[tt.front().first][tt.front().second] = 0;
				tt.pop();
			}
			rr = 0;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					// 덩어리를 세줍니다.
					if (b[i][j] != 0 && !visited[i][j]) {
						dfs(i, j);
						rr++;
					}
				}
			}
			// 두덩이 이상이라면 출력
			if (rr >= 2) return !printf("%d", cnt);
			memset(visited, false, sizeof(visited));
		}
		pii cur = q.front();
		q.pop();
		int x = 0;
		for (int i = 0; i < 4; i++) {
			int nr = cur.first + rgo[i], nc = cur.second + cgo[i];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			// 사방의 0 개수 세주기
			if (b[nr][nc] == 0) x++;
		}
		if (b[cur.first][cur.second] - x <= 0) tt.push(cur);
		else {
			b[cur.first][cur.second] -= x;
			q.push(cur);
		}
		s--;
	}
	printf("0");

	return 0;
}