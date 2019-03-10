#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;

typedef long long ll;

ll N, M;
ll arr[100001];// i번째 심사대 시간을 담는다.
ll ans;

// t시간으로 각 심사대에서 가능한 사람의 수 t/arr[i]를 구해
// 입력으로 받은 사람 수 c에 빼준다. c가 0보다 작거나 같으면
// t시간으로 모든 사람의 입국 심사를 처리할 수 있다.
bool chk(ll t, ll c) {// time, cnt of people
	for (int i = 0; i < N; i++) {
		c -= (t / arr[i]);
		if (c <= 0) return true;
	}
	return false;
}

// 이분탐색을 통하여 m시간으로 입국심사가 가능하면
// ans에 m값을 갱신시킨다. 갱신 시킬 때 마다 더 큰 값으로 가진 않으니
// 가장 마지막에 갱신된 ans값이 M사람 모두 입국심사 할 수 있는 최소시간이다.
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
		// 심사대의 최대 개수 곱하기 각 심사대의 최대 시간 = 1e14
		bs((ll)0, (ll)1e14);
		cout << '#' << T << ' ' << ans << '\n';
	}
	return 0;
}