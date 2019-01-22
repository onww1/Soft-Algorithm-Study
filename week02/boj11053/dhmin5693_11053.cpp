/*
 * 2중 반복문으로 비교하며 이전 값보다 큰 경우 +1을 계속 더합니다.
 * 모든 연산이 끝나고 가장 높은 값을 산출합니다.
 */
#include <cstdio>

int num[1000];
int memo[1000];

int main()
{
	int n, max = 0;
	scanf("%d", &n);

    // 입력 숫자를 num 배열에 저장
	for (int i = 0; i < n; ++i)
		scanf("%d", &num[i]);

	for (int i = 0; i < n; ++i)
	{
        // 모든 부분에서 1로 시작
		memo[i] = 1;

        // 현재 숫자가 이전 숫자보다 크고, 이전의 dp값보다 적으면 +1
		for (int j = 0; j < i; ++j)
		{
			if (num[j] < num[i] && memo[i] < memo[j] + 1)
				memo[i] = memo[j] + 1;
		}
	}

	for (int i = 0; i < n; ++i)
		max = memo[max] < memo[i] ? i : max;

	printf("%d\n", memo[max]);

	return 0;
}