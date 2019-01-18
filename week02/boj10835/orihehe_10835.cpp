/*
BOJ 10835 - 카드게임

dp[aa번째 왼쪽 카드][bb번째 오른쪽 카드] 로 배열을 설정합니다.
왼쪽 카드를 버린 경우 aa를 늘려주고, 오른쪽 카드를 버린 경우 bb를 늘려줍니다.

기본적으로 왼쪽 카드만 버릴 때, 왼쪽 오른쪽 카드를 버릴 때를 봐줍니다.
aa번째 왼쪽 카드보다 bb번째 오른쪽 카드가 작다면 오른쪽 카드를 버리고 점수를 추가해 주는 경우를 봐줍니다.
세 경우를 봤을 때의 최댓값을 dp배열에 채워주고, 값이 이미 있다면 그 값을 리턴해줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int a[2000], b[2000], dp[2000][2000], n;
int go(int aa,int bb) {
	if (aa == n || bb == n) return 0; // 두 카드 더미 중 하나라도 동난다면 0 리턴
	if (dp[aa][bb] != -1) { // 이미 값이 있다면
		return dp[aa][bb];
	}
	int maxV = 0;
	maxV = max(maxV, go(aa + 1, bb)); // 왼쪽 카드를 버렸을 때
	maxV = max(maxV, go(aa + 1, bb + 1)); // 왼쪽, 오른쪽 카드를 버렸을 때 
	if (a[aa] > b[bb]) { // 오른쪽이 왼쪽보다 작을 경우
		maxV = max(maxV, go(aa, bb + 1) + b[bb]); // 오른쪽 카드를 버리며 점수 획득
	}
	// 위의 경우 중 최댓값 저장
	return dp[aa][bb] = maxV;
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &b[i]);
	}
	memset(dp, -1, sizeof(dp));

	printf("%d", go(0, 0));

	return 0;
}