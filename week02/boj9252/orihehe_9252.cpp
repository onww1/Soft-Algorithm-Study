/*
BOJ 9252 - LCS 2

dp[i][j] = s1문자열 i까지, s2문자열 j까지의 LCS길이 값으로 설정합니다.
s1의 i-1, s2의 j까지의 LCS 길이, s1의 i, s2의 j-1까지의 LCS 길이,
i-1, j-1까지의 LCS 길이에 s1[i]와 s2[j]가 같다면 +1 한 값중 최댓값을 저장해줍니다.

이전 값들과 비교했을 때 dp[i - 1][j - 1] + (s1[i] == s2[j]) 부분에서만 값이 증가하기 때문에
LCS는 dp[i][j]가 최초로 증가한 부분의 문자를 포함하게 됩니다.
따라서 현재 위치 (p1,p2)에서 dp[p1-1][p2] 와 dp[p1][p2-1] 의 값들이 
모두 dp[p1][p2]와 다를 때 스택에 문자를 넣어주고 출력해줍니다.

문자열을 입력 받을 때 s1의 주소값 + 1 부터 넣어주어 dp를 채울 때 조금 편하게 하려 시도했습니다.
이런 방식은 처음 써 봤는데 런타임 에러가 계속 나서 이유를 찾아보니
strlen(s1)을 할 때 s1[0]에 '\0' 문자가 들어있다면 길이 0을 리턴받아 dp배열이 제대로 채워지지 않고,
밑의 while문에서 dp[-1]에 접근하게 됐습니다.
(우연히 질문 게시판에 같은 상황의 분이 계셔서 이유를 알 수 있었습니다..)
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <stack>
using namespace std;

int dp[1001][1001];
int main() {
	char s1[1002], s2[1002];
	int len1, len2, p1, p2;
	stack<char> sta;
	scanf("%s %s", 1 + s1, 1 + s2);
	s1[0] = '0', s2[0] = '1';
	len1 = strlen(s1)-1, len2 = strlen(s2)-1;
	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			dp[i][j] = max({dp[i - 1][j - 1] + (s1[i] == s2[j]),
				dp[i][j - 1], dp[i - 1][j]});
		}
	}
	p1 = len1, p2 = len2;
	while (dp[p1][p2] > 0) {
		int tmp = dp[p1][p2];
		if (dp[p1 - 1][p2] == tmp) p1--;
		else if (dp[p1][p2 - 1] == tmp) p2--;
		else { // 최초로 증가한 부분
			sta.push(s1[p1]);
			p1--, p2--;
		}
	}
	printf("%d\n", dp[len1][len2]);
	while (!sta.empty()) {
		printf("%c", sta.top()); sta.pop();
	}

	return 0;
}