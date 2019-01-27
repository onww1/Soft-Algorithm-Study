/*
BOJ 1033 - Ĭ����

������ ��� �ؾ����� �� ���� ����� �����Դϴ�.
�� ����� ������ �ٲ�� �ٸ� ������ ������ �׿� ���� �ٲ�Ƿ� �׷����� ����� ���� �� ���ҽ��ϴ�.
�м� ���´� first�� ����, second�� �и��� pair�� ���������ϴ�.

a->b �������� p/q�� ���м��� ����� �����մϴ�.
��� ���������� ���� �� 0�� ����� ������ 1�� �ΰ� dfs�Լ��� ���Ƚ��ϴ�.
dfs���� ������ ��� �Դ���(p), ���� �� �� �������(cur)�� �Ű������� �ΰ�,
p�� ������ cur->p�� ������ ���� ���� ����� ������ ��������ϴ�.

dfs�� ������ ���� ��� ���м� ���·� ������ ��� ������ �и��� �ּҰ������ ���� ���Ѱ��� ������ݴϴ�.
*/
#include <cstdio>
#include <algorithm>
#define ll long long
#define P pair<ll,ll>
using namespace std;

P vec[12][12];
P arr[12];  // ��Ằ ����
int n, a, b;
ll p, q, t = 1, tm;
ll gcd(ll a, ll b) {  // �ִ�����
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
	ll up = arr[p].first*vec[cur][p].first; // ����
	ll dw = arr[p].second*vec[cur][p].second; // �и�
	ll tp = gcd(up, dw);
	arr[cur] = { up / tp,dw / tp };  // ���м��� ����
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
	// 0�� 1�� �ΰ� �� ���̱� ������ 0->11 ������ 1 : 1 ������ ������ݴϴ�.
	arr[11] = { 1,1 };
	vec[0][11] = { 1,1 };
	dfs(11, 0);
	for (int i = 0; i < n; i++) {
		tm = gcd(t, arr[i].second);
		t *= arr[i].second / tm;  // ��� �и��� �ּҰ����
	}
	for (int i = 0; i < n; i++)
		printf("%lld ", arr[i].first*t / arr[i].second);

	return 0;
}