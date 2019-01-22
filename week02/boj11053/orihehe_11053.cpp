/*
BOJ 11053 - 가장 긴 증가하는 부분 수열

현재 수(arr[i])보다 작은 이전 수들 중 가장 긴 길이 + 1이 dp[i]의 값이 됩니다.
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int arr[1000], dp[1000];
int main() {
	int n, maxL = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			if (arr[j] < arr[i]) { // 현재 수보다 작다면
				dp[i] = max(dp[j], dp[i]); // 이전에 나온 가장 긴 길이
			}
		}
		dp[i]++; // 가장 긴 길이에 현재 수도 포함
		maxL = max(maxL, dp[i]);
	}
	printf("%d", maxL);

	return 0;
}