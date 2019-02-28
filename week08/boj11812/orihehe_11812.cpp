/*
BOJ 11812 - K진 트리

시간복잡도 : O(QlogN)
공간복잡도 : O(logN)

각 깊이별로 노드수는 k^깊이 입니다.
그 노드수를 wprhq배열에 부분합으로 저장해주면, a와b의 깊이를 구해줄 수 있습니다.
k가 1인 경우를 제외하고 lca에서 두 노드가 같아질때까지 한칸씩 올려줍니다.
노드를 왼쪽부터 차례로 추가하므로 현재 노드의 부모는 (a - 1 + k - 1) / k 가 됩니다.
*/
#include <cstdio>
#include <algorithm>
#define ll long long
using namespace std;

/* 🐣🐥 */
ll wprhq[51];
int wp, q; // wp는 wprhq배열 end
ll k, n, a, b, x = 1;
ll lca(ll a, ll b) {
	int da, db; // 깊이
	ll ret = 0;
	da = lower_bound(wprhq, wprhq + wp, a)-wprhq;
	db = lower_bound(wprhq, wprhq + wp, b)-wprhq;

	if (da > db) { // b가 더 깊게
		swap(a, b);
		swap(da, db);
	}
	while (db > da) { // 한칸씩 깊이 올려줌
		db--;
		b = (b - 1 + k - 1) / k;
		ret++;
	}
	if (a == b) return ret;
	while (a != b) { // 같을 때까지 올려줌
		ret += 2;
		b = (b - 1 + k - 1) / k;
		a = (a - 1 + k - 1) / k;
	}
	return ret;
}
int main() {
	scanf("%lld %lld %d", &n, &k, &q);
	wprhq[0] = 1;
	if (k != 1) {
		for (int i = 1; wprhq[i - 1] < n; i++) {
			wprhq[i] = x * k + wprhq[i - 1];
			wp = i;
			x *= k;
		}
	}
	wp++;
	while (q--) {
		scanf("%lld %lld", &a, &b);
		if (k == 1) {
			if (a < b) swap(a, b);
			printf("%lld\n", a - b);
		}
		else printf("%lld\n", lca(a, b));
	}

	return 0;
}