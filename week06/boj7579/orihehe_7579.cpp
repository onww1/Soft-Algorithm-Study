/*
BOJ 7579 - 앱

시간복잡도 : O(10000*N)
공간복잡도 : O(N)

처음에는 필요한 메모리에 대해 비용을 계산하는 생각밖에 떠오르지 않았습니다.
그 과정을 노트에 써보다가 비용이 같은 값은 그냥 메모리가 큰걸 골라도 되니,
비용에 대해 dp테이블을 정의하는게 좋겠다는 생각이 들었습니다.

dp[현재 비용의 최대 메모리]로 정의하고, 
현재 앱의 비용에 대해 최대비용인 10000부터 감소시켜주며 dp테이블을 갱신해줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
int dp[10001];
pii mmr[100];
int main() {
	int n, m, x, ap = 0;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		mmr[i].second = x;
	}
	memset(dp, -1, sizeof(dp));
	dp[0] = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		mmr[i].first = x;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 10000; j >= mmr[i].first; j--) {
			if (dp[j - mmr[i].first] != -1) {
				dp[j] = max(dp[j], dp[j - mmr[i].first] + mmr[i].second);
			}
		}
	}
	// 적은비용부터 보면서 m을 만족시키면 출력
	for (int i = 0; i <= 10000; i++) {
		if (dp[i] >= m) return !printf("%d", i);
	}

	return 0;
}