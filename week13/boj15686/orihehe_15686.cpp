/*
BOJ 15686 - 치킨 배달

시간복잡도 : O(2^M)
공간복잡도 : O(N^2)

M개의 치킨집을 선택하는 모든 경우에 대해 각 집으로의 거리를 bfs로 구해줬습니다.
선택한 치킨집의 위치를 초기 큐에 모두 넣어서 가까운 거리를 구해주는 방식입니다.
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
int rgo[4] = { -1,0,1,0 }, cgo[4] = { 0,1,0,-1 };
int arr[51][51], dist[51][51], sz, ans = 987654321;
bool use[14];
int n, m;
vector<pii> ck;
queue<pii> q;
int bfs() {
	int tot = 0;
	while (!q.empty()) {
		pii cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nr = cur.first + rgo[i], nc = cur.second + cgo[i];
			if (nr < 0 || nc < 0 || nr >= n || nc >= n || dist[nr][nc]!=-1) continue;
			dist[nr][nc] = dist[cur.first][cur.second] + 1;
			q.push({ nr,nc });
			if (arr[nr][nc] == 1) tot += dist[nr][nc];
		}
	}
	return tot;
}
// 치킨집 선택의 모든 경우 봐주기
void dfs(int cur, int cnt) {
	if (cnt == m) {
		memset(dist, -1, sizeof(dist));
		for (int i = 0; i < sz; i++) {
			// 선택한 치킨집 모두 넣기
			if (use[i]) {
				q.push(ck[i]);
				dist[ck[i].first][ck[i].second] = 0;
			}
		}
		ans = min(ans, bfs());
		return;
	}
	if (cur == sz) return;
	use[cur] = true;
	dfs(cur + 1, cnt + 1);
	use[cur] = false;
	dfs(cur + 1, cnt);
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]);
			// 치킨집 좌표를 저장해둡니다.
			if (arr[i][j] == 2) ck.push_back({ i,j });
		}
	sz = ck.size();
	dfs(0, 0);
	printf("%d", ans);

	return 0;
}