/*
BOJ 2140 - 지뢰찾기

시간복잡도 : O(N^2)
공간복잡도 : O(N^2)

지뢰를 놓을 위치의 주변 숫자를 모두 탐색합니다.
주변 숫자의 최댓값이 0보다 크고, 최솟값이 0보다 크다면 그 자리에 지뢰를 놓아주고,
숫자들 값을 1씩 빼줍니다.
*/
#include <cstdio>
#include <algorithm>
using namespace std;

/* 🐣🐥 */
char b[101][101];
int rgo[8] = { -1,-1,-1,0,0,1,1,1 };
int cgo[8] = { -1,0,1,-1,1,-1,0,1 };
int main() {
	int n, cnt = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", b[i]);
	}
	if (n <= 2) return !printf("0");
	for (int i = 1; i < n - 1; i++) {
		for (int j = 1; j < n - 1; j++) {
			int mx = 0, mn=4;
			for (int k = 0; k < 8; k++) {
				int nr = i + rgo[k], nc = j + cgo[k];
				if (b[nr][nc] == '#') continue;
				mx = max(mx, b[nr][nc] - '0');
				mn = min(mn, b[nr][nc] - '0');
			}
			if (mx > 0 && mn > 0) {
				cnt++;
				for (int k = 0; k < 8; k++) {
					int nr = i + rgo[k], nc = j + cgo[k];
					if (b[nr][nc] == '#') continue;
					b[nr][nc]--;
				}
			}
		}
	}
	if (n > 3) {
		cnt += (n - 4)*(n - 4);
	}
	printf("%d", cnt);

	return 0;
}