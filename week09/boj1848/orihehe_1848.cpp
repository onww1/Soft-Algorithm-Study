/*
BOJ 1848 - 동굴 탐험

시간복잡도 : 1. O(NlogN*MlogN)  2. O(MlogN)

두 가지 풀이가 있습니다.
일단 이 문제는 1번방과 인접한 정점들 중 시작점, 끝점이 있는 최단경로를 구하는 문제입니다.

1. 분할정복 + 다익스트라
분할정복을 통해 시작점, 끝점의 그룹을 나누어 그 그룹들에 대해 다익스트라를 돌려줍니다.
방향이 있는 그래프이므로 시작점 끝점을 반대로 하는 경우또한 봐줍니다.
시작점 그룹을 pq에 1->시작점 가중치와 함께 넣고, 나온 최단거리를 끝점 그룹의 것을 봐주면 됩니다.

2. 다익스트라
1번방과 인접한 정점들로 다익스트라를 한번 돌려줍니다. 각각의 1과 인접한 정점들에 색을 부여해줍니다.
그러면 최단거리 정보가 나오는데, 각 정점의 최단거리가 어느 정점에서 왔는지에 따라 색을 칠해줍니다.
이제 간선들을 뒤집어주고 다익스트라를 한번 더 돌려줍니다.
간선을 뒤집어주면 다익 한번으로 돌아오는 경로를 봐줄 수 있습니다.
두 번째 다익 과정에서 같은 색을 만날 때는 뿌리 정점이 같다는 의미이므로 봐주지 않고,
다른 색을 만났을 때 ans를 갱신해줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#define pii pair<int,int>
#define INF 2000000000
using namespace std;

/* 🐣🐥 */
priority_queue<pii, vector<pii>, greater<pii>> pq;
vector<pii> vec[5001], f[14], s[14]; // f, s에 재귀 깊이별로 그룹을 넣어줍니다.
int dist[5001], to1[5001];
int n, m, a, b, c, d, ans = INF;
void dq(int cnt, int l, int r) {
	if (l == r) return;
	int mid = (l + r) / 2;
	for (int i = l; i <= mid; i++) {
		f[cnt].push_back(vec[1][i]); // 시작 그룹
	}
	for (int i = mid + 1; i <= r; i++) {
		s[cnt].push_back(vec[1][i]); // 끝 그룹
	}
	dq(cnt + 1, l, mid);
	dq(cnt + 1, mid + 1, r);
}
void dijk() {
	while (!pq.empty()) {
		pii cur = pq.top();
		pq.pop();
		if (dist[cur.second] < cur.first) continue;
		for (pii nx : vec[cur.second]) {
			int tmp = nx.first + cur.first;
			if (tmp < dist[nx.second]) {
				pq.push({ tmp,nx.second });
				dist[nx.second] = tmp;
			}
		}
	}
}
int main() {
	int cnt = 1;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		vec[a].push_back({ c,b });
		vec[b].push_back({ d,a });
		// 1로 들어가는 간선을 저장해줍니다.
		if (a == 1) to1[b] = d;
		else if (b == 1) to1[a] = c;
	}
	// 분할정복으로 1과 인접한 정점들 그룹 나눠주기
	dq(0, 0, vec[1].size() - 1);
	// 깊이별로 시작점, 끝점 다익
	for (int i = 0; i < 14; i++) {
		fill(dist, dist + n + 1, INF);
		dist[1] = 0;
		for (pii nx : f[i]) {
			dist[nx.second] = nx.first;
			pq.push(nx);
		}
		dijk();
		for (pii nx : s[i]) {
			if (to1[nx.second] != 0)
				ans = min(ans, dist[nx.second] + to1[nx.second]);
		}
		fill(dist, dist + n + 1, INF);
		dist[1] = 0;
		for (pii nx : s[i]) {
			dist[nx.second] = nx.first;
			pq.push(nx);
		}
		dijk();
		for (pii nx : f[i]) {
			if (to1[nx.second] != 0)
				ans = min(ans, dist[nx.second] + to1[nx.second]);
		}
	}
	printf("%d", ans);

	return 0;
}

//struct node {
//	int val, v, col;
//	bool operator<(const node &a) const {
//		return val > a.val;
//	}
//};
//priority_queue<node> pq;
//vector<pii> vec[5001], uvec[5001];
//int dist[5001], udist[5001], color[5001], ori[5001];
//int n, m, a, b, c, d, ans = INF;
//void dijk() {
//	while (!pq.empty()) {
//		node cur = pq.top();
//		pq.pop();
//		if (dist[cur.v] < cur.val) continue;
//		for (pii nx : vec[cur.v]) {
//			int tmp = nx.first + cur.val;
//			if (tmp < dist[nx.second]) {
//				color[nx.second] = cur.col;
//				pq.push({ tmp,nx.second, cur.col });
//				dist[nx.second] = tmp;
//			}
//		}
//	}
//}
//void dijk2() {
//	while (!pq.empty()) {
//		node cur = pq.top();
//		pq.pop();
//		if (udist[cur.v] < cur.val) continue;
//		for (pii nx : uvec[cur.v]) {
//			if (nx.second != 1 && color[nx.second] != cur.col) {
//				ans = min(ans, nx.first + dist[nx.second] + cur.val);
//			}
//			int tmp = nx.first + cur.val;
//			if (tmp < udist[nx.second]) {
//				pq.push({ tmp,nx.second, cur.col });
//				udist[nx.second] = tmp;
//			}
//		}
//	}
//}
//int main() {
//	int cnt = 1;
//	scanf("%d %d", &n, &m);
//	for (int i = 0; i < m; i++) {
//		scanf("%d %d %d %d", &a, &b, &c, &d);
//		vec[a].push_back({ c,b });
//		vec[b].push_back({ d,a });
//
//		uvec[b].push_back({ c,a });
//		uvec[a].push_back({ d,b });
//	}
//	fill(dist, dist + n + 1, INF);
//	dist[1] = 0;
//	for (pii nx : vec[1]) {
//		dist[nx.second] = nx.first;
//		color[nx.second] = cnt;
//		ori[nx.second] = cnt;
//		pq.push({ nx.first, nx.second, cnt++ });
//	}
//	dijk();
//	fill(udist, udist + n + 1, INF);
//	udist[1] = 0;
//	for (pii nx : uvec[1]) {
//		if (ori[nx.second] != color[nx.second])
//			ans = min(ans, nx.first + dist[nx.second]);
//		udist[nx.second] = nx.first;
//		pq.push({ nx.first, nx.second, color[nx.second] });
//	}
//	dijk2();
//	for (pii nx : vec[1]) {
//		if (ori[nx.second] != color[nx.second])
//			ans = min(ans, nx.first + udist[nx.second]);
//	}
//
//	printf("%d", ans);
//
//	return 0;
//}