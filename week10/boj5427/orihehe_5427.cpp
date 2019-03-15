/*
BOJ 5427 - 불

시간복잡도 : O(TWH)
공간복잡도 : O(WH)

bfs로 상근이의 이동 횟수가 늘어날 때마다 불을 퍼뜨려 주면 됩니다.
이제 불이 붙으려는 칸으로는 이동할 수 없으므로 불을 먼저 한번 퍼뜨려줬습니다.
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
char b[1001][1001], cur;
bool visited[1001][1001];
int rgo[4] = { 1,-1,0,0 }, cgo[4] = { 0,0,1,-1 };
queue<pii> fire, q;
int main() {
	int t, w, h, s, cnt;
	scanf("%d", &t);
	while (t--) {
		bool suc = false;
		cnt = 0;
		memset(visited, false, sizeof(visited));
		scanf("%d %d", &w, &h);
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				scanf(" %c", &b[i][j]);
				if (b[i][j] == '@') {
					q.push({ i,j });
					visited[i][j] = true;
					b[i][j] = '.';
				}
				// 불이 난 위치를 모두 넣어줍니다.
				else if (b[i][j] == '*') fire.push({ i,j });
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
					b[nr][nc] = '*';
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
							b[nr][nc] = '*';
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
		// 큐 비워주기
		while (!q.empty()) q.pop();
		while (!fire.empty()) fire.pop();
	}

	return 0;
}