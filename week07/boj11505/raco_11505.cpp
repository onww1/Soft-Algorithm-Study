/*
 *  BOJ 11505. 구간 곱 구하기
 *
 *  시간복잡도 : O((M+K)logN)
 *
 *  구간 합 더하기와 완전 똑같다 초기 단말노드의 값을 0에서 1로 초기화 하는 것만
 *  빼고 곱하기니까 0으로 하면 아무리 곱해도 0이 나온다. 그래서 1로 초기화 하였다.
 *
 */


#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
using namespace std;
#define MXN 1000001
#define MOD 1000000007
typedef long long ll;

int N, M, K;
ll tree[MXN * 4];
int pli;// parent_last_index 부모 노드 중에 가장 인덱스가 큰 값을 저장한다.

void init() {
	pli = 1;// root는 1부터 시작한다.
	while (pli < N) pli *= 2;
	pli--;
	// 왼쪽 노드부터 오른쪽으로 차례대로 값을 입력받는다.
	for (int i = 1; i <= pli + 1; i++) tree[pli + i] = 1;
	for (int i = 1; i <= N; i++) cin >> tree[pli + i];
	// 위에서 얻은 단말 노드 정보를 통해 부모의 값을 갱신시킨다.
	for (int i = pli; i >= 1; i--) tree[i] = (tree[i * 2] * tree[i * 2 + 1]) % MOD;
}

ll mul(int s, int e) {
	ll ret = 1;
	s += pli;
	e += pli;
	while (s <= e) {
		if (s % 2 == 1) ret = (ret * tree[s]) % MOD;
		if (e % 2 == 0) ret = (ret * tree[e]) % MOD;
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return ret;
}

void update(int idx, ll chg) {// 바꿔야 할 순서의 인덱스 index, 바꿀 숫자 change
	idx += pli;
	tree[idx] = chg;
	idx /= 2;
	while (idx) {
		tree[idx] = (tree[idx * 2] * tree[idx * 2 + 1]) % MOD;
		idx /= 2;
	}
}

int main() {
	fastio();
	cin >> N >> M >> K;
	init();

	ll a, b, c;
	for (int i = 0; i < M + K; i++) {
		cin >> a >> b >> c;
		if (a == 1) update(b, c); // update
		else cout << mul(b, c) << '\n'; // mul
	}
	return 0;
}