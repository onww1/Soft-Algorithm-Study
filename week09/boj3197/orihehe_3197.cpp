/*
BOJ 3197 - 백조의 호수

시간복잡도 : O(NM)
공간복잡도 : O(NM)

백조와 호수 부분을 모두 큐에 넣어두고, 주위의 빙판을 탐색해줍니다.
이 과정에서 유니온 파인드를 이용하여 같은 호수가 같은 부모를 가지도록하여
백조 X와 Y가 같은 집합일시 답을 출력해줬습니다.
백조가 처음부터 같은 집합일 경우는 따로 처리해줍니다.
*/
#include <cstdio>
#include <queue>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
char b[1501][1501];
bool visited[1501][1501];
pii p[1501][1501], X, Y;
int rgo[4] = { 0,0,-1,1 };
int cgo[4] = { -1,1,0,0 };
int n, m, s, cnt;
queue<pii> q;
pii getr(pii x) {
	if (x == p[x.first][x.second]) return x;
	return p[x.first][x.second] = getr(p[x.first][x.second]);
}
void merge(pii x, pii y) {
	x = getr(x);
	y = getr(y);
	if (x != y)
		p[x.first][x.second] = y;
}
void dfs(pii x) { // 처음 백조의 집합 구해준다.
	visited[x.first][x.second] = true;
	for (int i = 0; i < 4; i++) {
		int nr = x.first + rgo[i], nc = x.second + cgo[i];
		if (nr < 0 || nc < 0 || nr >= n || nc >= m || visited[nr][nc]) continue;
		if (b[nr][nc] != 'X') {
			merge(x, { nr,nc });
			dfs({ nr, nc });
		}
	}
}
int main() {
	X = { -1,-1 };
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", b[i]);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			p[i][j] = { i,j };
			if (b[i][j] == 'L') {
				if (X.first == -1) {
					X = { i,j };
				}
				else Y = { i,j };
			}
			if (b[i][j] != 'X') q.push({ i,j });
		}
	}
	dfs(X), dfs(Y);
	if (getr(X) == getr(Y)) return !printf("0");
	s = q.size();
	cnt = 1;
	while (!q.empty()) {
		if (s == 0) {
			s = q.size();
			cnt++;
		}
		pii cur = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nr = cur.first + rgo[i], nc = cur.second + cgo[i];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			merge(cur, { nr,nc });
			if (b[nr][nc] == 'X') {
				q.push({ nr,nc });
				b[nr][nc] = '.';
			}
			/*
			한 칸 다음것도 봐주는 이유는
			LXXL 일 경우 빙하를 녹인 후 한번 더 봐줘야 merge가 되어 
			원래 답보다 1크게 나오게됩니다.
			*/
			nr += rgo[i], nc += cgo[i];
			if (nr < 0 || nc < 0 || nr >= n || nc >= m) continue;
			if (b[nr][nc] == '.')
				merge(cur, { nr,nc });
		}
		if (getr(X) == getr(Y)) {
			return !printf("%d", cnt);
		}
		s--;
	}

	return 0;
}