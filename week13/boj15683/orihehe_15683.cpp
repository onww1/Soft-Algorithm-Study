/*
BOJ 15683 - 감시

시간복잡도 : O(4^K*N)  K = cctv 개수
공간복잡도 : O(N^N)

먼저 cctv 종류별로 감시하는 방법을 저장해둡니다.
또한 각 cctv의 위치를 vec에 저장해둡니다.
이제 모든 cctv의 감시 방향을 모두 구해준뒤, 그 방향을 감시 체크 해줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
// 북 동 남 서
int rgo[4] = { -1,0,1,0 }, cgo[4] = { 0,1,0,-1 };
int arr[10][10], tmp[10][10], cc[6][4];
int n, m, sum, sz, dir[10], ans = 100, cnt;
vector<pii> vec;
// cctv가 가리키는 방향 체크
void draw(int dir, int r, int c) {
	while (true) {
		r += rgo[dir], c += cgo[dir];
		if (r < 0 || c < 0 || r >= n || c >= m || arr[r][c]==6) break;
		if (tmp[r][c] == 0) cnt++;
		tmp[r][c] = -1;
	}
}
void dfs(int cur) {
	if (cur == sz) {
		memcpy(tmp, arr, sizeof(tmp));
		cnt = 0; // cctv가 감시하는 구역 개수
		for (int i = 0; i < sz; i++) {
			pii v = vec[i];
			int w = arr[v.first][v.second];
			for (int j = 0; j < 4; j++) {
				if (cc[w][j] == -1) break;
				draw((cc[w][j] + dir[i])%4, v.first, v.second);
			}
		}
		ans = min(ans, sum - cnt);
		return;
	}
	// cctv 방향 정해주기
	for (int i = 0; i < 4; i++) {
		dir[cur] = i;
		dfs(cur + 1);
	}
}
int main() {
	memset(cc, -1, sizeof(cc));
	// cctv 종류별 방향 전처리
	cc[1][0] = 0;
	cc[2][0] = 0, cc[2][1] = 2;
	cc[3][0] = 0, cc[3][1] = 1;
	cc[4][0] = 0, cc[4][1] = 1, cc[4][2] = 2;
	cc[5][0] = 0, cc[5][1] = 1, cc[5][2] = 2, cc[5][3] = 3;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &arr[i][j]);
			if (arr[i][j] == 0) sum++;
			else if (arr[i][j] <= 5) vec.push_back({ i,j }); // cctv좌표 넣어둠
		}
	}
	sz = vec.size(); // cctv개수
	dfs(0);
	printf("%d", ans);

	return 0;
}