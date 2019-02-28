/*
BOJ 1761 - 정점들의 거리

시간복잡도 : O(NlogN)
공간복잡도 : O(NlogN)

sps에 2^i위의 부모, 부모까지의 거리 정보를 저장해둡니다.
LCA를 찾는 과정에서 올라가는 거리를 더한 값을 리턴!
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
vector<pii> vec[40001];
pii sps[40001][18];
int dep[40001]; // 깊이
void dfs(int cur, int cnt) {
	dep[cur] = cnt;
	for (int i = 1; i <= 17; i++) {
		sps[cur][i].first = sps[sps[cur][i - 1].first][i - 1].first;
		// 2^(i-1)까지의 거리, 현재에서 2^(i-1) 위의 노드 ~ 2^i 까지의 거리 합
		sps[cur][i].second = sps[cur][i - 1].second +
			sps[sps[cur][i - 1].first][i - 1].second;
	}
	for (pii v : vec[cur]) {
		if (!dep[v.second]) {
			// 자식노드의 0번째에 부모(= 현재) 정보를 저장
			sps[v.second][0].first = cur;
			sps[v.second][0].second = v.first;
			dfs(v.second, cnt + 1);
		}
	}
}
int lca(int a, int b) {
	int ret = 0;
	if (dep[a] < dep[b]) swap(a, b); // 더 깊은 노드 a
	for (int i = 17; i >= 0; i--) {
		// a를 2^i만큼 올렸을 때 여전히 깊이가 b 이상이라면
		if (dep[sps[a][i].first] >= dep[b]) {
			ret += sps[a][i].second; // 올라간 거리 더해줍니다.
			a = sps[a][i].first;
		}
	}
	if (a == b) {
		return ret;
	}
	for (int i = 17; i >= 0; i--) {
		// 2^i만큼 올렸을 때 노드가 다르다면 올려줘도 됩니다.
		if (sps[a][i].first != sps[b][i].first) {
			// 올라간 거리 더해줍니다.
			ret += sps[a][i].second + sps[b][i].second;
			a = sps[a][i].first;
			b = sps[b][i].first;
		}
	}
	// 공통 부모 한 칸 아래까지 올라가있는 상태
	return ret + sps[a][0].second + sps[b][0].second;
}
int main() {
	int n, a, b, c, m;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		vec[a].push_back({ c,b });
		vec[b].push_back({ c,a });
	}
	dfs(1, 1);
	scanf("%d", &m);
	while (m--) {
		scanf("%d %d", &a, &b);
		printf("%d\n", lca(a, b));
	}

	return 0;
}