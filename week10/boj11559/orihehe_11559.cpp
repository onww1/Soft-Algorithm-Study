/*
BOJ 11559 - Puyo Puyo

시간복잡도 : O((12*6)^2)
공간복잡도 : O(12*6)

dfs에서 이어진 블록이 4개 이상인지 판별하고,
4개 이상일 때 rm에서 블록을 지워줍니다.
과정을 마친 뒤 dw에서 블록들을 땅으로 내려줍니다.
*/
#include <cstdio>
#include <cstring>
using namespace std;

/* 🐣🐥 */
char b[13][7], cur;
bool visited[13][7];
int cnt, rgo[4] = {1,-1,0,0}, cgo[4] = { 0,0,1,-1 };
void dfs(int r, int c) {
	visited[r][c] = true;
	cnt++;
	for (int i = 0; i < 4; i++) {
		int nr = r + rgo[i], nc = c + cgo[i];
		if (nr < 0 || nc < 0 || nr >= 12 || nc >= 6) continue;
		if (!visited[nr][nc] && b[r][c] == b[nr][nc]) dfs(nr, nc);
	}
}
void rm(int r, int c) {
	b[r][c] = '.';
	for (int i = 0; i < 4; i++) {
		int nr = r + rgo[i], nc = c + cgo[i];
		if (nr < 0 || nc < 0 || nr >= 12 || nc >= 6) continue;
		if (cur == b[nr][nc]) rm(nr, nc);
	}
}
void dw() {
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 6; j++) {
			int nr = i;
			while (nr < 12 && b[nr][j]=='.') {
				nr++;
			}
			// 현재 칸이 비어있다면 가장 가까운 위의 블록으로 채웁니다.
			if (b[i][j] == '.') {
				b[i][j] = b[nr][j];
				b[nr][j] = '.';
			}
		}
	}
}
int main() {
	int ans = 0;
	for (int i = 11; i >=0; i--) {
		scanf("%s", b[i]);
	}
	for (int i = 0; i < 6; i++) b[12][i] = '.';
	while (true) {
		bool suc = false;
		memset(visited, false, sizeof(visited));
		for (int i = 11; i >= 0; i--) {
			for (int j = 0; j < 6; j++) {
				cnt = 0;
				// 블록이 있다면 개수 세주기
				if (!visited[i][j] && b[i][j]!='.') dfs(i, j);
				// 터뜨릴 수 있는 블록이라면 제거
				if (cnt >= 4) {
					cur = b[i][j];
					rm(i, j);
					suc = true;
				}
			}
		}
		if (!suc) break;
		ans++;
		dw();
	}
	printf("%d", ans);

	return 0;
}