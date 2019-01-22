/*
BOJ 2229 - 조 짜기

지문의 설명이 이해하기 좀 어려웠습니다..
나이 순으로 입력이 주어지고, 연속한 학생끼리만 묶어 조를 짤 수 있습니다.

조를 짤 학생 수를 한 명씩 늘려가며 최댓값을 구해봤습니다.
dp[i]에 i번째 학생 까지 조를 짰을 경우 최댓값을 넣어줍니다.
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int arr[1001];
int dp[1001];
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	for (int i = 2; i <= n; i++) {
		int minV = arr[i], maxV = arr[i];
		for (int j = 1; j < i; j++) { // i는 i앞 j명과 함께 조가 된다.
			minV = min(minV, arr[i-j]), maxV = max(maxV, arr[i-j]);
			// j명 만큼과 조가 되었을 때 점수 차이 + j 이전의 최댓값
			dp[i] = max(dp[i], dp[i - j-1] + maxV - minV); 
		}
	}
	printf("%d", dp[n]);

	return 0;
}