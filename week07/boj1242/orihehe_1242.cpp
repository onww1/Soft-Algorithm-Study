/*
BOJ 1242 - 소풍

시간복잡도 : O(N)
공간복잡도 : O(1)

남은 친구들을 1번을 말할 친구를 맨 앞으로 오도록 재배치 해주면
1 2 3 4 5
3 4 5 1
5 1 3
3 5
3
동호의 위치는 m%(인원수)만큼 앞으로 땡겨지게 됩니다.
*/
#include <cstdio>
using namespace std;

/* 🐣🐥 */
int main() {
	int n, m, k, loc, cnt = 1;
	scanf("%d %d %d", &n, &m, &k);
	loc = k;
	for (int i = n; i > 1; i--) {
		// 동호가 퇴장할 차례라면 나오기
		if (loc == (m - 1) % i + 1) break;
		cnt++;
		loc -= m % i;
		if (loc <= 0) loc += i;
	}
	printf("%d", cnt);

	return 0;
}