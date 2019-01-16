// 0 딸기우유, 1 초코우유, 2 바나나우유 
// 이 문제는 우유를 마실 수 있을 때 무조건 마셔야 가장 많은 우유를 마신다.
// cur은 현재 milk의 종류를 나타내며 바나나우유를 먹은 것으로 시작한다.
// (cur + 1) % 3이 입력 값 a와 같다면 우유를 마실 수 있는 경우이고
// 우유를 마신 개수 ans의 개수를 증가시켜준다.
// 그리고 cur에는 마신 우유로 cur값을 변경한다.
// N개의 입력에 대해서 이 과정을 반복해서 ans를 구하면 된다.

#include <iostream>
using namespace std;
int N;

int main() {
	cin >> N;
	int a;
	int ans = 0;
	int cur = 2;

	for (int i = 0; i < N; i++) {
		cin >> a;
		if (a == (cur + 1) % 3) {
			ans++;
			cur = (cur + 1) % 3;
		}
	}
	cout << ans << '\n';
	return 0;
}