/*
BOJ 1981 - 배열에서 이동

시간복잡도 : O(N^2*KlogK) ?    n^2-dfs 를 mid별로 k번, logk-이분탐색, k=200
공간복잡도 : O(N^2)

mid 값을 최댓값과 최솟값의 차이로 설정합니다.
배열의 각 수는 0<=x<=200 의 범위이므로 0~0+mid, 1~1+mid ... 의 범위 안에 있는 수들만 방문하여
1,1에서 n,n에 도착할 수 있는지 dfs로 검사해줍니다.
n,n에 도착 했다면 mid차이로 이동할 수 있으므로 r=mid-1로 다음 mid값을 줄여주고,
도착하지 못했다면 l=mid+1로 다음 mid값을 늘려줍니다.
*/
#include <cstdio>
#include <cstring>
using namespace std;

int rgo[4] = { 0,-1,0,1 };
int cgo[4] = { 1,0,-1,0 };
bool visited[101][101], suc;
int b[101][101];
int n, l, r, mid, ans, mx, mn;
void dfs(int r, int c) {
	// mn~mx범위를 벗어난다면 return
	if (b[r][c] > mx || b[r][c] < mn) { 
		return;
	}
	visited[r][c] = true;
	if (r == n - 1 && c == n - 1) { // 도착
		suc = true; return; // suc변수에 도착했음을 표시
	}
	for (int i = 0; i < 4; i++) {
		int nr = r + rgo[i], nc = c + cgo[i];
		// 이미 방문했거나, 범위 밖이라면
		if (visited[nr][nc] || nr >= n || nr < 0 || nc < 0 || nc >= n) continue;
		if (suc) return; // 도착했다면 return
		dfs(nr, nc);
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			scanf("%d", &b[i][j]);
	}
	l = 0; r = 200;
	while (l <= r) {
		mid = (l + r) / 2;
		suc = false;
		// i~i+mid 사이의 수들만 방문하여 도착할 수 있는지
		for (int i = 0; i + mid <= 200; i++) {
			memset(visited, false, sizeof(visited));
			mx = i + mid; mn = i;
			dfs(0, 0);
			if (suc) break; // 도착했다면 더 볼 필요 없음
		}
		if (suc) {
			r = mid - 1;
			ans = mid;
		}
		else {
			l = mid + 1;
		}
	}
	printf("%d", ans);

	return 0;
}