/*
BOJ 5719 - 거의 최단 경로

시간복잡도 : O(T*N^2logN)
공간복잡도 : O(N^2)

다익스트라 과정에서 현재까지 최단경로일 때 그 값이 나오는 모든 부모를 저장해줍니다.
그리고나서 도착지점에서부터 부모로 따라 올라가 간선들을 지워줍니다.
다시 다익스트라를 돌려주면 거의 최단경로가 나오게 됩니다.
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#define pii pair<int,int>
#define INF 500001
using namespace std;

/* 🐣🐥 */
priority_queue<pii, vector<pii>, greater<pii>> pq;
int vec[500][500];
int dist[500], n;
vector<int> p[500];
bool visited[500];
void dijk(int srt) {
	fill(dist, dist + n, INF);
	dist[srt] = 0;
	pq.push({ 0,srt });
	while (!pq.empty()) {
		pii cur = pq.top();
		pq.pop();
		if (cur.first > dist[cur.second]) continue;
		for (int i = 0; i < n; i++) {
			if (vec[cur.second][i] == 0) continue;
			int tmp = vec[cur.second][i] + cur.first;
			if (tmp < dist[i]) {
				p[i].clear(); // 부모 초기화
				p[i].push_back(cur.second); // 부모 넣어주기
				
				dist[i] = tmp;
				pq.push({ tmp,i });
			}
			else if (tmp == dist[i]) // 같은 값이라면 부모 넣어주기
				p[i].push_back(cur.second);
		}
	}
}
// 부모를 타고올라가 간선 지워주기
void rm(int fr) {
	visited[fr] = true;
	for (int v : p[fr]) {
		vec[v][fr] = 0;
		if (!visited[v]) rm(v);
	}
}
int main() {
	int m, s, e, a, b, c;
	while (scanf("%d %d", &n, &m)) {
		if (n == 0 && m == 0) break;
		scanf("%d %d", &s, &e);
		memset(vec, 0, sizeof(vec));
		memset(visited, false, sizeof(visited));
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &c);
			vec[a][b] = c;
		}
		dijk(s);
		rm(e);
		dijk(s);
		if (dist[e] == INF) printf("-1\n");
		else printf("%d\n", dist[e]);
		for (int i = 0; i < n; i++) p[i].clear();
	}

	return 0;
}