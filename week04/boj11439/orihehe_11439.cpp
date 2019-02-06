/*
BOJ 11439 - ���� ��� 5

�ð����⵵ : O(NlogN)
�������⵵ : O(N)

��� �����ؾ� �ϴ����� ��Ʈ�� ������ϴ�. ��
nCk ���� ��� �����̴� �и� ���� �� �ִٴ� ���� �˴ϴ�.
���� ���� 0�� ���� �������� n!������ x�� ������ ���ϵ��� �Ҽ��� ������ ���Ͽ�
���� �������� ��� ���� ���� ������ݴϴ�.
*/
#include <cstdio>
#include <vector>
#define ll long long
#define pll pair<ll,ll>
using namespace std;

// num!�� �ִ� x����
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
		// n!/k!(n-k)! �� �ִ� i�� ����
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