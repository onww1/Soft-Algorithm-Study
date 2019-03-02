/*
BOJ 1395 - 스위치

시간복잡도 : O(MlogN)
공간복잡도 : O(2^logN)

한 구간에서 스위치 상태는 횟수%2==1 -켜짐, ==0 - 꺼짐 상태 입니다.
이걸 구현 하는게 어려웠습니다. 이렇게 저렇게 해봤는데 안 돼서 많이 고민했습니다.
내려가면서 보면 아래 노드들의 정보가 누락되고, 올라가면서 보면 위의 정보가 누락되고..
둘을 조합하면 되는 문제였습니다!

update에서는 lazy에 현재 세그 구간의 스위치 조작 횟수를 저장하고, 
업데이트 후의 자식 노드의 켜진 스위치 개수를 가져와 현재 lazy값에 따라 현재 노드를 채웠습니다.
현재 노드의 아래 정보를 저장한 것입니다.

hap에서는 구간을 찾아 내려가면서 lazy값을 모두 가져갑니다.
그리고 구할 구간에 도달하면 현재 노드 위의 lazy값을 적용하여 개수를 리턴해줍니다!
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

/* 🐣🐥 */
int *lazy, *tree;
void update(int idx, int s, int e, int l, int r) {
	if (e<l || s>r) return;
	if (l <= s && e <= r) {
		lazy[idx]++;
		tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
		if (lazy[idx] % 2) {
			tree[idx] = e - s + 1 - tree[idx];
		}
		return;
	}
	update(idx * 2, s, (s + e) / 2, l, r);
	update(idx * 2 + 1, (s + e) / 2 + 1, e, l, r);
	// 업데이트 한 자식 정보를 가져와서 현재 노드에 적용
	tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
	if (lazy[idx] % 2) {
		tree[idx] = e - s + 1 - tree[idx];
	}
}
int hap(int idx, int s, int e, int l,int r, int sum) {
	if (e<l || s>r) return 0;
	sum += lazy[idx]; // lazy값을 가져간다.
	if (l <= s && e <= r) {
		sum -= lazy[idx]; // 현재 lazy값은 이미 적용 되어있으니 빼주고
		if (sum % 2) { // 반전
			return e - s + 1 - tree[idx];
		}
		return tree[idx];
	}
	return hap(idx * 2, s, (s + e) / 2, l, r, sum)
		+ hap(idx * 2 + 1, (s + e) / 2 + 1, e, l, r, sum);
}
int main() {
	int n, m, cm, a, b, h;
	scanf("%d %d", &n, &m);
	h = ceil(log2(n)) + 2;
	h = 1 << h;
	tree = new int[h];
	lazy = new int[h];
	fill(tree, tree + h, 0);
	fill(lazy, lazy + h, 0);
	while (m--) {
		scanf("%d %d %d", &cm, &a, &b);
		if (cm == 0) {
			update(1, 1, n, a, b);
		}
		else if (cm == 1) {
			printf("%d\n", hap(1, 1, n, a, b, 0));
		}
	}

	return 0;
}