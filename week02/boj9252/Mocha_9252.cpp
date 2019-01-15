/*
 *	BOJ 9252. LCS 2
 *
 *  전형적인 DP 문제죠.
 *  
 *  DP[i][j] : 첫 번째 string의 i번째 인덱스, 두 번째 string의 j번째 인덱스까지 
 *             비교하였을 때, LCS의 길이
 *  DP[i][j] = 1. DP[i][j] = DP[i-1][j-1] (if string1[i] == string2[j])
 *             2. DP[i][j] = max(DP[i-1][j], DP[i][j-1]) (if string1[i] != string2[j])
 * 
 *  점화식은 위와 같습니다. 먼저 한 번 훑으면서 위의 점화식으로 DP 테이블을 정리하고,
 *  거꾸로 마지막 항부터 시작해서 같은 문자를 가지는 부분에 대해서 결과 string에 추가해주고,
 *  같은 문자가 아니라면 현재 위치와 같은 DP값을 가지는 쪽으로 이동합니다.
 *  그렇게 끝까지 다 했을 때, 결과값을 출력하면 됩니다. 
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int dp[1005][1005];
char a[1005], b[1005], res[1005];
int main(int argc, char *argv[]) {
	int l1, l2, len, i, j;
	scanf("%s %s", a + 1, b + 1); // index 0 칸을 0의 값으로 이용하기 위해서 이렇게 했습니다.
	l1 = strlen(a + 1);
	l2 = strlen(b + 1);
	for (i = 1; i <= l1; ++i) {
		for (j = 1; j <= l2; ++j) {
			if (a[i] == b[j]) dp[i][j] = dp[i-1][j-1] + 1;  // 같을 때,
			else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);    // 다를 때,
		}
	}

	len = dp[l1][l2], res[len] = 0; // LCS 길이와 결과 배열 마지막 부분을 NULL로 채움.
	i = l1, j = l2;
	while (len && i && j) {
		if (a[i] == b[j]) {   // 같을 경우 결과 배열 뒤에 남은 부분에 추가
			res[--len] = a[i];
			--i; --j;
		} 
		else if (dp[i][j] == dp[i-1][j]) --i; // 다를 경우 다른 칸으로 이동
		else --j;
	}
	return !printf("%d\n%s\n", dp[l1][l2], res);
}