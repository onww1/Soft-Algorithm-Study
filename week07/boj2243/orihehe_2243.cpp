/*
BOJ 2243 - 사탕상자

시간복잡도 : O(NlogK)  k=1000000
공간복잡도 : O(2^logK)

renum함수에서 tree의 각 노드에 현재 구간의 사탕 개수를 저장합니다.
nth함수에서 k번째 사탕을 찾아줍니다.

k번째 사탕은 1~x까지 구간의 합이 k 이상인 가장 작은 x입니다.
따라서 현재 노드의 왼쪽노드가 k이상 이라면 k를 포함하므로 왼쪽으로 내려가주고,
그렇지 않다면 sum+왼쪽노드 값과 함깨 오른쪽 노드로 내려가줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
#define MAX 1000001
using namespace std;

/* 🐣🐥 */
int *tree;
void renum(int idx, int s, int e, int k, int val) {
	if (k > e || k < s) return;
	if (s == e) {
		tree[idx] += val;
		return;
	}
	renum(idx * 2, s, (s + e) / 2, k, val);
	renum(idx * 2 + 1, (s + e) / 2 + 1, e, k, val);
	tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
}
int nth(int idx, int s, int e, int k, int sum) {
	if (s == e) { // 리프노드라면 현재 노드의 사탕 주면 됨
		renum(1, 1, MAX - 1, s, -1);
		return s;
	}
	// 왼쪽 노드 + sum 이 k보다 크다면 왼쪽 노드로
	if (tree[idx*2]+sum >= k) {
		return nth(idx * 2, s, (s + e) / 2, k, sum);
	}
	else { // 오른쪽 노드로 sum에 왼쪽 노드를 더한 값 넘겨줌
		return nth(idx * 2 + 1, (s + e) / 2 + 1, e, k, sum + tree[idx * 2]);
	}
}
int main() {
	int n, h, cm, b, c;
	scanf("%d", &n);
	h = ceil(log2(MAX));
	tree = new int[1 << (h + 1)];
	fill(tree, tree + (1 << (h + 1)), 0);
	for (int i = 0; i < n; i++) {
		scanf("%d", &cm);
		if (cm == 1) {
			scanf("%d", &b);
			printf("%d\n", nth(1,1,MAX-1, b,0));
		}
		else if (cm == 2) {
			scanf("%d %d", &b, &c);
			renum(1, 1, MAX - 1, b, c);
		}
	}

	return 0;
}