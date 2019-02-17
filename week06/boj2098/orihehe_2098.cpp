/*
BOJ 2098 - 외판원 순회

시간복잡도 : O(N^3*2^N)
공간복잡도 : O(N^2*2^N)

dp[시작점][도착점][방문한 정점] 으로 설정했습니다.
main의 3중포문에서 k를 시작점, 돌아올 점으로 두고, k를 제외한 i, j를 시작점, 도착점으로 둡니다.
그 모든 i->j 경로에서의 최솟값이 k에서 시작했을 때의 최소비용이 됩니다.

저는 모든 k에 대해 해줘야하는줄 알았으나 하나의 k에서 구한 값이 답이 되게 됩니다.
k0 에서 구한 경로는 k0 에서 나가는 간선, 들어오는 간선이 있는데,
다른 k1 에서 최소비용을 다시 구할 때 이전 k0 의 나가는 간선, 들어오는 간선이 포함되기 때문입니다.

시간복잡도로만 보면 시간이 터지는데, go에서 항상 모든 정점을 보는 게 아닌 방문하지 않은 남은 정점들로만 가기 때문에
570ms로 AC를 받았습니다..
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#define MAX 16000001
using namespace std;

/* 🐣🐥 */
int b[16][16], n;
int dp[16][16][1 << 16], minV = MAX;
int go(int start, int end, int val) {
	int tmp = MAX;
	if (dp[start][end][val] != -1) return dp[start][end][val];
	// 마지막 도착점만 남았다면
	if (val + (1 << end) == (1 << n) - 1) {
		if (b[start][end] != 0) return dp[start][end][val + (1 << end)] = b[start][end];
		else return MAX;
	}
	for (int i = 0; i < n; i++) {
		// 도착점 제외, 방문하지 않은 도시로, 간선이 있을 경우
		if (i != end && (val | (1 << i)) != val && b[start][i] != 0) {
			tmp = min(tmp, go(i, end, val + (1 << i)) + b[start][i]);
		}
	}
	return dp[start][end][val] = tmp;
}
int main() {
	scanf("%d", &n);
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &b[i][j]);
		}
	}
	for (int k = 0; k < n; k++) {  // 시작, 돌아올 지점
		for (int i = 0; i < n; i++) {
			if (k == i || b[k][i] == 0) continue;
			for (int j = 0; j < n; j++) {
				if (k == j || j == i) continue;
				if (b[j][k] != 0)
					// k와 i는 방문했음을 표시
					minV = min(minV, go(i, j, (1 << k) + (1 << i)) + b[k][i] + b[j][k]);
			}
		}
	}
	if (n == 2) printf("%d", b[0][1] + b[1][0]);
	else printf("%d", minV);

	return 0;
}