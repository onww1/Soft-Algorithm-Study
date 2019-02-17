/*
BOJ 11062 - 카드 게임

시간복잡도 : O(N^2)
공간복잡도 : O(N^2)

근우 명우 둘 다 최선의 전략으로 카드를 뽑는다.
따라서 근우가 l or r을 뽑고 명우의 선택 후 근우 턴이 다시 돌아왔을 때 뽑는 카드는
명우의 선택 후 남은 카드에서 뽑는 경우들 중 작은 값이 된다. 명우 또한 최선으로 뽑기 때문
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

/* 🐣🐥 */
int arr[1000], dp[1000][1000];
int go(int l, int r) {
	if (dp[l][r] != -1) return dp[l][r];
	if (l > r) return 0;
	dp[l][r] = arr[l] + min(go(l + 1, r - 1), go(l + 2, r));
	dp[l][r] = max(dp[l][r], arr[r] + min(go(l, r - 2), go(l + 1, r - 1)));
	return dp[l][r];
}
int main() {
	int t, n;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		memset(dp, -1, sizeof(dp));
		for (int i = 0; i<n; i++) {
			scanf("%d", &arr[i]);
		}
		printf("%d\n", go(0, n - 1));
	}

	return 0;
}