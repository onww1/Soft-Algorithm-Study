/*
 *  수열과 쿼리16의 소스에서 find_miv의 리턴 값을 miv.second에서
 *  miv.first로 바꾼것만 다릅니다. 수열과 쿼리16을 참고하면 됩니다.
 *
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;
#define MXN 100002
typedef pair<int, int> pi;

pi tree[MXN * 4];
int N, M;
int pli;
const int INF = 2e9;

bool cmp(pi a, pi b) {
	if (a.first == b.first) return a.second < b.second;
	return a.first < b.first;
}

void init() {
	cin >> N;
	pli = 1;
	while (pli < N) pli *= 2;
	pli--;
	int a;
	for (int i = 1; i <= pli + 1; i++) {
		tree[pli + i] = { INF, 0 };
	}
	for (int i = 1; i <= N; i++) {
		cin >> a;
		tree[pli + i] = { a,i };
	}
	for (int i = pli; i >= 1; i--) {
		tree[i] = cmp(tree[i * 2], tree[i * 2 + 1]) ? tree[i * 2] : tree[i * 2 + 1];
	}
}

void update(int idx) {
	while (idx) {
		tree[idx] = cmp(tree[idx * 2], tree[idx * 2 + 1]) ? tree[idx * 2] : tree[idx * 2 + 1];
		idx /= 2;
	}
}

int find_miv(int s, int e) {
	s += pli;
	e += pli;
	pi miv = { INF, 0 };
	while (s <= e) {
		if (s % 2 == 1) {
			if (miv.first > tree[s].first) miv = tree[s];
			else if (miv.first == tree[s].first && miv.second > tree[s].second) miv = tree[s];
		}
		if (e % 2 == 0) {
			if (miv.first > tree[e].first) miv = tree[e];
			else if (miv.first == tree[e].first && miv.second > tree[e].second) miv = tree[e];
		}
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return miv.first;
}

int main() {
	fastio();
	init();
	cin >> M;
	int q, a, b;
	for (int i = 0; i < M; i++) {
		cin >> q >> a >> b;
		if (q == 1) {
			tree[pli + a].first = b;
			update((pli + a) / 2);
		}
		else cout << find_miv(a, b) << '\n';
	}
	return 0;
}