// 입력으로 4, {2,5,7,1}(각 인덱스는 1,2,3,4이다. 이 배열을 arr이라 하겠다.)을 준다.
// dp[2]에는 값 3이 들어갔고, dp[3]에는 값 5가 들어갔다고 하면,
// abs(arr[4] - arr[1])의 값 6(1~4까지를 한 조로 묶음) + dp[0](값이 0이다.)을 해서
// dp[4]의 값과 비교해서 더 큰 값을 dp[4]에 갱신
// abs(arr[4] - arr[2])의 값 6(2~4까지를 한 조로 묶음) + dp[1](값이 0이다.)을 해서
// dp[4]의 값과 비교해서 더 큰 값을 dp[4]에 갱신
// abs(arr[4] - arr[3])의 값 6(3~4까지를 한 조로 묶음) + dp[2](값이 3이다.)을 해서
// dp[4]의 값과 비교해서 더 큰 값을 dp[4]에 갱신
// abs(arr[4] - arr[4])의 값 0(4만 한 조로 만듦) + dp[3](값이 5이다.)을 해서
// dp[4]의 값과 비교해서 더 큰 값을 dp[4]에 갱신
// 인덱스를 4로 해서 설명했지만 이걸 i로 생각해서 N번 반복해서 계산해주면
// dp[N]에는 조들이 잘 짜여진 정도의 합 값중 제일 큰 값이 들어간다.

#include <iostream>
using namespace std;
#define MXN 1001

int dp[MXN];
int arr[MXN];
int N;

int abs(int a) {
	return a < 0 ? -a : a;
}

int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	cin >> N;
	for (int i = 1; i <= N; i++) cin >> arr[i];

	for (int i = 2; i <= N; i++) {
		for (int j = 1; j <= i; j++) {
			dp[i] = max(dp[i], abs(arr[i] - arr[j]) + dp[j - 1]);
		}
	}
	cout << dp[N] << '\n';
	return 0;
}