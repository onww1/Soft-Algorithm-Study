/*
BOJ 1753 - 최단경로

시간복잡도 : O(VlogE)
공간복잡도 : O(V)

다익스트라 기본 문제입니다.
시작정점을 pq에 넣고 시작, 현재 정점까지의 거리 + 현재-다음 거리가 
다음 정점까지의 이미 저장되어있는 최단거리보다 작다면 갱신해 주는 방식 입니다.
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#define pii pair<int,int>
#define INF 2000000000
using namespace std;

/* 🐣🐥 */
vector<pii> vec[20001];
int dist[20001];
priority_queue<pii, vector<pii>, greater<pii>> pq;
void dijk(int srt) {
	// 시작 정점
	pq.push({ 0,srt });
	dist[srt] = 0;
	while (!pq.empty()) {
		pii cur = pq.top();
		pq.pop();
		// 현재까지의 거리가 이미 저장된 거리보다 크다면 보지 않는다.
		if (cur.first > dist[cur.second]) continue;
		for (pii nx : vec[cur.second]) {
			// 현재까지 거리 + 다음정점 간선
			int tmp = nx.first + cur.first;
			if (tmp < dist[nx.second]) {
				dist[nx.second] = tmp;
				pq.push({ tmp,nx.second });
			}
		}
	}
}
int main() {
	int v, e, st, a, b, c;
	scanf("%d %d %d", &v, &e, &st);
	// 각 정점까지의 거리를 INF로 초기화
	fill(dist, dist + v + 1, INF);
	for (int i = 0; i < e; i++) {
		scanf("%d %d %d", &a, &b, &c);
		vec[a].push_back({ c,b });
	}
	dijk(st);
	for (int i = 1; i <= v; i++) {
		if (dist[i] == INF)printf("INF\n");
		else printf("%d\n", dist[i]);
	}

	return 0;
}