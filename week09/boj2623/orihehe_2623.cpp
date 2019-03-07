/*
BOJ 2623 - 음악프로그램

시간복잡도 : O(N+M)
공간복잡도 : O(N)

위상정렬 기본 문제입니다.
현재 가수(a) 앞에 나오는 가수 (l) l->a의 간선을 만들어 위상정렬 해줍니다.
*/
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

/* 🐣🐥 */
int deg[1001];
queue<int> q;
vector<int> vec[1001], ans;
int main() {
	int n, m, c, a, l;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &c, &l);
		for (int i = 1; i < c; i++) {
			scanf("%d", &a);
			vec[l].push_back(a);
			deg[a]++;
			l = a;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (!deg[i]) {
			q.push(i);
		}
	}
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		ans.push_back(cur);
		for (int v : vec[cur]) {
			deg[v]--;
			if (deg[v] == 0) q.push(v);
		}
	}
	if (ans.size() == n) {
		for (int v : ans) printf("%d\n", v);
	}
	else printf("0");

	return 0;
}