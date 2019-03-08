/*
BOJ 2931 - 가스관

시간복잡도 : O(NM)
공간복잡도 : O(NM)

Z과 M에서 시작하여 위치와 방향정보를 저장해줍니다.
곡선 파이프 외엔 가던 방향으로 가줍니다.
M에 작은 방향을 준 뒤 Z와 M의 방향이 정반대라면 왼쪽 위 방향 정보로 파이프를 판별
그렇지 않다면 M방향으로 두칸 간 정보로 파이프를 판별했습니다.
*/
#include <cstdio>
#include <algorithm>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
char b[26][26];
int n, m, dM, dZ;
pii M, Z;
// 왼 위 오 아
int rgo[4] = { 0,-1,0,1 };
int cgo[4] = { -1,0,1,0 };
// [0]의 방향이라면 [1] 로, 아니라면 [2] 로
int turn[3][4] = { {0,3,2,2},{3,2,1,3},{2,1,0,0} };
void go(int &r, int &c, int &dir) {
	while (b[r+rgo[dir]][c+cgo[dir]] != '.') {
		r += rgo[dir];
		c += cgo[dir];
		// 방향전환
		if (b[r][c] >= '1' && b[r][c] <= '4') {
			if (dir == turn[0][b[r][c] - '1']) dir = turn[1][b[r][c] - '1'];
			else dir = turn[2][b[r][c] - '1'];
		}
	}
}
int main() {
	int r, c;
	char sh;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf(" %c", &b[i][j]);
			if (b[i][j] == 'M') M = { i,j };
			if (b[i][j] == 'Z') Z = { i,j };
		}
	}
	// M의 방향
	for (int i = 0; i < 4; i++) {
		int nr = M.first + rgo[i], nc = M.second + cgo[i];
		if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
		if (b[nr][nc] != '.' && b[nr][nc]!='Z') dM = i;
	}
	// Z의 방향
	for (int i = 0; i < 4; i++) {
		int nr = Z.first + rgo[i], nc = Z.second + cgo[i];
		if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
		if (b[nr][nc] != '.'&& b[nr][nc] != 'M') dZ = i;
	}
	go(M.first, M.second, dM);
	go(Z.first, Z.second, dZ);
	int nr, nc;
	if (dM > dZ) {
		swap(dZ, dM);
		swap(Z, M);
	}
	if (dM == (dZ + 2) % 4) { // 서로 반댓편
		nr = M.first - 1;
		nc = M.second - 1;
		r = M.first + rgo[dM], c = M.second + cgo[dM];
		if (dM == 0) { // 왼쪽
			if (nr < 0 || nc < 0 || b[nr][nc] == '-' || b[nr][nc] == '.' ||
				b[nr][nc] == '2' || b[nr][nc] == '3' || b[nr][nc] == 'M' || b[nr][nc] == 'Z') {
				sh = '-';
			}
			else sh = '+';
		}
		if (dM == 1) { // 북
			if (nr < 0 || nc < 0 || b[nr][nc] == '|' || b[nr][nc] == '.' ||
				b[nr][nc] == '3' || b[nr][nc] == '4' || b[nr][nc]=='M' || b[nr][nc]=='Z') {
				sh = '|';
			}
			else sh = '+';
		}
	}
	else {
		r = nr = M.first + rgo[dM] * 2;
		c = nc = M.second + cgo[dM] * 2;
		r -= rgo[dM];
		c -= cgo[dM];
		if (dM == 0 && dZ == 1) { // 1
			if ((nr >= 0 && nc >= 0 && nr < n && nc < m) && (b[nr][nc] == '-' || b[nr][nc] == '1' || b[nr][nc] == '2'))
				sh = '+';
			else sh = '1';
		}
		else if (dM == 0 && dZ == 3) { // 2
			if ((nr >= 0 && nc >= 0 && nr < n && nc < m) && (b[nr][nc] == '-' || b[nr][nc] == '1' || b[nr][nc] == '2'))
				sh = '+';
			else sh = '2';
		}
		else if (dM == 2 && dZ == 3) { // 3
			if ((nr >= 0 && nc >= 0 && nr < n && nc < m) && (b[nr][nc] == '-' || b[nr][nc] == '3' || b[nr][nc] == '4'))
				sh = '+';
			else sh = '3';
		}
		else if (dM == 1 && dZ == 2) { // 4
			if ((nr >= 0 && nc >= 0 && nr < n && nc < m) && (b[nr][nc] == '|' || b[nr][nc] == '1' || b[nr][nc] == '4'))
				sh = '+';
			else sh = '4';
		}
	}
	printf("%d %d %c", r+1, c+1, sh);

	return 0;
}