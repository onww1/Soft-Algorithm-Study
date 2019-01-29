/*
BOJ 1124 - 언더프라임

시간복잡도 : O(NlogN)
공간복잡도 : O(N)

처음 짤 땐 에라스토테네스의 체를 이용하여 소수인지 아닌지를 판별하고,
소수들을 벡터에 넣어 각 a~b수를 현재 소수로 나누어떨어지면 계속 나눠주는 식으로 풀었습니다.

다른 풀이를 찾아봤는데, 에라스토테네스의 체로 판별하는 과정에서
소수배열에 소수인지 아닌지를 저장하지 않고, 그 소수로 나눠지는 수들에 소수 값을 넣어줬습니다.
그리고나서 a~b 각 수(tmp)에 대해 sosu[tmp]에 저장된 소수로 나눠주고, 카운트 하는 과정을 반복합니다.
소수 배열에서 현재 수가 소수라면 배열의 값이 현재 수로 저장되어있으므로 그것으로 개수가 소수인지 판별합니다.
*/
#include <cstdio>
#define MAX 100000
using namespace std;

int sosu[100001], cnt;
int main() {
	for (int i = 2; i <= MAX; i++) {
		if (sosu[i] != 0) continue;
		for (int j = 1; j*i <= MAX; j++) {
			sosu[j*i] = i;
		}
	}
	int a, b, tmp, cnt, ans = 0;
	scanf("%d %d", &a, &b);
	for (int i = a; i <= b; i++) {
		tmp = i; cnt = 0;
		while (tmp > 1) {
			tmp /= sosu[tmp];
			cnt++;
		}
		if (cnt == sosu[cnt]) ans++;
	}
	printf("%d", ans);

	return 0;
}