/*
BOJ 11401 - ���� ��� 3

�ð����⵵ : O(NlogP)
�������⵵ : O(1)

nCk n!/(k!*(n-k)!) ���� up�� n!/k!��, dw�� (n-k)!�� ���صӴϴ�.
�丣���� �������� a^p%p = a%p �Ŀ��� a�� �� �� ���� a^(p-2) %p = a^-1 %p ���� ����,
��ⷯ �յ��� �������� (up/dw)%p = (up%p * (dw^-1%p))%p �̰�
(up%p * dw^(p-2)%p)%p�� ���� ���� �� �ֽ��ϴ�.
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