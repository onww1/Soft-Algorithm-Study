/*
BOJ 2980 - 도로와 신호등

시간복잡도 : O(L)
공간복잡도 : O(L)

arr에 빨간신호 시간, 빨간+초록 시간을 저장해둡니다.
다음으로 길을 하나씩 봐주며 신호등이 있을 때 빨간신호라면 기다리는 시간을 더해줍니다.
*/
#include <cstdio>
#include <algorithm>
#define pii pair<int,int>
using namespace std;

/* 🐣🐥 */
pii arr[1001];
int main() {
	int n, l, a, b, c, ans = 0;
	scanf("%d %d", &n, &l);
	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &a, &b, &c);
		arr[a] = { b,b+c };
	}
	for (int i = 1; i < l; i++) {
		if (arr[i].first != 0) {
			// 기다려야 한다면
			if (ans%arr[i].second < arr[i].first)
				ans += arr[i].first - ans % arr[i].second;
		}
		ans++;
	}
	printf("%d", ans);

	return 0;
}