/*
BOJ 1347 - 미로 만들기

시간복잡도 : O(len*len)
공간복잡도 : O(100*100)

홍준이가 적은 내용에 따라 현재 위치에서 수행하면 됩니다.
미로를 그리기 위해 내용의 최대 길이 50의 두배로 그릴 크기를 잡고
50, 50 좌표에서 시작하여 그려주면 범위를 벗어나지 않습니다.
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

/* 🐣🐥 */
char b[101][101];
// 남 서 북 동
int rgo[4] = { 1,0,-1,0 }, cgo[4] = { 0,-1,0,1 };
int mxr, mnr, mxc, mnc, r, c, dir;
int main() {
	int n, len;
	char st[51];
	scanf("%d", &n);
	scanf("%s", st);
	len = strlen(st);
	mxr = mnr = mxc = mnc = r = c = 50; dir = 0;
	b[r][c] = '.';
	for (int i = 0; i < len; i++) {
		// 오른쪽 회전
		if (st[i] == 'R') {
			dir = (dir + 1) % 4;
		}
		// 왼쪽 회전
		else if (st[i] == 'L') {
			dir = (dir + 3) % 4;
		}
		// 현재 방향으로 전진
		else if (st[i] == 'F') {
			r += rgo[dir], c += cgo[dir];
			b[r][c] = '.';
			mxr = max(mxr, r);
			mxc = max(mxc, c);
			mnr = min(mnr, r);
			mnc = min(mnc, c);
		}
	}
	for (int i = mnr; i <= mxr; i++) {
		for (int j = mnc; j <= mxc; j++) {
			if (b[i][j] == '.') printf(".");
			else printf("#");
		}
		printf("\n");
	}

	return 0;
}