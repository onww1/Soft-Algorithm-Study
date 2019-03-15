/*
BOJ 4179 - 불!

시간복잡도 : O(WH)
공간복잡도 : O(WH)

BOJ 5427 (불) 문제와 같은 방식으로 풀었습니다.
*/
#include <cstdio>
#include <algorithm>
#include <queue>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
char b[1001][1001], cur;
bool visited[1001][1001];
int rgo[4] = { 1,-1,0,0 }, cgo[4] = { 0,0,1,-1 };
queue<pii> fire, q;
int main() {
	int w, h, s, cnt = 0;
	bool suc = false;
	scanf("%d %d", &h, &w);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			scanf(" %c", &b[i][j]);
			if (b[i][j] == 'J') {
				q.push({ i,j });
				visited[i][j] = true;
				b[i][j] = '.';
			}
			// 불이 난 위치를 모두 넣어줍니다.
			else if (b[i][j] == 'F') fire.push({ i,j });
		}
	}
	int fs = fire.size();
	// 불을 한 번 퍼뜨려주고
	while (!fire.empty()) {
		if (fs == 0) break;
		pii fc = fire.front();
		fire.pop();
		for (int i = 0; i < 4; i++) {
			int nr = fc.first + rgo[i], nc = fc.second + cgo[i];
			if (nr < 0 || nc < 0 || nr >= h || nc >= w) continue;
			if (b[nr][nc] == '.') {
				b[nr][nc] = 'F';
				fire.push({ nr,nc });
			}
		}
		fs--;
	}
	s = 1;
	while (!q.empty()) {
		// 이동 횟수가 바뀔 때마다 불을 퍼뜨려줍니다.
		if (s == 0) {
			fs = fire.size();
			while (!fire.empty()) {
				if (fs == 0) break;
				pii fc = fire.front();
				fire.pop();
				for (int i = 0; i < 4; i++) {
					int nr = fc.first + rgo[i], nc = fc.second + cgo[i];
					if (nr < 0 || nc < 0 || nr >= h || nc >= w) continue;
					if (b[nr][nc] == '.') {
						b[nr][nc] = 'F';
						fire.push({ nr,nc });
					}
				}
				fs--;
			}
			s = q.size();
			cnt++;
		}
		pii cur = q.front();
		q.pop();
		// 사이드에 도착했다면
		if (cur.first == 0 || cur.first == h - 1
			|| cur.second == 0 || cur.second == w - 1) {
			suc = true;
			printf("%d\n", cnt + 1);
			break;
		}
		for (int i = 0; i < 4; i++) {
			int nr = cur.first + rgo[i], nc = cur.second + cgo[i];
			if (nr < 0 || nc < 0 || nr >= h || nc >= w) continue;
			if (b[nr][nc] == '.' && !visited[nr][nc]) {
				q.push({ nr,nc });
				visited[nr][nc] = true;
			}
		}
		s--;
	}
	if (!suc) printf("IMPOSSIBLE\n");

	return 0;
}