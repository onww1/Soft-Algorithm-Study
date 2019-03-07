/*
BOJ 9470 - Strahler 순서

시간복잡도 : O(T*(VlogV+E))
공간복잡도 : O(V)

위상정렬 과정에서 다음 정점의 st벡터에 현재의 Strahler순서를 넣어줍니다.
현재 정점을 볼 때 st에 저장된 순서를 토대로 현재 정점의 순서를 정해줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

/* 🐣🐥 */
int deg[1001], ler[1001]; //ler엔 i의 Strahler순서가 저장됩니다.
queue<int> q;
int main() {
	int t, k, m, p, a, b;
	scanf("%d", &t);
	while (t--) {
		vector<int> vec[1001], st[1001];
		memset(deg, 0, sizeof(deg));
		memset(ler, 0, sizeof(ler));

		scanf("%d %d %d", &k, &m, &p);
		for (int i = 0; i < p; i++) {
			scanf("%d %d", &a, &b);
			vec[a].push_back(b);
			deg[b]++;
		}
		for (int i = 1; i <= m; i++) {
			if (!deg[i]) {
				q.push(i);
				ler[i] = 1;
			}
		}
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			// 현재 정점으로 들어온 간선들의 Strahler 순서 정렬
			sort(st[cur].begin(), st[cur].end());
			int s = st[cur].size() - 1;
			if (ler[cur] == 0) { // cur의 Strahler 순서를 구해줍니다.
				// 끝의 값이 2개 이상이라면 i+1
				if (s > 0 && st[cur][s] == st[cur][s - 1])
					ler[cur] = st[cur][s] + 1;
				else ler[cur] = st[cur][s]; // i
			}
			for (int v : vec[cur]) {
				if (deg[v] > 0) {
					// 간선 방향에 있는 정점에 나의 Strahler순서 넣어줌.
					st[v].push_back(ler[cur]);
				}
				deg[v]--;
				if (deg[v] == 0) q.push(v);
			}
		}
		printf("%d %d\n", k, ler[m]);
	}

	return 0;
}