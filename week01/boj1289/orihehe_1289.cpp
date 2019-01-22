/*
BOJ 1289 - 트리의 가중치

현재 노드에서 자식을 타고 내려가는 경로 가중치의 합을 식으로 구한 후 묶어보면
(현재 노드의 자식의 경로 가중치 합) * (현재 노드에서 자식으로 가는 간선의 가중치) 임을 볼 수 있습니다.
또한 현재 노드의 자식들끼리의 경로 가중치 합 또한 구해주어야 하므로
이전까지 구한 자식들의 경로 가중치 합에 지금 구한 자식에서 나온 경로 가중치를 곱해줍니다.
구해야 할 값은 모든 경로 가중치 합이므로 값을 구할 때마다 리턴할 값에 더해줍니다.
*/
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define ll long long
#define P pair<int,int>
#define mod 1000000007
using namespace std;

vector<P> vec[100001];
int parent[100001];
ll ans;
ll dfs(int cur) {
	int vcnt = 0;
	ll ret = 0; // cur에서 자식들로 가는 경로 가중치 합 (리턴할 값)
	for (P &v : vec[cur]) { // 한 자식씩
		if (parent[cur] == v.first) continue;
		parent[v.first] = cur; vcnt++;
		ll re = dfs(v.first); // 한 자식에서 나올 경로 가중치 합

		// cur->자식 간선 가중치 + 자식의 경로 가중치 합 * cur->자식 간선 가중치
		ll rr = (v.second*re + v.second) % mod; 
		ans = (ans + rr + rr * ret) % mod; // 이미 탐색한 자식들로 가는 경로를 더함
		ret = (ret + rr) % mod;			   // 탐색한 자식들로 가는 경로의 가중치 합
	}
	if (vcnt == 0) return 0; // 리프노드일 때 0 반환
	return ret;
}
int main() {
	int n, a, b, c;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		vec[a].push_back({ b,c });
		vec[b].push_back({ a,c });
	}
	dfs(1);
	printf("%lld", ans);

	return 0;
}