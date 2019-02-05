/*
BOJ 2110 - 공유기 설치

시간복잡도 : O(NlogK)  K=1000000000
공간복잡도 : O(N)

가장 인접한 두 공유기 사이의 거리를 mid값으로 설정합니다.
우선 맨 앞 좌표에 공유기를 설치하는 것이 그 좌표가 영향을 미치는 거리가 최대가 될 것은 자명합니다.
따라서 맨 앞 좌표에 하나를 설치 하고, 다음 좌표들을 둘러보는데,
현재 좌표와 이전 좌표의 거리가 mid값 이상이라면 공유기를 설치하고 카운트 해줍니다.
*/
#include <cstdio>
#include <algorithm>
using namespace std;

int arr[200000];
int main() {
	int n, c, l, r, mid, last, cnt, ans;
	scanf("%d %d", &n, &c);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	sort(arr, arr + n);
	l = 1, r = 1000000000;
	while (l <= r) {
		mid = (l + r) / 2;
		last = arr[0]; 
		cnt = 1;
		for (int i = 1; i < n; i++) {
			if (arr[i] - last >= mid) {
				cnt++;
				last = arr[i];
			}
		}
		if (cnt >= c) {
			ans = mid;
			l = mid + 1;
		}
		else {
			r = mid - 1;
		}
	}
	printf("%d", ans);

	return 0;
}