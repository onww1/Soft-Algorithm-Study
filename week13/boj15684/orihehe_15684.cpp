/*
BOJ 15684 - 사다리 조작

시간복잡도 : O(H*N C 3)
공간복잡도 : O(HN)

tkekfl배열에 가로선이 있을 시 가야하는 세로선 숫자를 저장해둡니다.
그 후 놓을 수 있는 가로선 위치를 벡터에 모두 저장해두고 mx개 선택했을 때의 모든 경우에서
그 사다리로 i번째 세로선이 i에 도착할 수 있는지 검사해줍니다.
*/
#include <cstdio>
#include <vector>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
int tkekfl[31][11], mx, ans = -1, sz;
vector<pii> vec;
int n, m, h, a, b;
bool ss;
bool suc() {
	int r, c;
	for (int i = 1; i <= n; i++) {
		r = 1, c = i;
		while (r <= h) {
			if(tkekfl[r][c]!=0)
				c = tkekfl[r][c];
			r++;
		}
		if (c != i) return false;
	}
	return true;
}
void dfs(int cur, int cnt) {
	if (mx == cnt) {
		if (suc()) ss = true;
		return;
	}
	if (cur == sz) return;
	// 가로선을 놓을 수 있을 경우
	if (tkekfl[vec[cur].first][vec[cur].second] == 0 && tkekfl[vec[cur].first][vec[cur].second + 1] == 0) {
		tkekfl[vec[cur].first][vec[cur].second] = vec[cur].second + 1;
		tkekfl[vec[cur].first][vec[cur].second + 1] = vec[cur].second;
		dfs(cur + 1, cnt + 1);
		tkekfl[vec[cur].first][vec[cur].second] = 0;
		tkekfl[vec[cur].first][vec[cur].second + 1] = 0;
		dfs(cur + 1, cnt);
	}
	else { // 불가
		dfs(cur + 1, cnt);
	}
}
int main() {
	scanf("%d %d %d", &n, &m, &h);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		tkekfl[a][b] = b + 1;
		tkekfl[a][b + 1] = b;
	}
	for (int i = 1; i <= h; i++) {
		for (int j = 1; j < n; j++) {
			// 놓을 수 있는 위치 모두 저장
			if (tkekfl[i][j] == 0 && tkekfl[i][j+1] == 0) {
				vec.push_back({ i,j });
			}
		}
	}
	sz = vec.size();
	for (int i = 0; i <= 3; i++) {
		mx = i;
		dfs(0, 0);
		if (ss) return !printf("%d", i);
	}
	printf("-1");

	return 0;
}