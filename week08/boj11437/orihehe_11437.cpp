/*
BOJ 11437 - LCA

시간복잡도 : O(NlogN)
공간복잡도 : O(NlogN)

LCA 기초 문제 입니다.
dfs과정에서 dep배열에 현재 노드의 깊이와 
sps배열에 현재 노드의 2^i 위의 부모 노드를 저장해줍니다.

lca에서는 가장 가까운 공통 조상을 찾는데,
먼저 깊이가 더 깊은 노드를 다른 노드의 깊이와 같게 올려준 뒤,
2^17부터 위로 올라갔을 때 조상이 다를 시 올라가주며 노드들을 LCA한칸 아래까지 옮겨줍니다.

ex) 만약 조상이 7칸 위에 있다면, 4칸, 2칸 올라가 주게 됩니다.
*/
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

/* 🐣🐥 */
vector<int> vec[50001];
int sps[50001][18];
int dep[50001]; // 깊이
void ddd(int cur, int cnt) {
	dep[cur] = cnt;
	for (int i = 1; i <= 17; i++) {
		// 2^i위 부모정보는
		// 2^(i-1)위 부모의 2^(i-1)위 부모와 같다.
		sps[cur][i] = sps[sps[cur][i - 1]][i - 1];
	}
	for (int v : vec[cur]) {
		if (!dep[v]) {
			// 자식노드의 0번째에 부모(= cur) 정보를 저장
			sps[v][0] = cur;
			ddd(v, cnt + 1);
		}
	}
}
int lca(int a, int b) { 
	if (dep[a] > dep[b]) swap(a, b); // 깊은 노드를 b로

	for (int i = 17; i >= 0; i--) {
		// b를 2^i만큼 올렸을 때 여전히 깊이가 a의 깊이 이상이라면
		if (dep[sps[b][i]] >= dep[a])
			b = sps[b][i];
	}
	if (a == b) return a; // 올렸을 때 같은 노드라면 리턴

	for (int i = 17; i >= 0; i--) {
		// 2^i만큼 올렸을 때 노드가 다르다면 올려줘도 됩니다.
		if (sps[a][i] != sps[b][i]) {
			a = sps[a][i];
			b = sps[b][i];
		}
	}
	// 공통 부모 한 칸 아래까지 올라가있는 상태
	return sps[a][0]; // a의 한칸 위 부모 리턴
}
int main() {
	int n, m, a, b, x = 1;
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b);
		vec[a].push_back(b);
		vec[b].push_back(a);
	}
	ddd(1, 1);
	scanf("%d", &m);
	while (m--) {
		x = 1;
		scanf("%d %d", &a, &b);
		printf("%d\n", lca(a, b));
	}

	return 0;
}