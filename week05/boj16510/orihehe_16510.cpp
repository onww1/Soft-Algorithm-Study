/*
BOJ 16510 - Predictable Queue

시간복잡도 : O(MlogN)
공간복잡도 : O(N)

배열에 i까지의 걸리는 시간을 저장해둡니다.
그리고나서 lower_bound로 x시간 이상의 최솟값을 찾습니다.
만약 lower_bound로 찾은 인덱스의 값이 x보다 크다면 -1한 값을, 같다면 그 값을 출력해줍니다.
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int arr[200002];
int main() {
	int n, m, x, idx;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		arr[i] += arr[i - 1];
	}
	while (m--) {
		scanf("%d", &x);
		idx = lower_bound(arr, arr + n, x) - arr;
		printf("%d\n", idx - (arr[idx] > x ? 1 : 0));
	}

	return 0;
}