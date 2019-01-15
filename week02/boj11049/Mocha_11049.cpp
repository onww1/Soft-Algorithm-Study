/*
 *  BOJ 11049. 행렬 곱셈 순서
 * 
 *  DP[i][j] : i번째 행렬에서 j번째 행렬까지 곱했을 때 비용의 최솟값
 *  DP[i][j] = min {k = i ~ j-1} (DP[i][k] + DP[k+1][j] + p[i-1] * p[k] * p[j])
 * 
 *  DP 항의 정의와 점화식은 위와 같습니다.
 *  곱셈을 하는 행렬의 갯수를 점차 확장시켜나가면서 어떤 순서로 곱했을 때 최소가 되는지 구하는 것입니다.
 *  그렇게 해서 최종적으로 DP[1][n]에는 모든 행렬을 곱했을 때 비용의 최솟값이 저장될 것이고,
 *  이를 출력하면 되는 문제입니다.
 * 
 *  위의 점화식에서 p는 행렬의 행과 열의 수에 대한 정보입니다.
 *  p[i]는 (i+1)번째 행렬의 행의 수이자 i번째 행렬의 열의 수입니다.
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#define INF 0x7f7f7f7f
using namespace std;

int p[505], dp[505][505];
int main(int argc, char *argv[]) {
	int n, r, c, i, j, k;
	scanf("%d", &n);
	memset(dp, 0x7f, sizeof(dp)); // 최솟값을 구하는 문제이므로 DP를 큰 값으로!
	for (i = 1; i <= n; ++i) {
		scanf("%d %d", &r, &c);
		if (i == 1) p[i-1] = r;
		p[i] = c;
	}
	for (i = 1; i <= n; ++i) dp[i][i] = 0;  // 한 행렬에 대해서는 곱의 비용이 0이죠.
	for (k = 1; k < n; ++k) {  // k는 곱하는 구간의 처음과 끝 행렬의 인덱스 차이입니다.
		for (i = 1; i <= n - k; ++i) {
			for (j = i; j < i + k; ++j) {
        // i ~ i + k에 대한 값을 구할 때, 어디서 끊을지를 모르니 모두 확인해서 최솟값을 저장하는 것입니다.
				dp[i][i + k] = min(dp[i][i + k], dp[i][j] + dp[j+1][i + k] + p[i - 1] * p[j] * p[i + k]);
			}
		}
	}
	return !printf("%d\n", dp[1][n]);
}