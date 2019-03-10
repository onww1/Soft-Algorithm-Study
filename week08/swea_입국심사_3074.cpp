#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;

typedef long long ll;

ll N, M;
ll arr[100001];// i��° �ɻ�� �ð��� ��´�.
ll ans;

// t�ð����� �� �ɻ�뿡�� ������ ����� �� t/arr[i]�� ����
// �Է����� ���� ��� �� c�� ���ش�. c�� 0���� �۰ų� ������
// t�ð����� ��� ����� �Ա� �ɻ縦 ó���� �� �ִ�.
bool chk(ll t, ll c) {// time, cnt of people
	for (int i = 0; i < N; i++) {
		c -= (t / arr[i]);
		if (c <= 0) return true;
	}
	return false;
}

// �̺�Ž���� ���Ͽ� m�ð����� �Ա��ɻ簡 �����ϸ�
// ans�� m���� ���Ž�Ų��. ���� ��ų �� ���� �� ū ������ ���� ������
// ���� �������� ���ŵ� ans���� M��� ��� �Ա��ɻ� �� �� �ִ� �ּҽð��̴�.
void bs(ll s, ll e) {
	while (s <= e) {
		ll m = (e + s) / 2;
		if (chk(m, M)) {
			e = m - 1;
			ans = m;
		}
		else s = m + 1;
	}
}

int main() {
	fastio();
	int TC;
	cin >> TC;
	for (int T = 1; T <= TC; T++) {
		cin >> N >> M;
		ans = -1;
		for (int i = 0; i < N; i++) {
			cin >> arr[i];
		}
		// �ɻ���� �ִ� ���� ���ϱ� �� �ɻ���� �ִ� �ð� = 1e14
		bs((ll)0, (ll)1e14);
		cout << '#' << T << ' ' << ans << '\n';
	}
	return 0;
}