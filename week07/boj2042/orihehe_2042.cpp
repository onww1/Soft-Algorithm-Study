/*
BOJ 2042 - 구간 합 구하기

시간복잡도 : O((M+K)logN)
공간복잡도 : O(2^logN)

세그먼트트리 기초 문제입니다.
*/
#include <cstdio>
#include <cmath>
#define ll long long
using namespace std;

/* 🐣🐥 */
ll arr[1000001], *tree;
ll init(int idx, int l, int r) { // 세그 트리 초기화
	if (l == r) return tree[idx] = arr[l]; // 리프노드
	// 현재 노드는 자식 노드의 합
	return tree[idx] = init(idx * 2, l, (l + r) / 2)
		+ init(idx * 2 + 1, (l + r) / 2 + 1, r);
}
void renum(int idx, int s, int e, ll k, ll val) { // k번째 값 변경
	if (k > e || k < s) return; // k를 포함하지 않는 범위라면 나가기
	tree[idx] += val;
	if (s == e) { // 리프노드라면 (s=e=k)
		arr[k] += val;
		return;
	}
	// 자식노드들 탐색
	renum(idx * 2, s, (s + e) / 2, k, val);
	renum(idx * 2 + 1, (s + e) / 2 + 1, e, k, val);
}
ll hap(int idx, int s, int e, ll l, ll r) { // 구간 합 구하기
	if (l > e || r < s) return 0; // 구하려는 구간을 완전히 벗어났을 때 
	// 구하려는 구간에 완전히 포함되어 있을 때
	if (l <= s && r >= e) return tree[idx];
	// 자식노드들 탐색
	return hap(idx * 2, s, (s + e) / 2, l, r)
		+ hap(idx * 2 + 1, (s + e) / 2 + 1, e, l, r);
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
	for (int i = 0; i < m + k; i++) {
		scanf("%d %lld %lld", &cm, &b, &c);
		if (cm == 1) {
			renum(1, 1, n, b, c - arr[b]);
		}
		else if (cm == 2) {
			printf("%lld\n", hap(1, 1, n, b, c));
		}
	}

	return 0;
}