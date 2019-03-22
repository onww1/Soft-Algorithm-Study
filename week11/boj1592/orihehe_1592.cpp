/*
BOJ 1592 - 영식이와 친구들

시간복잡도 : O(NM)
공간복잡도 : O(N)

arr배열에 자리별로 공을 받은 횟수를 저장해둡니다.
모듈러연산을 하기 편하도록 인덱스를 0부터 잡아서 풀었습니다.
*/
#include <cstdio>
using namespace std;

/* 🐣🐥 */
int arr[1001];
int main() {
	int n, m, l, cur, cnt = 0;
	scanf("%d %d %d", &n, &m, &l);
	if (m == 1) printf("0");
	arr[0] = 1;
	cur = 0;
	while (true) {
		if (arr[cur] % 2) {
			cur = (cur + l) % n;
		}
		else {
			cur = (cur - l + n) % n;
		}
		arr[cur]++;
		cnt++;
		if (arr[cur] == m) break;
	}
	printf("%d", cnt);

	return 0;
}