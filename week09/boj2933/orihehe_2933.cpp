/*
BOJ 2933 - 미네랄

시간복잡도 : O(NMK + Klog(NM))
공간복잡도 : O(NM)

막대기를 던져 미네랄을 파괴한 후 그 상하좌우를 봐줍니다.
상하좌우에 미네랄이 있다면 dfs로 클러스터 탐색, 
만약 그 클러스터의 최고높이가 0이라면 떨어지는 클러스터가 아닙니다.

dfs과정에서 모든 좌표를 vec에 넣어줍니다.
그 좌표값들을 이용하여 멈춰야할 자리까지의 최솟값을 구해줍니다.
구해준 뒤 좌표값들을 이동시켜주면 됩니다. 이때 r을 정렬하여 높이가 작은 것부터 옮겨줍니다.

상하좌우를 보며 visited를 계속 초기화 시키고, vec를 비워줘야해서 비효율적입니다..
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#define pii pair<int,int>
#define MAX 2000000000
using namespace std;

/* 🐣🐥 */
char b[101][101];
int mnr;
bool visited[101][101];
int rgo[4] = { 1,-1,0,0 };
int cgo[4] = { 0,0,1,-1 };
int n, m, k, h, dw;
vector<pii> vec;
void dfs(int r,int c) {
	vec.push_back({ r,c });
	visited[r][c] = true;
	mnr = min(r, mnr); // 클러스터 가장 아래 좌표, 0이 아니라면 떨어져야함
	for (int i = 0; i < 4; i++) {
		int nr = r + rgo[i], nc = c + cgo[i];
		if (nr < 0 || nc < 0 || nr >= n || nc >= m || visited[nr][nc]) continue;
		if (b[nr][nc] == 'x')
			dfs(nr, nc);
	}
}
int main() {
	scanf("%d %d", &n, &m);
	for (int i = n-1; i >=0; i--) {
		scanf("%s", b[i]);
	}
	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		scanf("%d", &h);
		h--;
		mnr = dw = MAX;
		memset(visited, false, sizeof(visited));
		vec.clear();
		// 창영과 상근의 차례를 구분
		int j = i % 2 ? m - 1 : 0 , d = i % 2 ? -1 : 1;
		while (j >= 0 && j < m) {
			// 파괴할 미네랄 만났다!
			if (b[h][j] == 'x') {
				b[h][j] = '.';
				for (int u = 0; u < 4; u++) {
					int nr = h + rgo[u], nc = j + cgo[u];
					if (nr < 0 || nc < 0 || nr >= n || nc >= m || b[nr][nc] == '.') continue;
					dfs(nr, nc);
					if (mnr > 0) break;
					memset(visited, false, sizeof(visited));
					mnr = dw = MAX;
					vec.clear();
				}
				break;
			}
			j += d;
		}
		if (mnr != 0 && mnr!=MAX) { // 떨어질게 있으면 
			sort(vec.begin(), vec.end()); // r좌표순 정렬
			for (pii v : vec) {
				int tr = v.first - 1 , tt = 0;
				// 현재위치가 비어있거나, 미네랄이지만 나와 같은 클러스터 소속이라면
				// 내려가야 합니다.
				while (tr >= 0 && (b[tr][v.second] == '.' 
					|| (b[tr][v.second]=='x' && visited[tr][v.second]))) {
					tt++;
					tr--;
				}
				dw = min(dw, tt); // dw만큼 떨어져야함.
			}
			for (pii v : vec) {
				b[v.first][v.second] = '.';
				b[v.first - dw][v.second] = 'x';
			}
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < m; j++) printf("%c", b[i][j]);
		printf("\n");
	}

	return 0;
}