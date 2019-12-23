/*
BOJ 14889 - 스타트와 링크

시간복잡도 : O(2^(n/2))
공간복잡도 : O(N^2)

한쪽 팀원을 n/2명 선택하는 경우를 모두 탐색해줍니다.
그리고나서 그 때마다 점수를 계산하여 최솟값을 구합니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

/* 🐣🐥 */
int b[21][21], n, fr[11], ba[11], fp, bp, fs, bs, mn=98754321;
bool num[21];
void dfs(int cur, int cnt) {
	if (cnt == n / 2) {
		fp = bp = fs = bs = 0;
		for (int i = 0; i < n; i++) {
			if (num[i]) fr[fp++] = i;
			else ba[bp++] = i;
		}
		for (int i = 0; i < fp; i++) {
			for (int j = 0; j < fp; j++) {
				fs += b[fr[i]][fr[j]];
			}
		}
		for (int i = 0; i < bp; i++) {
			for (int j = 0; j < bp; j++) {
				bs += b[ba[i]][ba[j]];
			}
		}
		mn = min(mn, abs(fs - bs));

		return;
	}
	if (cur == n) return;
	num[cur] = true;
	dfs(cur + 1, cnt + 1);
	num[cur] = false;
	dfs(cur + 1, cnt);
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &b[i][j]);
		}
	}
	dfs(0, 0);
	printf("%d", mn);

	return 0;
}