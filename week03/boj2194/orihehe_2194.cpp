/*
BOJ 2194 - 유닛 이동시키기

bfs 방식으로 현재 유닛의 왼쪽 위 좌표를 큐에 넣어 탐색해줬습니다.
상하좌우 네 방향에 대해 유닛을 이동시키고, 장애물이 없다면 이동가능하므로 큐에 좌표를 넣어줍니다.
또한 이미 방문한 곳은 다시 넣어도 최소 이동 횟수가 될 수 없으니 넣어주지 않습니다.

유닛이 이동했을 때 장애물이 있는지 여부는 igo함수에서 체크합니다.
유닛은 한 칸씩 이동하므로 유닛 전체를 체크하는 것보다는
테두리만 보는 것이 효율적일 것 같아 테두리만 체크해줬습니다.
*/
#include <cstdio>
#include <queue>
#define P pair<int,int>
using namespace std;

int bo[501][501]; // 장애물 -1, 방문 1
int rgo[4] = { -1,0,1,0 }; // 북 동 남 서
int cgo[4] = { 0,1,0,-1 };
int n, m, a, b, k, r, c, cnt = 0, s = 1;

bool igo(int rr, int cc) {  // 유닛의 테두리 검사
	// 직사각형 세로 변 검사
	for (int i = rr; i < rr + a; i++) {
		if (bo[i][cc] == -1) return false;
		if (bo[i][cc + b-1] == -1) return false;
	}
	// 직사각형 가로 변 검사
	for (int i = cc; i < cc + b; i++) {
		if (bo[rr][i] == -1) return false;
		if (bo[rr+a-1][i] == -1) return false;
	}
	return true;
}
int main() {
	queue<P> q;
	scanf("%d %d %d %d %d", &n, &m, &a, &b, &k);
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &r, &c);
		bo[r][c] = -1;
	}
	scanf("%d %d", &r, &c);
	q.push({ r,c });
	bo[r][c] = 1;
	scanf("%d %d", &r, &c);

	bool suc = false;
	while (!q.empty()) {
		if (s == 0) {
			cnt++;
			s = q.size();
		}
		int cr = q.front().first, cc = q.front().second;
		q.pop();
		if (cr==r && cc==c) {  // 도착
			suc = true; break;
		}
		for (int i = 0; i < 4; i++) {
			int nr = cr + rgo[i], nc = cc + cgo[i];
			if (nr <= 0 || nc <= 0 || nr + a - 1 > n || nc + b - 1 > m) 
				continue;
			// 방문하지 않았고, 장애물이 없다면
			if (bo[nr][nc]!=1 && igo(nr, nc)) {
				q.push({ nr, nc });
				bo[nr][nc] = 1; // 방문 했음을 표시
			}
		}
		s--;
	}
	if (suc) printf("%d", cnt);
	else printf("-1");

	return 0;
}