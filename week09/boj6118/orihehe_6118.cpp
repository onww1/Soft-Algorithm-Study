/*
BOJ 6118 - 숨바꼭질

시간복잡도 : O(N+M)
공간복잡도 : O(M)

bfs를 통해 cc배열에 첫 헛간에서부터의 거리를 저장해줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

/* 🐣🐥 */
vector<int> vec[20001];
queue<int> q;
int cc[20001];
int main() {
	int n, m, a, b, s, cnt, idx = 0, ans = 0, mm = 0;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		vec[a].push_back(b);
		vec[b].push_back(a);
	}
	q.push(1);
	cnt = 1, s = 1;
	cc[1] = -1;
	while (!q.empty()) {
		if (s == 0) {
			s = q.size();
			cnt++;
		}
		int cur = q.front();
		q.pop();
		for (int v : vec[cur]) {
			if (!cc[v]) {
				// v까지의 거리
				cc[v] = cnt;
				// 최대 거리 저장
				mm = max(mm, cnt);
				q.push(v);
			}
		}
		s--;
	}
	for (int i = 1; i <= n; i++) {
		if (cc[i] == mm) {
			if (!idx) idx = i;
			ans++;
		}
	}
	printf("%d %d %d", idx, mm, ans);

	return 0;
}