/*
BOJ 7812 - 중앙 트리

우선 0을 루트로 두고 init에서 0에서의 모든 노드로의 경로 합(sum)을 구합니다.
그 후 dfs 함수에서 자식으로 내려가면서 구해둔 sum을 이용해 그 자식에서의 모든 노드로의 경로 합을 구해줍니다.
현재 노드에서 자식으로 내려가면서 어떤 값이 변하는 지를 생각해보면
cur-자식을 잇는 가중치를 x로 두면 내려가면서 자식들 수 * x만큼 감소하고, 
간선수(n-1)에서 cur과 자식을 잇는 간선1개 제외, (n-2-자식들 수) * x만큼 증가합니다.
*/
#include <cstdio>
#include <vector>
#include <algorithm>
#define ll long long
#define P pair<ll,ll>
using namespace std;

vector<P> vec[10001];
P parent[10001];
ll ans, n;
// init에서 cur의 자식 수와 cur에서 자식으로 가는 비용의 합을 구함.
ll init(ll cur) {
	ll vcnt = 0;
	ll sum = 0;
	for (P &v : vec[cur]) {
		if (parent[cur].first == v.first) continue;
		parent[v.first].first = cur, vcnt++;
		// v자식으로 가는 비용은 cur-v의 가중치 * (v자식 수 + 1)
		sum += v.second + init(v.first); // v까지의 합 + v-cur
		sum += v.second*parent[v.first].second; // v-cur * v자식수
		// 현재 노드 자식 수는 내 자식수 + 내 자식의 자식수를 더한것
		vcnt += parent[v.first].second; 
	}
	parent[cur].second = vcnt; // 자식 노드 수 저장
	return sum;
}
void dfs(ll cur, ll sum) {
	ans = min(ans, sum);
	for (P &v : vec[cur]) {
		if (parent[cur].first == v.first) continue;
		dfs(v.first, sum - v.second*parent[v.first].second * 2
			+ v.second*(n - 2));
	}
}
int main() {
	ll a, b, c;
	while (scanf("%lld", &n)) {
		if (n == 0) break;
		ans = 987987987987987987;
		for (int i = 1; i < n; i++) {
			scanf("%lld %lld %lld", &a, &b, &c);
			vec[a].push_back({ b,c });
			vec[b].push_back({ a,c });
		}
		dfs(0, init(0));
		printf("%lld\n", ans);
		for (int i = 0; i < n; i++) {
			vec[i].clear();
			parent[i] = { 0,0 };
		}
	}

	return 0;
}