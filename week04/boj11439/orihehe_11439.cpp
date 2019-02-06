/*
BOJ 11439 - 이항 계수 5

시간복잡도 : O(NlogN)
공간복잡도 : O(N)

어떻게 접근해야 하는지는 힌트를 들었습니다. 흑
nCk 값은 모두 정수이니 분모를 없앨 수 있다는 말이 됩니다.
따라서 조합 0의 개수 문제에서 n!에서의 x의 개수를 구하듯이 소수의 개수를 구하여
남은 개수들을 모두 곱한 값을 출력해줍니다.
*/
#include <cstdio>
#include <vector>
#define ll long long
#define pll pair<ll,ll>
using namespace std;

// num!에 있는 x개수
ll calc(ll x, ll num) { 
	ll cnt = 0;
	while (num > 0) {
		cnt += num / x;
		num /= x;
	}
	return cnt;
}
bool sosu[4000001];
vector<pll> vec;
int main() {
	ll n, k, m, ans = 1;
	scanf("%lld %lld %lld", &n, &k, &m);
	for (ll i = 2; i <= 4000000; i++) {
		if (sosu[i]) continue;
		// n!/k!(n-k)! 에 있는 i의 개수
		vec.push_back({ i,calc(i, n) - calc(i, k) - calc(i, n-k) });
		for (ll j = 2; j*i <= 4000000; j++) {
			sosu[j*i] = true;
		}
	}
	for (pll &v : vec) {
		while (v.second-- > 0) {
			ans = (ans*v.first) % m;
		}
	}
	printf("%lld", ans);

	return 0;
}