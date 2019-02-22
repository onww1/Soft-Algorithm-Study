/*
BOJ 3653 - 영화 수집

시간복잡도 : O(Mlog(N+M)
공간복잡도 : O(2^log(200000))

트리를 N제한으로만 짜려고만 생각하다 오래 걸렸습니다ㅠㅠ
세그트리의 리프노드를 생각했을 때 1~n의 맨 오른쪽을 맨 위라고 생각합니다.
arr배열에 각 DVD의 인덱스를 저장해두고, n=5일때 5,4,3,2,1로 DVD를 쌓아둡니다. 
그리고나서, 선택한 DVD의 인덱스~최고 높이 까지의 합을 출력해주고 
그 DVD를 삭제 후 최고높이 +1에 쌓아줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
#define MAX 200001
using namespace std;

/* 🐣🐥 */
int *tree;
int arr[100001];
void update(int idx, int s, int e, int k, int val) {
	if (k < s || k > e) return;
	tree[idx]+=val;
	if (s == e) return;
	update(idx * 2, s, (e + s) / 2, k, val);
	update(idx * 2 + 1, (e + s) / 2 + 1, e, k,val);
	tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
}
int hap(int idx, int s, int e, int l, int r) {
	if (l > e || r < s) return 0;
	if (l <= s && e <= r) return tree[idx];
	return hap(idx * 2, s, (e + s) / 2, l, r)
		+ hap(idx * 2 + 1, (e + s) / 2 + 1, e, l, r);
}
int main() {
	int t, n, m, h, end, x;
	scanf("%d", &t);
	h = ceil(log2(MAX)) + 1;
	tree = new int[1 << h];
	while (t--) {
		scanf("%d %d", &n, &m);
		fill(tree, tree + (1 << h), 0);
		end = n; // 최고 높이
		for (int i = 1; i <= n; i++) {
			update(1, 1, n + m, i, 1); // 각 DVD 쌓아줌
			arr[i] = n - i + 1; 
		}
		for (int i = 0; i < m; i++) {
			scanf("%d", &x);
			printf("%d ", hap(1, 1, n + m, arr[x], end)-1);
			update(1, 1, n + m, arr[x], -1); // 현재 DVD삭제
			arr[x] = ++end; // 높이 증가
			update(1, 1, n + m, arr[x], 1); // 현재 DVD 맨 위에
		}
		printf("\n");
	}

	return 0;
}