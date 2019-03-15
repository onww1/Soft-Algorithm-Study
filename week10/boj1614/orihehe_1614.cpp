/*
BOJ 1614 - 영식이의 손가락

시간복잡도 : O(1)
공간복잡도 : O(1)

각 손가락별로 계산해주면 됩니다.
2~4손가락 : 앞 손가락 수 + 한바퀴 + 홀수일 때 더 셀 수 있는 개수
*/
#include <cstdio>
using namespace std;

/* 🐣🐥 */
int main() {
	int n;
	long long k;
	scanf("%d %lld", &n, &k);
	if (n == 1)
		printf("%lld", k * 8);
	else if (n == 5)
		printf("%lld", 4 + k * 8);
	else
		printf("%lld", n - 1 + (k / 2) * 8 + (k % 2) * (5 - n) * 2);

	return 0;
}