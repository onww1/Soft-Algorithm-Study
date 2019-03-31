/*
BOJ 1948 - 임계경로

시간복잡도 : O(M)
공간복잡도 : O(M)

각 정점에 그 정점으로 들어오는 경로들 중 도착시간이 큰 값의 직전 정점을 저장해둡니다.
도로의 개수는 정점에 저장되어있는 직전 정점의 수의 합과 같습니다.
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
vector<pii> vec[10001];
vector<int> p[10001];  // 정점으로 들어오는 최댓값의 직전정점
queue<int> q;
int deg[10001], arr[10001];  // arr : 정점으로 들어오는 시간 최댓값
bool visited[10001];
int n, m, a, b, c, ans;
void dfs(int cur) { // 직전정점 탐색
	visited[cur]= true;
	ans += p[cur].size();
	for (int pp : p[cur]) {
		if(!visited[pp])
			dfs(pp);
	}
}
int main() {
	scanf("%d %d", &n, &m);
	while (m--) {
		scanf("%d %d %d", &a, &b, &c);
		vec[a].push_back({ c,b });
		deg[b]++;
	}
	scanf("%d %d", &a, &b);
	q.push(a);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (pii v : vec[cur]) {
			int tmp = arr[cur] + v.first;
			if (tmp > arr[v.second]) { // 최댓값 갱신
				arr[v.second] = tmp;
				p[v.second].clear();
				p[v.second].push_back(cur);
			}
			else if (tmp == arr[v.second]) { // 최댓값이 같다면 
				p[v.second].push_back(cur);
			}
			deg[v.second]--;
			if (deg[v.second] == 0) q.push(v.second);
		}
	}
	ans = p[b].size();
	for (int pp : p[b]) {
		dfs(pp);
	}
	printf("%d\n%d", arr[b], ans);

	return 0;
}