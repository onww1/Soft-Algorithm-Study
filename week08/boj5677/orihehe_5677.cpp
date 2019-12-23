/*
BOJ 5677 - Joining Couples

시간복잡도 : O(T*(N+Q)logN)
공간복잡도 : O(NlogN)

입력의 그래프를 사이클과 그 사이클을 부모로 하는 가지로 생각합니다.

각 커플이 이용할 최소 비행기 수는
만약 a,b가 같은 가지에 속한다면 공통 부모에서 만날 때이고,
같은 가지는 아니지만 같은 그룹에 속한다면 각 가지에서 부모까지의 거리 + 사이클에서 가까운 거리 입니다.

따라서 각 가지와 그룹의 유니온을 따로 판별해준 뒤
같은 가지에 속한다면 lca로 판별,
같은 그룹이라면 사이클에 번호를 부여해준 뒤
각각의 가지에서의 깊이 + a(루트) -> b(루트) 와 b(루트) -> a(루트) 중 작은 값이 답이 됩니다.
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

/* 🐣🐥 */
// p는 가지별로, pp는 그룹별로
int to[100001], dep[100001], p[100001], pp[100001], ind[100001], cy[100001];
int sps[100001][18];
queue<int> q;
vector<int> vec[100001];
int find(int a, int op[]) {
	if (a == op[a]) return a;
	return op[a] = find(op[a], op);
}
void merge(int a, int b, int op[]) {
	a = find(a, op);
	b = find(b, op);
	op[a] = b;
}
void dfs(int cur, int cnt) {
	dep[cur] = cnt;
	for (int i = 1; i < 18; i++) {
		sps[cur][i] = sps[sps[cur][i - 1]][i - 1];
	}
	for (int v : vec[cur]) {
		if (!dep[v]) {
			sps[v][0] = cur;
			dfs(v, cnt + 1);
		}
	}
}
int lca(int a, int b) { // 같은 가지일 때
	int ad, bd;
	if (dep[a] > dep[b]) 
		swap(a, b);
	ad = dep[a], bd = dep[b];
	for (int i = 17; i >= 0; i--) {
		if (dep[sps[b][i]] >= dep[a]) {
			b = sps[b][i];
		}
	}
	if (a == b) return bd - dep[b];
	for (int i = 17; i >= 0; i--) {
		if (sps[b][i] != sps[a][i]) {
			a = sps[a][i];
			b = sps[b][i];
		}
	}
	return ad - dep[a] + bd - dep[b] + 2;
}
void mdfs(int cur, int cnt) {
	ind[cur] = 0;
	cy[cur] = cnt;
	merge(cur, to[cur], pp);
	if (ind[to[cur]]) mdfs(to[cur], cnt+1);
}
int main() {
	//freopen("input.txt", "r", stdin);
	int n, qq, a, b;
	while (~scanf("%d", &n)) {
		memset(ind, 0, sizeof(ind));
		memset(sps, 0, sizeof(sps));
		for (int i = 1; i <= n; i++) {
			scanf("%d", &to[i]);
			p[i] = pp[i] = i;
			cy[i] = dep[i] = 0;
			ind[to[i]]++;
		}
		for (int i = 1; i <= n; i++) {
			if (!ind[i]) q.push(i);
		}
		// 위상정렬을 통해 가지 부분 간선 뒤집기
		while (!q.empty()) {
			int cur = q.front();
			q.pop();
			vec[to[cur]].push_back(cur);
			ind[to[cur]]--;
			merge(cur, to[cur], p);
			merge(cur, to[cur], pp);
			if (!ind[to[cur]]) q.push(to[cur]);
		}
		for (int i = 1; i <= n; i++) {
			if (ind[i]) dfs(i, 1); // 같은 가지 판별
		}
		for (int i = 1; i <= n; i++) {
			if (ind[i]) mdfs(i,0); // 같은 그룹 만들기
			vec[i].clear();
		}

		scanf("%d", &qq);
		while (qq--) {
			scanf("%d %d", &a, &b);
			if (find(a, pp) != find(b, pp)) {
				printf("-1\n");
				continue;
			}
			if (find(a, p) == find(b, p)) {
				printf("%d\n", lca(a, b));
			}
			else {
				int ans = dep[a] + dep[b] - 2;
				a = find(a, p);
				b = find(b, p);
				if (cy[a] > cy[b]) 
					swap(a, b);
				printf("%d\n", min(cy[b] - cy[a], cy[a] + cy[find(b, pp)] - cy[b] + 1) + ans);
			}
		}
	}

	return 0;
}