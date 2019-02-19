/*
BOJ 11505 - 구간 곱 구하기

시간복잡도 : O((M+K)logN)
공간복잡도 : O(2^logN)

init에서 트리의 각 노드에 두 자식노드를 곱한 값을 저장합니다.
renum에서 리프노드에 도달했을 때 그 수를 바꿔주고, 현재 노드에 두 자식노드를 곱한 값을 저장합니다.
mul에서 원하는 구간의 곱을 구해줍니다.
*/
#include <cstdio>
#include <cmath>
#define ll long long
#define mod 1000000007
using namespace std;

/* 🐣🐥 */
ll arr[1000001], *tree;
ll init(int idx, int l, int r) {
	if (l == r) return tree[idx] = arr[l]; // 리프노드일 때
	// 현재 노드에 두 자식 노드의 곱을 저장
	return tree[idx] = (init(idx * 2, l, (l + r) / 2)
		*init(idx * 2 + 1, (l + r) / 2 + 1, r))%mod;
}
void renum(int idx, int s, int e, ll k, ll val) {
	if (k > e || k < s) return; // 구간 밖이라면
	if (s == e) { // 리프노드일 때 값 바꿔줌
		tree[idx] += val;
		arr[k] += val;
		return;
	}
	// 자식노드 탐색
	renum(idx * 2, s, (s + e) / 2, k, val);
	renum(idx * 2 + 1, (s + e) / 2 + 1, e, k, val);
	// 현재 노드에 두 자식 노드의 곱 저장
	tree[idx] =(tree[idx * 2] * tree[idx * 2 + 1])%mod;
}
ll mul(int idx, int s, int e, ll l, ll r) {
	if (l > e || r < s) return 1; // 구간에 겹치지 않으면
	if (l <= s && r >= e) return tree[idx]; // 구간을 완전히 포함하면
	// 곱 반환
	return (mul(idx * 2, s, (s + e) / 2, l, r)
		* mul(idx * 2 + 1, (s + e) / 2 + 1, e, l, r))%mod;
}
int main() {
	int n, m, k, h, cm;
	ll b, c;
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &arr[i]);
	}
	h = ceil(log2(n));
	tree = new ll[1 << (h + 1)];
	init(1, 1, n);
	for (int i = 0; i < m+k; i++) {
		scanf("%d %lld %lld", &cm, &b, &c);
		if (cm == 2) {
			printf("%lld\n", mul(1, 1, n, b, c));
		}
		else if (cm == 1) {
			renum(1, 1, n, b, c - arr[b]);
		}
	}

	return 0;
}