/*
BOJ 3006 - 터보소트

시간복잡도 : O(NlogN)
공간복잡도 : O(2^logN)

홀수번째 단계라면, 고른 숫자 위치 앞의 수 개수를 세주고
짝수번째 단계라면, 고른 숫자 위치 뒤의 수 개수를 세줍니다.
세준 뒤 고른 숫자 위치를 1 감소 시켜줍니다.
*/
#include <cstdio>
#include <algorithm>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
int tree[262145];
pii arr[100001];
void update(int idx, int s, int e, int k, int val) {
	if (k > e || k < s) return;
	tree[idx] += val;
	if (s == e) return;
	update(idx * 2, s, (s + e) / 2,k, val);
	update(idx * 2 + 1, (s + e) / 2 + 1, e, k, val);
}
int hap(int idx, int s, int e, int l, int r) {
	if (r < l) return 0;
	if (r<s || l >e) return 0;
	if (l <= s && e <= r) return tree[idx];
	return hap(idx * 2, s, (s + e) / 2,l,r)
		+ hap(idx * 2 + 1, (s + e) / 2 + 1, e, l,r);
}
int main() {
	int n, cur, fr, ba;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i].first);
		arr[i].second = i;
		update(1, 1, n, i, 1);
	}
	sort(arr+1, arr + n+1);
	fr = 1, ba = n;
	for (int i = 0; i < n; i++) {
		// i가 짝수일 때 앞, 홀수일 때 뒤
		if (i % 2 == 0) {
			printf("%d\n", hap(1, 1, n, 1, arr[fr].second - 1));
			update(1, 1, n, arr[fr].second, -1);
			fr++;
		}
		else {
			printf("%d\n", hap(1, 1, n, arr[ba].second + 1, n));
			update(1, 1, n, arr[ba].second, -1);
			ba--;
		}
	}

	return 0;
}