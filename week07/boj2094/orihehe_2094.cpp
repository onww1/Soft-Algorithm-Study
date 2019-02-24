/*
BOJ 2094 - 강수량

시간복잡도 : O(MlogN)
공간복잡도 : O(2^logN)

구데기 코드입니다....
각 경우를 잘 나누어 풀어주면 됩니다. main에 각 경우를 써뒀습니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
#define pii pair<int,int>
#define pib pair<int,bool>
#define pbb pair<bool,bool>
#define MAX 1000000000
using namespace std;

/* 🐣🐥 */
pib *tree;
pii arr[50002];
void update(int idx, int s, int e, int k, int val) {
	if (k<s || k > e) return;
	if (s == e) {
		tree[idx] = { val,true };
		return;
	}
	update(idx * 2, s, (e + s) / 2, k, val);
	update(idx * 2 + 1, (e + s) / 2 + 1, e, k, val);
	// 구간의 최댓값 저장
	tree[idx] = max(tree[idx * 2], tree[idx * 2 + 1]);
	if (tree[idx * 2].second && tree[idx * 2 + 1].second) { // 구간 연속한 년도 다 있으면
		if (arr[(e + s) / 2].first + 1 == arr[(e + s) / 2 + 1].first) { // 지금도 연속하면
			tree[idx].second = true;
		}
		else tree[idx].second = false;
	}
	else {
		tree[idx].second = false;
	}
}
pbb getAns(int idx, int s, int e, int l, int r, int k) {// pair의 앞은 가능한지, 뒤는 연속한지
	if (l > e || r < s) return { true,true };
	else if (l <= s && e <= r) {
		if (tree[idx].first >= k) return { false,false }; // k강수량보다 큰값이면 false
		else if (tree[idx].second) return { true,true }; // 연속하다면 true
		else return { true,false }; // k강수량보다 큰값은 없지만 연속하지 않을 때
	}

	pbb tmp1 = getAns(idx * 2, s, (e + s) / 2, l, r, k);
	pbb tmp2 = getAns(idx * 2 + 1, (e + s) / 2 + 1, e, l, r, k);
	return { tmp1.first && tmp2.first, tmp1.second && tmp2.second };
}

int main() {
	int n, m, h, b, a;
	pbb ans;
	scanf("%d", &n);
	h = ceil(log2(n));
	tree = new pib[1 << (h + 1)];
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &arr[i].first, &arr[i].second);
		update(1, 1, n, i, arr[i].second);
	}
	scanf("%d", &m);
	while (m--) {
		scanf("%d %d", &a, &b);
		int ii = lower_bound(arr + 1, arr + n + 1, pii(a, -MAX)) - arr;
		int jj = lower_bound(arr + 1, arr + n + 1, pii(b, -MAX)) - arr;
		if (arr[jj].first != b && arr[ii].first != a) { // 년도 둘 다 없을 때
			printf("maybe\n");
		}
		else if (arr[jj].first != b) { // X년도 없을 때
			// Y는 있음. 연속하다면 X년도 Y년도 사이 주어진 값이 없음
			if (ii + 1 == jj) {
				printf("maybe\n");
			}
			else {
				ans = getAns(1, 1, n, ii + 1, jj - 1, arr[ii].second);
				if (ans.first) // Y강수량보다 모두 작을 때
					printf("maybe\n");
				else printf("false\n");
			}
		}
		else if (arr[ii].first != a) { // Y년도 없을 때
			// ii는 Y년도보다 큰 값 가르키니, Y년도 X년도 같다면 사이에 값 없음
			if (ii == jj)
				printf("maybe\n");
			else {
				ans = getAns(1, 1, n, ii, jj - 1, arr[jj].second);
				if (ans.first) // X강수량 보다 모두 작을 때
					printf("maybe\n");
				else printf("false\n");
			}
		}
		else { //  둘 다 있을 때
			if (ii + 1 == jj) { // 찾은 값 연속하다면
				if (arr[ii].second >= arr[jj].second) { // Y가 X이상
					// 년도가 연속하면 true
					if (arr[ii].first + 1 == arr[jj].first) printf("true\n");
					else printf("maybe\n");
				}
				else {
					printf("false\n");
				}
			}
			else {
				ans = getAns(1, 1, n, ii + 1, jj - 1, arr[jj].second);
				// 사이의 값들이 X강수량 미만이고, Y가 X이상
				if (ans.first && arr[ii].second >= arr[jj].second) {
					// 년도가 연속하면
					if (arr[ii].first + 1 == arr[ii + 1].first
						&&arr[jj - 1].first + 1 == arr[jj].first && ans.second)
						printf("true\n");
					else printf("maybe\n");
				}
				else printf("false\n");
			}
		}
	}

	return 0;
}