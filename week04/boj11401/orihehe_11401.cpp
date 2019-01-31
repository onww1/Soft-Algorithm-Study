/*
BOJ 11401 - 이항 계수 3

시간복잡도 : O(NlogP)
공간복잡도 : O(1)

nCk n!/(k!*(n-k)!) 에서 up엔 n!/k!을, dw엔 (n-k)!를 구해둡니다.
페르마의 소정리로 a^p%p = a%p 식에서 a로 두 번 나눈 a^(p-2) %p = a^-1 %p 또한 성립,
모듈러 합동의 성질에서 (up/dw)%p = (up%p * (dw^-1%p))%p 이고
(up%p * dw^(p-2)%p)%p로 답을 구할 수 있습니다.
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
int main() {
	ll n, k, up = 1, dw = 1;
	scanf("%lld %lld", &n, &k);
	k = max(k, n - k);
	for (ll i = k + 1; i <= n; i++) {
		up = (up*i) % mod;
	}
	for (ll i = 2; i <= n - k; i++) {
		dw = (dw*i) % mod;
	}
	printf("%lld", up*myPow(dw, mod - 2) % mod);

	return 0;
}