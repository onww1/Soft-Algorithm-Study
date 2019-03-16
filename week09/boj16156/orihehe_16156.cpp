/*
BOJ 16156 - 장애물 달리기

시간복잡도 : O(NMlogNM)
공간복잡도 : O(NM)

결승선의 각 지점을 pq에 모두 넣어준 뒤 다익스트라를 돌려줍니다.
그렇면 모든 노드에 어느 결승선에서 가장 가까운지가 기록되게되고,
출발점에 저장된 결승선 정보를 세주어 출력합니다.
*/
#include <cstdio>
#include <algorithm>
#include <queue>
#include <climits>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
struct node {
	int r, c, p, val;
	bool operator <(const node &a) const {
		return val > a.val;
	}
};
int arr[500][500];
int n, m, ans[500];
pii dist[500][500]; // 거리, 어느 결승선에서 왔는지
int rgo[4] = { 0,0,1,-1 }, cgo[4] = { 1,-1,0,0 };
priority_queue<node> pq;
void dijk() {
	for (int i = 0; i < n; i++)
		fill(dist[i], dist[i] + m, pii(INT_MAX, 0));
	for (int i = 0; i < n; i++) {
		dist[i][m - 1] = { arr[i][m-1],i };
		pq.push({ i,m-1,i,arr[i][m - 1] });
	}
	while (!pq.empty()) {
		node cur = pq.top();
		pq.pop();
		if (dist[cur.r][cur.c].first < cur.val) continue;
		for (int i = 0; i < 4; i++) {
			int nr = cur.r + rgo[i], nc = cur.c + cgo[i];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			int tmp = cur.val + arr[nr][nc];
			if (tmp < dist[nr][nc].first) {
				dist[nr][nc] = { tmp,cur.p };
				pq.push({ nr,nc,cur.p,tmp });
			}
		}
	}
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
	dijk();
	for (int i = 0; i < n; i++)
		ans[dist[i][0].second]++;
	for (int i = 0; i < n; i++)printf("%d\n", ans[i]);;

	return 0;
}