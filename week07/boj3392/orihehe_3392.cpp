/*
BOJ 3392 - 화성 지도

시간복잡도 : O(NlogK)  K=30000
공간복잡도 : O(2^logK)

레이지를 조금 변형하여 풀었습니다.
x좌표를 기준으로 y좌표 구간을 세그트리에 넣어줄겁니다.
트리를 pair<현재 세그 구간의 y구간 개수, 현재 세그 구간의 y좌표 개수>로 설정합니다.

y구간을 그려줄 땐 update의 val에 1을 주고, pair.first에 val을 더해줍니다. (y구간 개수)
만약 first가 1이상이라면 그 세그 구간만큼 y좌표가 그려진 것이니 second는 e-l+1
first가 0이라면 그 세그 구간은 자식의 second값을 더한 값이 됩니다.
직사각형의 x끝에 도달하면 val에 -1을 주고 update를 해주면 됩니다.

높이를 h = ceil(log2(MAX)) + 1로 두고 풀었다가 런타임 에러를 받았는데,
update에서 리프노드일 때 또한 자식노드를 찾아 배열을 벗어나 생기는 문제였습니다..
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>
#define pii pair<int,int>
#define MAX 30001
using namespace std;

/* 🐣🐥 */
pii *tree; // 앞 : 켜진 횟수, 뒤 : 켜진 노드 개수
struct sq {
	int x1, y1, x2, y2;
	// x좌표 끝지점 가까운 것부터 나오도록
	bool operator <(const sq &a) const { 
		return x2 > a.x2;
	}
};
bool cmp(sq &a, sq &b) { // x좌표 기준 정렬
	return a.x1 < b.x1;
}
sq arr[10001];
priority_queue<sq> pq; // 끝나는 시점 기준으로 뽑자
void update(int idx, int s, int e, int l, int r, int val) {
	if (r < s || l > e) return;
	if (l <= s && e <= r) {
		tree[idx].first += val;
		if (tree[idx].first <= 0) {
			tree[idx].second = tree[idx * 2].second + tree[idx * 2 + 1].second;
		}
		else {
			tree[idx].second = e - s + 1;
		}
		return;
	}
	update(idx * 2, s, (s + e) / 2, l, r, val);
	update(idx * 2 + 1,(s + e) / 2 + 1, e, l, r, val);
	if (tree[idx].first <= 0) 
		tree[idx].second = tree[idx * 2].second + tree[idx * 2 + 1].second;
}
int main() {
	int n, h, ap = 0, ans = 0;
	scanf("%d", &n);
	h = ceil(log2(MAX)) + 2;
	tree = new pii[1 << h];
	fill(tree, tree + (1 << h), pii(0,0));
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d %d", &arr[i].x1, &arr[i].y1, &arr[i].x2, &arr[i].y2);
	}
	sort(arr, arr + n, cmp);
	for (int i = 0; i <= MAX; i++) {
		while (ap < n && arr[ap].x1 == i) {
			update(1, 1, MAX, arr[ap].y1+1, arr[ap].y2, 1);
			pq.push(arr[ap++]); // 넣을 때 세그에 그려주자
		}
		while (!pq.empty() && pq.top().x2 <= i) {
			update(1, 1, MAX, pq.top().y1+1, pq.top().y2, -1);
			pq.pop(); // 뺄 때 세그에서 빼주자
		}
		ans += tree[1].second; // i좌표 합
	}
	printf("%d", ans);

	return 0;
}