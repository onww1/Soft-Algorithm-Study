/*
BOJ 13977 - 이항 계수와 쿼리

시간복잡도 : O(N+MlogP)
공간복잡도 : O(N)

c배열에 n! 값을 모두 구해둡니다.
이항계수 3 문제와 같은 방식이나 n!에 k!을 나누고, (n-k)!을 나눠줬습니다.
*/
#include <cstdio>
#include <algorithm>
#define ll long long
#define mod 1000000007
using namespace std;

ll myPow(ll a, ll b) {
	ll ans = 1;
	while (b > 0) {
		if (b % 2 == 1) {
			ans = (ans*a) % mod;
		}
		a = (a*a) % mod;
		b /= 2;
	}
	return ans;
}
ll c[4000001];
int main() {
	int t;
	ll n, k, up = 1, dw = 1;
	scanf("%d", &t);
	c[0] = 1;
	for (ll i = 1; i <= 4000000; i++) {
		c[i] = (c[i - 1] * i) % mod;
	}
	while (t--) {
		scanf("%lld %lld", &n, &k);
		up = c[n];
		printf("%lld\n", ((up*myPow(c[k], mod - 2))%mod*myPow(c[n-k], mod - 2))% mod);
	}

	return 0;
}