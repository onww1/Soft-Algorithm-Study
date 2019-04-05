/*
BOJ 14890 - 경사로

시간복잡도 : O(N^2)
공간복잡도 : O(N^2)

가로 배열을 늘려 세로부분을 옮겨주어 가로부분만 봐주었습니다.
먼저 ru배열에 같은 값의 연속한 개수를 넣어줍니다.

그리고나서 가로로 한줄씩 보며 현재 위치의 수와 옆의 수가 다른 값일 때
작은 쪽에 L보다 많은 연속한 값이 있으면 그 위치에 경사로를 놓을 수 있다는 뜻이 됩니다.
그 과정에서 연속한 수의 차이가 1이하인지 체크, 경사로를 놓는다면 연속한 개수를 L만큼 줄여줍니다.
*/
#include <cstdio>
using namespace std;

/* 🐣🐥 */
int arr[201][101];
int ru[201][101];
int n, l, num, cnt, lp, ans;
int main() {
	scanf("%d %d", &n, &l);
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) 
			scanf("%d", &arr[i][j]);

	// 가로부분만 보기위해 옮겨준다.
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			arr[i + n][j] = arr[j][i];

	// 연속한 개수 세주기.
	for (int i = 0; i < 2*n; i++) { 
		num = arr[i][0], cnt = 1, lp = 0;
		for (int j = 1; j <= n; j++) {
			if (num != arr[i][j]) {
				while (lp < j) {
					ru[i][lp++] = cnt;
				}
				num = arr[i][j];
				cnt = 1;
			}
			else {
				cnt++;
			}
		}
	}
	// 가능 여부 체크 부분
	for (int i = 0; i < 2*n; i++) {
		for (int j = 1; j < n; j++) {
			if (arr[i][j - 1] > arr[i][j]) {
				if (ru[i][j] < l || arr[i][j-1]>arr[i][j]+1) break;
				lp = j;
				while (arr[i][lp] == arr[i][j]) {
					ru[i][lp++] -= l;
				}
			}
			else if (arr[i][j - 1] < arr[i][j]) {
				if (ru[i][j-1] < l || arr[i][j - 1]+1 < arr[i][j]) break;
				lp = j - 1;
				while (lp >=0 && arr[i][lp] == arr[i][j-1]) {
					ru[i][lp--] -= l;
				}
			}
			if (j == n - 1) ans++;
		}
	}
	printf("%d", ans);

	return 0;
}