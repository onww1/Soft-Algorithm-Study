/*
BOJ 5600 - 품질검사

시간복잡도 : O(NlogN)
공간복잡도 : O(N)

먼저 합격 판정을 받은 부품들은 정상이라고 체크해줍니다.
그리고나서 불합격 판정을 받은 부품들 중 두 부품이 합격이라면 남은 한 부품은 불합격이 확실해집니다.
합격 불합격 결과가 없는 부품은 알 수 없음을 출력해줍니다.
*/
#include <cstdio>
#include <algorithm>
using namespace std;

/* 🐣🐥 */
struct bu {
	int a, b, c, v;
	bool operator < (const bu &aa) const {
		return v > aa.v;
	}
};
int ok[301];
int main() {
	int a, b, c, n, i;
	bu arr[1001];
	scanf("%d %d %d %d", &a, &b, &c, &n);
	for (i = 0; i < n; i++) {
		scanf("%d %d %d %d", &arr[i].a, &arr[i].b, &arr[i].c, &arr[i].v);
	}
	sort(arr, arr + n); // 합격판정이 앞으로 오도록
	for (i = 0; i < n; i++) {
		if (arr[i].v == 0) break;
		ok[arr[i].a] = ok[arr[i].b] = ok[arr[i].c] = 1;
	}
	for (; i < n; i++) {
		// 두 제품이 합격일때 나머지 하나 불합격 판정
		if (ok[arr[i].a] == 1 && ok[arr[i].b] == 1) ok[arr[i].c] = -1;
		if (ok[arr[i].a] == 1 && ok[arr[i].c] == 1) ok[arr[i].b] = -1;
		if (ok[arr[i].c] == 1 && ok[arr[i].b] == 1) ok[arr[i].a] = -1;
	}
	for (int i = 1; i <= a + b + c; i++) {
		if (ok[i] == 1) printf("1\n");
		if (ok[i] == 0) printf("2\n");
		if (ok[i] == -1)printf("0\n");
	}

	return 0;
}