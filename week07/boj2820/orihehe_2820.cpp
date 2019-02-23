/*
BOJ 2820 - 자동차 공장

시간복잡도 : O(MlogN)
공간복잡도 : O(2^logN)

A의 모든 부하의 월급을 올려야 합니다. 원래의 상태로는 구간을 주어 월급을 올려주기 힘듭니다.
어떻게하면 부하들의 구간을 알 수 있을까 하다가 일렬로 쭉 쓰다보니 dfs를 돌려 인덱스를 정해주면 될거 같았습니다.
dfs과정에서 탐색 순서대로 인덱스를 다시 정해주고, 각 노드의 자식 수를 세줬습니다.
그렇게되면 현재 노드의 부하는 (현재 노드+1)~(현재 노드 + 자식수) 의 구간에 있게 됩니다.
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

/* 🐣🐥 */
int *tree;
int child[500001];
int arr[500001], cnt;
int ix[500001];
vector<int> vec[500001];
int dfs(int cur, int idx) {
	int ch = 0;
	cnt++;
	ix[cur] = cnt; // ix[cur] 현재 직원의 인덱스 다시 만듦
	for (int v : vec[cur]) {
		ch += dfs(v, cnt + 1);
	}
	return child[idx] = ch + 1; // 자식 수 + 본인
}
void update(int idx, int s, int e, int l, int r, int val) {
	if (r < s || l > e) return;
	if (l <= s && e <= r) { // 구간에 변경 값 저장
		tree[idx] += val;
		return;
	}
	update(idx * 2, s, (e + s) / 2, l, r, val);
	update(idx * 2 + 1, (e + s) / 2 + 1, e, l, r, val);
}
int money(int idx, int s, int e, int k, int sum) {
	if (k > e || k < s) return 0;
	int tmp = sum + tree[idx]; // 구간의 값을 더해서 갑니다.
	if (e==s) {
		return tmp;
	}
	return money(idx * 2, s, (e + s) / 2, k, tmp)
		+ money(idx * 2 + 1, (e + s) / 2 + 1, e, k, tmp);
}
int main() {
	int n, m, h, x, p;
	char cm;
	scanf("%d %d", &n, &m);
	h = ceil(log2(n)) + 1;
	tree = new int[1 << h];
	fill(tree, tree + (1 << h), 0);
	scanf("%d", &x); // 루트 노드
	update(1, 1, n, 1, 1, x);
	for (int i = 2; i <= n; i++) {
		scanf("%d %d", &x, &p);
		vec[p].push_back(i);
		arr[i] = x; //i의 월급
	}
	dfs(1, 1);
	for (int i = 2; i <= n; i++) { // 다시 정한 인덱스에 월급 업데이트
		update(1, 1, n, ix[i],ix[i], arr[i]);
	}
	for (int i = 0; i < m; i++) {
		scanf(" %c", &cm);
		if (cm == 'p') {
			scanf("%d %d", &x, &p);
			x = ix[x];
			if (child[x]-1) { // 부하가 있다면
				update(1, 1, n, x + 1, x + child[x] - 1, p);
			}
		}
		else if (cm == 'u') {
			scanf("%d", &x);
			x = ix[x];
			printf("%d\n", money(1, 1, n, x, 0));
		}
	}

	return 0;
}