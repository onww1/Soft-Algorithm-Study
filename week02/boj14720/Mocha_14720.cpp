/*
 *  BOJ 14720. 우유 축제
 *
 *  DP 문제지만 굳이 값을 저장할 필요없이 한 번 훑으면 되는 문제였습니다.
 *  이런 것도 플레인 스위핑(?)이라고 하려나요ㅋㅋ
 * 
 *  딸기 우유부터 시작해서 훑으면서 초코우유 나오면 바로 바꿔주고,
 *  그 다음에 바나나 우유 나오면 바로 바꿔주고, 다시 딸기우유 바꿔주고,
 *  하는 식으로 쓸어나가면 되는 것이었어요!!
 */

#include <cstdio>
using namespace std;

int main() {
	int n, a, i, cur = 0, cnt = 0;
	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		scanf("%d", &a);
		if (a == cur) ++cnt, cur = (cur + 1) % 3; // 해당하는 우유 만나면 바로 마시고, 바꾸기
	}
	return !printf("%d\n", cnt);
}