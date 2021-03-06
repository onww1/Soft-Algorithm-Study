/*
 *  BOJ 7579. 앱
 *
 *  시간복잡도 : O(N*10^4)
 *  
 *  dp[c] : 비용이 c일 때 얻을 수 있는 최대 메모리 
 *
 *  0~N까지의 비용 인덱스 i에 대하여 i-1비용까지 사용했는 dp값을
 *  참조해서 i번째 비용도 사용했을 때의 최대 메모리를 dp에 갱신시킨다.
 *  
 */

#include <iostream>
#include <string.h>
using namespace std;
#define MXN 101

int N, M;
int am[MXN];
int ac[MXN];
int dp[MXN*MXN];
int tdp[MXN*MXN];//temp_dp

int max(int a, int b) {
	return a > b ? a : b;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) cin >> am[i];
	int tc = 0;//total_cost
	for (int i = 0; i < N; i++) {
		cin >> ac[i];
		tc += ac[i];
	}
	// 맨날 하던 멍청한 실수를 반복하였다. tdp를 쓰지 않고
	// dp[j] = max(dp[j - ac[i]] + am[i], dp[j]); 이런식으로 하면
	// i번째 dp는 i-1번째 dp의 값을 참조해서 값을 갱신해야 하는데
	// i번째에서 갱신된 값도 참조하여 틀리게 만든다.
	// 예를 들어 (메모리, 비용) => (10, 1) 하나 있다고 하자.
	// 틀린코드와 맞는 코드를 비교한 결과값을 보면 이해가 될 것이다.
	//  0  1  2  3  4  5
	//  0 20 30 40 50 60  <= 틀린 답
	//  0 10 10 10 10 10  <= 옳은 답
	for (int i = 0; i < N; i++) {
		for (int j = ac[i]; j <= tc; j++) {
			tdp[j] = max(dp[j - ac[i]] + am[i], dp[j]);
		}
		for (int j = 0; j <= tc; j++) dp[j] = tdp[j];
	}
	int ans = 0;
	for (int i = 0; i <= tc; i++) {
		if (dp[i] >= M) {
			ans = i;
			break;
		}
	}
	cout << ans << '\n';
	return 0;
}