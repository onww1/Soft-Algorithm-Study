/*
BOJ 1790 - 수 이어 쓰기 2

k번째 자리 숫자가 어느 수(tmp)에서 나오는지를 구합니다.
s = 자릿수, x = 자릿수 별 숫자 개수 (한 자릿수 9개, 두 자릿수 90개, 세 자릿수 900개 ...)
x*s 는 s자릿수에서의 숫자 개수입니다. 

sum + x*s 가 k보다 작을 때 sum에 x*s를 더해줍니다. 
while문이 끝나면 구하려는 수는 s자릿수임을 알 수 있습니다.
sum은 s이전 자릿수에서 나온 숫자들의 개수이기 때문에 k에서 sum을 빼줍니다.

tmp를 s자릿수의 첫 수 (2면 10, 3이면 100)으로 만들어주고,
그리고 s자릿수에선 한 수마다 s개의 숫자가 있기 때문에 k-1을 s로 나눠준 값을 tmp에 더해줍니다.
마지막으로 tmp를 ori문자열로 바꾸고, ori[(k - 1) % s]를 출력해줍니다.

자료형을 int로 하여 풀었다가 첫번째 while문에서 오버플로로 인한 TLE를 받았습니다. (ㅠㅠ)
*/
#include <cstdio>
#define ll long long
using namespace std;

int main() {
	ll x = 9, n, k, s = 1, sum = 0, tmp = 1, op = 0;
	char ori[10];
	scanf("%lld %lld", &n, &k);
	while (sum + x*s < k) {
		sum += x * s;
		x *= 10; // 자릿수별 숫자 개수
		s++;  // 자릿수
	}
	k -= sum;
	for (int i = 2; i <= s; i++) tmp *= 10;
	tmp += (k-1) / s;  // k번째 수는 tmp에 있다!
	if (tmp > n) printf("-1"); // tmp가 n보다 크다면 k번째 자리 숫자를 찾을 수 없음.
	else {
		ll mn = 100000000;
		while (mn > tmp) mn /= 10;
		while (mn > 0) {  // tmp를 ori문자열로 바꾸기
			ori[op++] = tmp / mn + '0';
			tmp %= mn;
			mn /= 10;
		}
		printf("%c", ori[(k - 1) % s]);
	}

	return 0;
}