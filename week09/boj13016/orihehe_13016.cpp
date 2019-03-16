/*
BOJ 13016 - 내 왼손에는 흑염룡이 잠들어 있다

시간복잡도 : O(N)
공간복잡도 : O(N)

처음 풀 때는 트리의 지름을 구해두고, 지름에 포함된 노드와 아닌 노드를 나누어서
포함된 노드는 지름의 위, 아래중 큰값을, 포함되지 않은 것은 max(위, 아래) + 지름까지 거리를
답으로 생각하고 코딩을 해봤지만 WA를 받았습니다. 흑흑

트리 디피란 걸 알고 생각해봤는데, 루트를 정해두고 한 노드를 기준으로 
위나 아래로의 거리의 최대가 그 노드의 답이 됐습니다.
아래로의 거리는 자식노드들만 봐주고, 위로의 거리는 루트부터 타고 내려오면서
내려가는 노드 외의 형제 노드들을 타고 내려갈 시의 최댓값과 현재 가져온 최댓값 중 큰 값을 보내줍니다.

그래서 우선 dfs로 현재 노드의 자식들을 타고 갔을 때의 최댓값과 두번째로 큰 값을 저장해줬습니다.
두번째로 큰 값은 최댓값인 노드를 타고 내려갈 시 최댓값을 사용하면 안 되니 구해줘야합니다.

solve에선 내려가며 현재 가진 최댓값과 내려가려는 곳 외의 형제중 최댓값의 큰 값을 보내주며
현재 노드에서 가장 먼 값은 자식의 최댓값과 현재 가진 값 중 큰 값이 됩니다.
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
vector<pii> vec[50001];
int p[50001], ans[50001];
pii mx[50001];
int dfs(int cur) {
	int tmp;
	for (pii v : vec[cur]) {
		if (p[cur] != v.second) {
			p[v.second] = cur;
			// 자식의 최댓값 + 간선
			tmp = dfs(v.second) + v.first;
			// 최댓값이라면 이미 저장된 최댓값을 두번째 큰 값으로
			if (tmp >= mx[cur].first) {
				mx[cur].second = mx[cur].first;
				mx[cur].first = tmp;
			}
			// 두번째 큰 값보다 크다면
			else if (tmp > mx[cur].second) {
				mx[cur].second = tmp;
			}
		}
	}
	return mx[cur].first;
}
void solve(int cur, int sum) {
	// 현재 가진 값(위로 가는 거리) 자식의 최댓값(아래) 중 큰 값
	ans[cur] = max(sum, mx[cur].first);
	for (pii v : vec[cur]) {
		if (p[cur] != v.second) {
			// 최댓값이 지금 내려가는 곳의 값이라면
			if (mx[cur].first == v.first + mx[v.second].first) {
				// 두번째 큰 값과 현재 값 중 큰값을 내려준다
				solve(v.second, max( sum, mx[cur].second) + v.first);
			}
			else solve(v.second, max(sum, mx[cur].first) + v.first);
		}
	}
}
int main() {
	int n, a, b, c;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		vec[a].push_back({ c,b });
		vec[b].push_back({ c,a });
	}
	dfs(1);
	solve(1, 0);
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);

	return 0;
}