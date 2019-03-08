/*
BOJ 2637 - 장난감조립

시간복잡도 : O(N*M)
공간복잡도 : O(N*N)

간선정보를 저장할 때 필요한 부품, 개수를 저장해줍니다.
위상정렬 중 현재 정점 -> 다음 정점을 보는 과정에서 
현재 정점의 부품 * 개수를 다음 정점에 저장해줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
int deg[101];
vector<pii> vec[101];
int cnt[101][101];
queue<int> q;
int main() {
	int n, m, a, b, c;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		vec[b].push_back({ a,c });
		deg[a]++;
	}
	for (int i = 1; i <= n; i++) {
		if (!deg[i]) {
			q.push(i);
			cnt[i][i] = 1;
		}
	}
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (pii v : vec[cur]) {
			// 각 부품별로 현재*개수를 다음 정점에 더해줍니다.
			for (int i = 1; i <= n; i++) {
				cnt[v.first][i] += v.second*cnt[cur][i];
			}
			deg[v.first]--;
			if (deg[v.first] == 0) q.push(v.first);
		}
	}
	for (int i = 1; i <= n; i++) {
		if (cnt[n][i] != 0) printf("%d %d\n", i, cnt[n][i]);
	}

	return 0;
}