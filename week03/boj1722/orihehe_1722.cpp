/*
BOJ 1722 - 순열의 순서

약간 구데기 코드 같습니다 흑.
순열의 i번째 수들은 (n-i)!번씩 작은 순서대로 나오게 됩니다.
k번째 순열을 구할 때는 (k / (n-i)!)번째에 있는 수를 출력해주면 됩니다.

k를 구할 땐 사용되지 않은 수들 중 몇 번째로 작은 수인지(cnt)를 구하여
(n-i)! * cnt 를 더해주면 됩니다.
*/
#include <cstdio>
#define ll long long
using namespace std;

int arr[21], ans[21], ap = 1;
int main() {
	int n, cm, cnt = 0;
	ll k = 1, g = 1;
	scanf("%d %d", &n, &cm);
	if (cm == 1) {  // k번째 순열 구하기
		scanf("%lld", &k);
		k--;
		for (int i = 1; i <= n; i++) {
			arr[i] = i;
			g *= i; // n!
		}
		for (int i = n; i >= 1; i--) {
			cnt = 0;
			g /= i;
			for (int j = 1; j <= n; j++) {
				if (arr[j] == 0) continue;  // 사용된 수 넘어감
				if (cnt == k/g) {  // k/(n-i)! 번째 수 (for문의 i와 다름)
					ans[ap++] = j;
					arr[j] = 0; // 사용했음을 표시
					break;
				}
				cnt++;
			}
			k %= g;
		}
		for (int j = 1; j <= n; j++) printf("%d ", ans[j]);
	}
	else if (cm == 2) {  // k구하기
		for (int i = 1; i <= n; i++) {
			scanf("%d", &arr[i]);
			g *= i;
			ans[i] = i;
		}
		g /= n;
		for (int i = 1; i <= n; i++) {
			cnt = 0;
			for (int j = 1; j <= n; j++) {
				if (ans[j] == 0) continue;  // 사용된 수 넘어감
				if (ans[j] == arr[i]) {
					ans[j] = 0;
					break;
				}
				cnt++; // cnt번째로 작은 수
			}
			k += g * cnt; 
			if (i != n) g /= (n - i);
		}
		printf("%lld", k);
	}

	return 0;
}