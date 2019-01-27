/*
BOJ 1033 - 칵테일

구현을 어떻게 해야할지 꽤 많이 고민한 문제입니다.
한 재료의 질량이 바뀌면 다른 재료들의 질량도 그에 따라 바뀌므로 그래프로 만들면 좋을 것 같았습니다.
분수 형태는 first는 분자, second는 분모인 pair로 만들어줬습니다.

a->b 간선에는 p/q를 기약분수로 만들어 저장합니다.
모든 간선정보를 넣은 후 0번 재료의 질량을 1로 두고 dfs함수를 돌렸습니다.
dfs에선 이전에 어디서 왔는지(p), 현재 몇 번 재료인지(cur)를 매개변수로 두고,
p의 질량과 cur->p의 간선을 곱해 현재 재료의 질량을 구해줬습니다.

dfs가 끝나고 값이 모두 기약분수 형태로 있으니 모든 재료들의 분모의 최소공배수를 구해 곱한값을 출력해줍니다.
*/
#include <cstdio>
#include <algorithm>
#define ll long long
#define P pair<ll,ll>
using namespace std;

P vec[12][12];
P arr[12];  // 재료별 질량
int n, a, b;
ll p, q, t = 1, tm;
ll gcd(ll a, ll b) {  // 최대공약수
	if (b > a) swap(a, b);
	ll tmp;
	while (b > 0) {
		tmp = a;
		a = b;
		b = tmp % b;
	}
	return a;
}
void dfs(int p, int cur) {
	ll up = arr[p].first*vec[cur][p].first; // 분자
	ll dw = arr[p].second*vec[cur][p].second; // 분모
	ll tp = gcd(up, dw);
	arr[cur] = { up / tp,dw / tp };  // 기약분수로 저장
	for (int i = 0; i < n; i++) {
		if (vec[cur][i].first != 0 && arr[i].first == 0)
			dfs(cur, i);
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d %d %lld %lld", &a, &b, &p, &q);
		tm = gcd(p, q);
		vec[a][b] = { p / tm,q / tm };
		vec[b][a] = { q / tm,p / tm };
	}
	// 0을 1로 두고 할 것이기 때문에 0->11 간선을 1 : 1 비율로 만들어줍니다.
	arr[11] = { 1,1 };
	vec[0][11] = { 1,1 };
	dfs(11, 0);
	for (int i = 0; i < n; i++) {
		tm = gcd(t, arr[i].second);
		t *= arr[i].second / tm;  // 모든 분모의 최소공배수
	}
	for (int i = 0; i < n; i++)
		printf("%lld ", arr[i].first*t / arr[i].second);

	return 0;
}