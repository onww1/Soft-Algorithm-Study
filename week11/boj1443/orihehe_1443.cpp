/*
BOJ 1443 - 망가진 계산기

시간복잡도 : O(...)
공간복잡도 : O(1)

시간복잡도 계산을 못하겠습니다 ( ._.)
곱하는 순서는 상관없으니 작은것부터 곱해보는 식으로 탐색
자릿수 제한에서도 경우가 많이 걸러지는거 같습니다.
*/
#include <cstdio>
#include <algorithm>
using namespace std;

/* 🐣🐥 */
int mv, mx=1;
int d, p;
void dfs(int cur, int cnt, int val) {
	if (val >= mx) return; // 자릿수를 넘어가면
	if (cnt == p) { // 횟수
		mv = max(mv, val);
		return;
	}
	for (int i = cur; i <= 9; i++) {
		dfs(i, cnt + 1, val*i);
	}
}
int main() {
	scanf("%d %d", &d, &p);
	for (int i = 0; i < d; i++) mx *= 10;
	dfs(2, 0, 1);
	if (mv == 0) printf("-1");
	else printf("%d", mv);

	return 0;
}