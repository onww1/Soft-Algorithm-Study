/*
BOJ 13977 - ���� ����� ����

�ð����⵵ : O(N+MlogP)
�������⵵ : O(N)

c�迭�� n! ���� ��� ���صӴϴ�.
���װ�� 3 ������ ���� ����̳� n!�� k!�� ������, (n-k)!�� ��������ϴ�.
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