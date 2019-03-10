/*
BOJ 2252 - 줄 세우기

시간복잡도 : O(N+M)
공간복잡도 : O(N)

위상정렬 기본 문제 입니다.
A가 B의 앞에 서야한다 : A->B 간선을 만들어줍니다.
*/
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

/* 🐣🐥 */
int deg[32001];
queue<int> q;
vector<int> vec[32001];
int main() {
	int n, m, a, b;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		vec[a].push_back(b); // a->b
		deg[b]++;
	}
	for (int i = 1; i <= n; i++) {
		if (!deg[i]) {
			q.push(i);
		}
	}
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		printf("%d ", cur);
		for (int v : vec[cur]) {
			deg[v]--;
			if (deg[v] == 0) q.push(v);
		}
	}

	return 0;
}