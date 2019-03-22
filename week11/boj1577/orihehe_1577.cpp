/*
BOJ 1577 - 도로의 개수

시간복잡도 : O(MN)
공간복잡도 : O(NM)

현재 정점에서 왼쪽도로와 윗쪽 도로가 공사중인지 아닌지를 vec에 체크해줍니다.
그리고나서 왼쪽, 윗쪽 도로에 대해 공사중이 아닐 때 그곳까지의 경로를 더해줍니다.
도로정보는 칸마다 번호를 매겨 저장해주었습니다.
*/
#include <cstdio>
#include <algorithm>
#define ll long long
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
ll dp[101][101];
bool vec[10201][2]; // 왼쪽 윗쪽
int main() {
	int n, m, k;
	pii a, b;
	scanf("%d %d %d", &n, &m, &k);
	while (k--) {
		scanf("%d %d %d %d", &a.first, &a.second, &b.first, &b.second);
		if (a.first > b.first || a.second > b.second) swap(a, b);
		if (a.first < b.first) { // 왼쪽에서 온거
			vec[b.second*(n+1) + b.first][0] = true;
		}
		else {
			vec[b.second*(n + 1) + b.first][1] = true;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (vec[i][0]) break;
		dp[i][0] = 1;
	}
	for (int i = 1; i <= m; i++) {
		if (vec[i*(n + 1)][1]) break;
		dp[0][i] = 1;
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (!vec[j*(n + 1) + i][0]) dp[i][j] += dp[i-1][j];
			if (!vec[j*(n + 1) + i][1]) dp[i][j] += dp[i][j-1];
		}
	}
	printf("%lld", dp[n][m]);

	return 0;
}