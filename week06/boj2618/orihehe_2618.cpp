/*
BOJ 2618 - 경찰차

시간복잡도 : O(W^2)
공간복잡도 : O(W^2)

dp[경찰차1의 마지막사건][경찰차2의 마지막사건]으로 설정합니다.
마지막에 맡은 사건으로 설정하면 각 경찰차의 위치를 알 수 있고, 모든 경우를 표현할 수 있습니다.

각 사건을 순서대로 처리하고 넘어가므로 i번째 사건을 볼 때 
dp[i-1][x], dp[x][i-1] + 이동거리의 최솟값을 넣어줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
int dp[1001][1001]; // 경찰1 마지막 사건, 경찰2 마지막 사건
pii arr[1001], y;
pii p[1001][1001];
void pans(int cur, int r, int c) { // 경로 추적
	if (cur <= 0) return;
	pans(cur - 1, p[r][c].first, p[r][c].second);
	if (cur == r) printf("1\n");
	else printf("2\n");
}
int main() {
	int n, w, mV = 987654321, tmp, r, c;
	scanf("%d %d", &n, &w);
	for (int i = 0; i <= 1000; i++)
		fill(dp[i], dp[i] + 1001, 987564321);
	dp[0][0] = 0;
	for (int i = 1; i <= w; i++) {
		scanf("%d %d", &arr[i].first, &arr[i].second);
		for (int j = 0; j < i; j++) {
			// dp[i-1][j], 경찰차 1이 이전사건 맡음
			if (i - 1 == 0) y = { 1,1 };
			else y = arr[i - 1];
			// 경찰차 1
			tmp = dp[i - 1][j] + abs(arr[i].first - y.first)
				+ abs(arr[i].second - y.second);
			if (dp[i][j] > tmp) {
				dp[i][j] = tmp;
				// p[i][j]는 i-1,j에서 왔음을 표시
				p[i][j] = { i - 1,j };
			}
			if (j == 0) y = { n,n };
			else y = arr[j];
			// 경찰차 2
			tmp = dp[i - 1][j] + abs(arr[i].first - y.first)
				+ abs(arr[i].second - y.second);
			if (dp[i - 1][i] > tmp) {
				dp[i - 1][i] = tmp;
				p[i - 1][i] = { i - 1,j };
			}

			// dp[j][i-1], 경찰차 2가 이전사건 맡음
			if (i - 1 == 0) y = { n,n };
			else y = arr[i - 1];
			// 경찰차 2
			tmp = dp[j][i - 1]
				+ abs(arr[i].first - y.first) + abs(arr[i].second - y.second);
			if (dp[j][i] > tmp) {
				dp[j][i] = tmp;
				p[j][i] = { j, i - 1 };
			}
			if (j == 0) y = { 1,1 };
			else y = arr[j];
			// 경찰차 1
			tmp = dp[j][i - 1] + abs(arr[i].first - y.first)
				+ abs(arr[i].second - y.second);
			if (dp[i][i - 1] > tmp) {
				dp[i][i - 1] = tmp;
				p[i][i - 1] = { j,i - 1 };
			}

		}
	}
	// w사건까지의 최솟값을 찾음
	for (int i = 0; i < w; i++) {
		if (mV > dp[w][i]) {
			mV = dp[w][i];
			r = w, c = i;
		}
		if (mV > dp[i][w]) {
			mV = dp[i][w];
			r = i, c = w;
		}
	}
	printf("%d\n", mV);
	pans(w, r, c);

	return 0;
}