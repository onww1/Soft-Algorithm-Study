/*
BOJ 2004 - 조합 0의 개수

시간 복잡도 : O(logN)
공간 복잡도 : O(1)

nCm -> n! / ((n-m)! * m!)
끝자리 0은 2*5일때 하나씩 생기므로 분자와 분모의 2와 5의 개수를 구해줍니다.
n!에서 x의 개수는 n까지의 x의 배수 개수, x^2의 배수 개수, x^3의 배수 개수 ...가 됩니다. 
calc함수에서 그것을 구해주고 분자-분모 후 2의 개수, 5의 개수중 작은 값을 출력해줍니다.
*/
#include <cstdio>
using namespace std;

int n, m, x2 = 0, x5 = 0, tmp;
// num!의 x개수
int calc(int x, int num) {
	int cnt = 0;
	while (num > 0) {
		cnt += num / x;
		num /= x;
	}
	return cnt;
}
int main() {
	scanf("%d %d", &n, &m);
	tmp = n - m;
	x2 += calc(2, n);
	x5 += calc(5, n);
	x2 -= calc(2, m);
	x5 -= calc(5, m);
	x2 -= calc(2, tmp);
	x5 -= calc(5, tmp);

	if (x2 < 0 || x5 < 0) printf("0");
	else printf("%d", x2 > x5 ? x5 : x2);

	return 0;
}