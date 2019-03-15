/*
BOJ 8068 - Water

시간복잡도 : O(NMH)
공간복잡도 : O(NMH)

vec에 높이별로 좌표를 모두 넣어줬습니다.
그 후 높이별로 벡터의 요소를 봐주면서 dfs를 돌려 같은 높이를 찾고, 주변 높이중 가장 낮은 값을 구해왔습니다.
또한 원소가 필드 가장자리에 있다면 물이 고일 수 없으니 가장자리에 있는지 또한 체크했습니다.

주변 높이가 현재 높이보다 크면서, 현재가 가장자리가 아니라면 현재 원소들에 개수*주변높이 만큼 물이 고이고,
주변 높이만큼 현재 원소들 높이를 올려줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
int b[101][101];
int rgo[4] = { 1,0,-1,0 }, cgo[4] = { 0,-1,0,1 };
bool visited[101][101], side;
int n, m, mh, bc;
vector<pii> vec[10001];
void dfs(int r, int c, int h) {
	visited[r][c] = true;
	bc++;
	for (int i = 0; i < 4; i++) {
		int nr = r + rgo[i], nc = c + cgo[i];
		// 현재 가장자리라면 side로 체크
		if (nr < 0 || nc < 0 || nr >= n || nc >= m) {
			side = true;
			continue;
		}
		if (visited[nr][nc]) continue;
		if (b[nr][nc] == h) dfs(nr, nc, h);
		else mh = min(b[nr][nc], mh); // mh에 주변의 가장 낮은 높이 저장
	}
}
void up(int r, int c, int h) {
	b[r][c] = mh; // mh로 올려주고
	vec[mh].push_back({ r,c }); // mh에 좌표 추가
	for (int i = 0; i < 4; i++) {
		int nr = r + rgo[i], nc = c + cgo[i];
		if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
		if (b[nr][nc] == h) up(nr, nc, h);
	}
}
int main() {
	int ans = 0;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &b[i][j]);
			vec[b[i][j]].push_back({ i,j });
		}
	}
	for (int i = 1; i <= 10000; i++) {
		memset(visited, false, sizeof(visited));
		for (pii v : vec[i]) {
			if (!visited[v.first][v.second]) {
				mh = 10001;
				side = false;
				bc = 0;
				dfs(v.first, v.second, i);
				// 가장자리가 아니고, 고일 수 있다면
				if (!side && mh > i) {
					ans += bc * (mh-i);
					up(v.first, v.second, i);
				}
			}
		}
	}
	printf("%d", ans);

	return 0;
}