/*
BOJ 11049 - 행렬 곱셈 순서

연속한 행렬끼리만 곱셈연산이 가능하고, 연산 순서에 따라 연산 수가 달라집니다.
따라서 k 범위의 구간을 반으로 나누어 왼쪽구간을 연산한 최솟값과, 
오른쪽 구간을 연산한 최솟값으로 두 구간을 연산 했을 때의 최솟값을 구했습니다.
dp[i][i+k] 에 i~i+k 범위에서의 연산의 최솟값이 들어가게 됩니다.
*/
#include <cstdio>
#include <algorithm>
#define P pair<int,int>
#define INF 2147483647
using namespace std;

int dp[502][502];
P arr[501];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d %d", &arr[i].first, &arr[i].second);
	}
	for (int k = 1; k <= n; k++) {	// 나눠서 볼 범위 크기
		for (int i = 1; i <= n - k; i++) {  // 범위의 시작 점
			dp[i][i + k] = INF;  // i를 시작점으로 하는 k범위에 최솟값을 저장할 것
			for (int j = i; j < i + k; j++) { // i~i+k 에서 j를 기준으로 두 범위로 나눠서 본다.
				dp[i][i + k] = min(dp[i][i + k],
					dp[i][j] + dp[j + 1][i + k] + arr[i].first*arr[i + k].second*arr[j].second);
			}
		}
	}
	printf("%d", dp[1][n]);

	return 0;
}