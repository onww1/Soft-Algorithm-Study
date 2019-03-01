/*
BOJ 11658 - 구간 합 구하기 3

시간복잡도 : O((N^2+M)*(logN)^2)
공간복잡도 : O((2^logN)^2)

2D 세그 문제입니다. 처음 짜봤는데 좀 헷갈렸습니다..
2차원으로 트리를 만들어서, 행과 열에서 따로 1차원에서의 세그를 짜듯이 풀어줬습니다.
각 행 별로 구간, 열 별로 구간이 있고, 행 기준으로 구간이 포함될 때 열의 구간을 또 봐줬습니다.

시간복잡도가 M(logN)^2 인줄 알고 냈는데 TLE를 받고 어느 부분에서 그런줄 몰랐는데,
일단 첫 입력에서 N^2번 업데이트를 해줘서 N^2(logN)^2..
그리고 lup과 lhap, rup과 rhap에서 매개변수가 원래 10개 있었는데, 
사용하지 않는 것들을 없애주니 아슬아슬하게 AC를 받아 신기했습니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

/* 🐣🐥 */
int **tree, arr[1025][1025];
int n, m, h, x, a, b, c, d;
void rup(int fi, int si, int ss, int se, int s, int val) { // 열 업데이트
	if (s<ss || s>se) return;
	tree[fi][si] += val; // 값 변경
	if (ss == se) return;
	rup(fi, si * 2, ss, (ss + se) / 2, s, val);
	rup(fi, si * 2 + 1, (ss + se) / 2 + 1, se, s, val);
}
void lup(int fi, int fs, int fe, int f, int val) { // 행 업데이트
	if (f<fs || f>fe) return;
	// 행 범위 안에 있다면 열 업데이트로
	rup(fi, 1, 1, n, b, val);
	if (fs == fe) return;
	lup(fi * 2, fs, (fs + fe) / 2, f, val);
	lup(fi * 2 + 1, (fs + fe) / 2 + 1, fe, f, val);
}
int rhap(int fi, int si, int ss, int se, int sl, int sr) { // 열 합
	if (sr<ss || sl>se) return 0;
	if (sl <= ss && se <= sr) {
		// 열 또한 포함된다면
		return tree[fi][si];
	}
	return rhap(fi, si * 2, ss, (ss + se) / 2, sl, sr)
		+ rhap(fi, si * 2 + 1, (ss + se) / 2 + 1, se, sl, sr);
}
int lhap(int fi, int fs, int fe, int fl, int fr) { // 행 합
	if (fr<fs || fl>fe) return 0;
	// 현재 구간이 포함된다면
	if (fl <= fs && fe <= fr) {
		// 열 합으로
		return rhap(fi, 1, 1, n, b, d);
	}
	return lhap(fi * 2, fs, (fs + fe) / 2, fl, fr)
		+ lhap(fi * 2 + 1, (fs + fe) / 2 + 1, fe, fl, fr);
}
int main() {
	scanf("%d %d", &n, &m);
	h = ceil(log2(n)) + 1;
	tree = new int*[1 << h];
	for (int i = 0; i < (1 << h); i++) {
		tree[i] = new int[1 << h];
		fill(tree[i], tree[i] + (1 << h), 0);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &arr[i][j]);
			b = j;
			lup(1, 1, n, i, arr[i][j]);
		}
	}
	while (m--) {
		scanf("%d", &x);
		if (x == 0) {
			scanf("%d %d %d", &a, &b, &c);
			lup(1, 1, n, a, c-arr[a][b]);
			arr[a][b] = c;
		}
		else if (x == 1) {
			scanf("%d %d %d %d", &a, &b, &c, &d);
			printf("%d\n", lhap(1, 1, n, a, c));
		}
	}

	return 0;
}