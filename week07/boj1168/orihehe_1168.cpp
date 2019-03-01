/*
BOJ 1168 - 조세퍼스 문제 2

시간복잡도 : O(NlogN)
공간복잡도 : O(2^logN)

현재 위치에서 (m - 1) % i + 1 뒤의 사람을 지워야 합니다.
마지막으로 지운 사람의 위치(st)에서부터 n까지 m%i 이상의 사람이 있다면 st~n에서,
부족하다면 st~n까지 사람을 빼고, 1~n에서
이분탐색을 사용하여 지울 사람의 위치를 구해줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

/* 🐣🐥 */
int *tree;
int n, m, h, st = 1;
int used[100001];
void update(int idx, int s, int e, int k, int val) {
	if (k<s || k>e) return;
	tree[idx] += val;
	if (e == s) {
		return;
	}
	update(idx * 2, s, (s + e) / 2, k, val);
	update(idx * 2 + 1, (s + e) / 2 + 1, e, k, val);
}
int hap(int idx, int s, int e, int l, int r) {
	if (r < s || e < l) return 0;
	if (l <= s && e <= r) return tree[idx];
	return hap(idx * 2, s, (s + e) / 2, l, r)
		+ hap(idx * 2 + 1, (s + e) / 2 + 1, e, l, r);
}
int bs(int ss, int val) { // 이분탐색
	int l = ss, r = n, mid, res, ret = 0;
	while (l <= r) {
		mid = (l + r) / 2;
		res = hap(1, 1, n, ss, mid);
		if (res >= val) {
			ret = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	return ret;
}
int main() {
	int tmp, tar;
	scanf("%d %d", &n, &m);
	h = ceil(log2(n)) + 1;
	tree = new int[1 << h];
	fill(tree, tree + (1 << h), 0);
	printf("<");
	for (int i = 1; i <= n; i++) {
		update(1, 1, n, i, 1); // 각 위치에 사람 추가
	}
	for (int i = n; i >= 2; i--) {
		tmp = hap(1, 1, n, st, n);
		tar = (m - 1) % i + 1;
		if (tmp >= tar) { // 지울 사람이 st~n 사이라면 st부터
			tmp = bs(st, tar);
		}
		else { // 지울 사람을 1에서 부터 봐야함
			tmp = bs(1, tar - tmp);
		}
		printf("%d, ", tmp);
		st = tmp;
		used[st] = true;
		update(1, 1, n, st, -1); // st위치 사람 빼줍니다.
	}
	// 마지막 남은 사람
	for (int i = 1; i <= n; i++) {
		if (!used[i]) return !printf("%d>", i);
	}

	return 0;
}