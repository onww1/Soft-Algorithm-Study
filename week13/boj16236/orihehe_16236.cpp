/*
BOJ 16236 - 아기 상어

시간복잡도 : O(N^2*NlogN)
공간복잡도 : O(N^2)

먹을 수 있는 물고기가 남아있을 때 bfs를 계속 돌립니다.
같은 거리에 있는 먹을 수 있는 물고기의 좌표를 모두 넣고 정렬 후 맨 앞 원소를 먹습니다.
먹을 수 있는 물고기가 남은지를 알기 위해 크기별로 물고기 수를 세고, 상어가 클 때마다 그 수를 더해줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
// 뚜루루뚜루
int n, arr[21][21], babyshark = 2, ecnt, ans;
int rgo[4] = { -1,0,0,1 }, cgo[4] = { 0,-1,1,0 };
int dist[21][21], cnt[7], rm;
int sr, sc;
void bfs() {
	queue<pii> q;
	vector<pii> v;
	memset(dist, -1, sizeof(dist));
	q.push({ sr,sc });
	dist[sr][sc] = 0;
	int ss = 1;
	bool ed = false;
	while (!q.empty()) {
		if (ss == 0) {
			if (ed) break; // 먹을 물고기 있을 때, 같은 거리 끝나면 break
			ss = q.size();
		}
		pii cur = q.front();
		q.pop();
		// 먹을 수 있는 물고기 찾음
		if (arr[cur.first][cur.second]>0 && arr[cur.first][cur.second] < babyshark) {
			v.push_back(cur);
			ed = true;
		}
		for (int i = 0; i < 4; i++) {
			int nr = cur.first + rgo[i], nc = cur.second + cgo[i];
			if (nr < 0 || nc < 0 || nr >= n || nc >= n || arr[nr][nc]>babyshark || dist[nr][nc]!=-1) continue;
			dist[nr][nc] = dist[cur.first][cur.second] + 1;
			q.push({ nr,nc });
		}
		ss--;
	}
	if (ed) {
		sort(v.begin(), v.end());
		sr = v[0].first, sc = v[0].second;
		arr[sr][sc] = 0;
		ecnt++;
		ans += dist[sr][sc];
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]);
			if (arr[i][j] == 9) {
				sr = i, sc = j;
				arr[i][j] = 0;
			}
			else if (arr[i][j] == 1) rm++;
			else if (arr[i][j] > 0) cnt[arr[i][j]]++;
		}
	}
	while (rm > 0) {
		rm--;
		bfs();
		if (ecnt == babyshark && babyshark <= 6) {
			ecnt = 0;
			rm += cnt[babyshark];
			babyshark++;
		}
	}

	printf("%d", ans);

	return 0;
}