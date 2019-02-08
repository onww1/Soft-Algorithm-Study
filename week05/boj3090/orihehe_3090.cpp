/*
BOJ 3090 - 차이를 최소로

시간복잡도 : O(NlogNlogK)  k=10^9
공간복잡도 : O(N)

먼저 입력받은 값들을 pq(최솟값)에 넣어줍니다. 
이분탐색의 mid값은 차이의 최댓값으로 설정, 작은 값을 먼저 뽑아내어 양 옆을 보는데, 
mid값보다 차이가 크다면 값을 현재+mid 값으로 바꿔주고 그 차이를 카운트, pq에 넣어줍니다.

만약 최솟값을 뽑아서 보지 않으면 현재 기준으로 양 옆 값들을 바꿨다고 해도
다음 작은 값을 볼 때 또 줄여주고 계속해서 영향을 미치게 됩니다.
*/
#include <cstdio>
#include <cstring>
#include <queue>
#define ll long long
#define pii pair<int,int>
using namespace std;

priority_queue<pii, vector<pii>, greater<pii>> q, tmp;
int arr[100002], ans[100002], aa[100002];
int main() {
	int n, l, r, mid;
	ll cnt, t;
	scanf("%d %lld", &n, &t);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
		tmp.push({ arr[i],i });
	}
	arr[0] = arr[n + 1] = 0;
	l = 0, r = 1000000000;
	while (l <= r) {
		mid = (l + r) / 2;
		memcpy(aa, arr, sizeof(aa)); // aa에 원래 배열 arr 복사
		cnt = 0;
		q = tmp; // 모두 넣어둔 pq 복사
		while (!q.empty()) {
			int nx = q.top().second; q.pop();
			// 현재와 양 옆의 차이가 mid이상이라면
			if (nx - 1 > 0 && aa[nx - 1] - mid > aa[nx]) {
				cnt += aa[nx - 1] - aa[nx] - mid;
				aa[nx - 1] = aa[nx] + mid; // 현재 + mid값으로 설정
				q.push({ aa[nx - 1],nx - 1 }); // 바뀐 값을 pq에 넣어줌
			}
			if (nx + 1 <= n && aa[nx + 1] - mid > aa[nx]) {
				cnt += aa[nx + 1] - aa[nx] - mid;
				aa[nx + 1] = aa[nx] + mid;
				q.push({ aa[nx + 1],nx + 1 });
			}
			if (cnt > t) break;
		}
		if (cnt > t) {
			l = mid + 1;
		}
		else {
			memcpy(ans, aa, sizeof(ans));
			r = mid - 1;
		}
	}
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);

	return 0;
}