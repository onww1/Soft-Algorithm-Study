/*
BOJ 3176 - 도로 네트워크

시간복잡도 : O(NlogN)
공간복잡도 : O(NlogN)

sps에 2^i위의 부모, 부모까지의 최소도로, 최대도로 정보를 저장해둡니다.
LCA를 찾는 과정에서 최소, 최대 도로 값을 구해줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
vector<pii> vec[100001]; // 트리
struct road {
	int p, mn, mx; // 부모, 최소, 최대
	road() { // 생성자
		p = 0, mn = 1000001, mx = 0;
	}
};
road sps[100001][18];
int dep[100001]; // 깊이
void dfs(int cur, int cnt) {
	dep[cur] = cnt;
	for (int i = 1; i <= 17; i++) {
		sps[cur][i].p = sps[sps[cur][i - 1].p][i - 1].p;
		// 2^(i-1)까지의 최소, 2^i 까지의 최소중 최소
		sps[cur][i].mn = min(sps[cur][i - 1].mn,
			sps[sps[cur][i - 1].p][i - 1].mn);
		// 2^(i-1)까지의 최대, 2^i 까지의 최대중 최대
		sps[cur][i].mx = max(sps[cur][i - 1].mx,
			sps[sps[cur][i - 1].p][i - 1].mx);
	}
	for (pii v : vec[cur]) {
		if (!dep[v.second]) {
			// 자식노드의 0번째에 부모(= 현재) 정보를 저장
			sps[v.second][0].p = cur;
			sps[v.second][0].mn = v.first;
			sps[v.second][0].mx = v.first;
			dfs(v.second, cnt + 1);
		}
	}
}
pii lca(int a, int b) {
	pii ret = { 1000001,0 };
	if (dep[a] < dep[b]) swap(a, b); // 더 깊은 것 a에
	for (int i = 17; i >= 0; i--) {
		// a를 2^i만큼 올렸을 때 여전히 깊이가 b 이상이라면
		if (dep[sps[a][i].p] >= dep[b]) {
			ret.first = min(ret.first, sps[a][i].mn);
			ret.second = max(ret.second, sps[a][i].mx);
			a = sps[a][i].p;
		}
	}
	if (a == b) {
		return ret;
	}
	for (int i = 17; i >= 0; i--) {
		// 2^i만큼 올렸을 때 노드가 다르다면 올려줘도 됩니다.
		if (sps[a][i].p != sps[b][i].p) {
			ret.first = min({ ret.first,sps[a][i].mn,sps[b][i].mn });
			ret.second = max({ ret.second,sps[a][i].mx,sps[b][i].mx });
			a = sps[a][i].p;
			b = sps[b][i].p;
		}
	}
	// 공통 부모 한 칸 아래까지 올라가있는 상태
	ret.first = min({ ret.first,sps[a][0].mn,sps[b][0].mn });
	ret.second = max({ ret.second,sps[a][0].mx,sps[b][0].mx });
	return ret;
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
		pii ans = lca(a, b);
		printf("%d %d\n", ans.first, ans.second);
	}

	return 0;
}