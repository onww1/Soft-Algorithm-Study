/*
BOJ 2624 - 동전 바꿔주기

시간복잡도 : O(TKN)
공간복잡도 : O(T)

종류가 같은 동전은 그 동전을 1,2,3,...개 썼을 경우의 가치별로 나올 수 있는 경우를 구해준 뒤
dp배열에 나온 가짓수를 더해줍니다.
*/
#include <cstdio>
#include <vector>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
vector<pii> coin;
int dp[10001], tmp[10001];
int main() {
	int k, t, a, b;
	scanf("%d %d", &t, &k);
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &a, &b);
		coin.push_back({ a,b });
	}
	dp[0] = 1;
	for (int c = 0; c < k; c++) {
		// 동전의 개수만큼
		for (int i = 1; i <= coin[c].second; i++) {
			for (int j = i * coin[c].first; j <= t; j++) {
				tmp[j] += dp[j - i * coin[c].first];
			}
		}
		for (int i = 0; i <= t; i++) {
			dp[i] += tmp[i];
			tmp[i] = 0;
		}
	}

	printf("%d", dp[t]);

	return 0;
}