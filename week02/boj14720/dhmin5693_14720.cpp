/*
 * 무조건 0, 1, 2, 0, ... 순으로 먹습니다.
 * 해당하는 우유가 나오자마자 먹는 것이 최대값입니다.
 * flag는 0이 한 번이라도 나왔는가를 판별합니다.
 * 다 짜놓고 생각해보니 이런 로직이면 저장할 배열이 없어도 되겠네요...
 */
#include <cstdio>

int milk[1000] = { 0, }; // 우유
int dp[1000] = { 0, }; // dp값 저장

int main()
{
	int n;
	scanf("%d", &n);

	bool flag = false; // 0을 한 번도 만나지 않은 상태
	int idx = -1;

	for (int i = 0; i < n; ++i) {
		scanf("%d", &milk[i]);

		if (!flag) {
			// 0을 만나게 되면 true로 변경
			if (milk[i] == 0) {
				flag = true;
				++dp[i];
				idx = i;
			}
			continue;
		}

		if (flag && (milk[idx] + 1) % 3 == milk[i]) {
			dp[i] = dp[i - 1] + 1;
			idx = i;
		}

		else {
			dp[i] = dp[i - 1];
		}
	}

	printf("%d\n", dp[n - 1]);
	return 0;
}