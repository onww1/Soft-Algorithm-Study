/*
BOJ 2613 - 숫자구슬

시간복잡도 : O(NlogN)
공간복잡도 : O(N)

이분탐색의 mid값을 최댓값으로 둡니다.
그룹의 합이 mid값 이하가 되도록 구슬을 그룹 지었을 때 그룹의 개수가 m이하라면,
앞에서부터 mid값 이하로 구슬을 배치하며 그룹을 만들고, 남은 구슬 개수와 남은 그룹 개수가 같을 때
나머지 그룹은 구슬 1개씩을 배치하는 방법으로 m개의 그룹을 만들 수 있습니다.

따라서 그룹 수가 m이하일 때 mid값을 amv변수에 저장, r=mid-1
m초과일 때 최댓값을 늘려야 하므로  l=mid+1
*/
#include <cstdio>
using namespace std;

int main() {
	int n, m, l, r, mid, cnt = 0, sum = 0, amv = 0, i;
	int arr[301], ans[301];
	scanf("%d %d", &n, &m);
	for (i = 1; i <= n; i++) {
		scanf("%d", &arr[i]);
	}
	l = 1, r = 30000;
	ans[0] = 0;
	// 이분탐색으로 최소가 되는 최댓값을 찾는다.
	while (l <= r) {  
		mid = (l + r) / 2;
		cnt = 1; sum = 0;
		for (i = 1; i <= n; i++) {
			// i번째 구슬을 cnt그룹에 추가해도 mid 이하라면 추가
			if (sum + arr[i] <= mid) { 
				sum += arr[i];
			}
			else {
				// mid값 보다 하나의 구슬이 더 큰 값일 때 break
				if (sum == 0) break; 
				cnt++; i--;
				sum = 0;
			}
		}
		// 그룹이 많거나, mid보다 큰 구슬이 있을 때
		if (i <= n || cnt > m) { 
			l = mid + 1;
		}
		else {
			r = mid - 1;
			amv = mid;
		}
	}
	sum = 0; cnt = 1;
	for (i = 1; i <= n; i++) {
		// 남은 그룹 수와 남은 구슬 수가 같을 때 break
		if (n - i == m - cnt - 1) { 
			cnt++;
			break;
		}
		// 이분탐색에서 구한 최댓값 이하로 그룹 만들기
		if (sum + arr[i] <= amv) { 
			sum += arr[i];
			ans[cnt] = i; // 구슬의 인덱스 저장
		}
		else {
			if (sum == 0) break;
			cnt++; i--;
			sum = 0;
		}
	}
	for (; i <= n; i++) { // 남은 그룹은 1이 나오도록
		ans[cnt++] = i;
	}
	printf("%d\n", amv);
	for (int i = 1; i <= m; i++) printf("%d ", ans[i] - ans[i - 1]);

	return 0;
}