/*
BOJ 1990 - 소수인팰린드롬

시간복잡도 : O(NlogN+Nsqrt(N))   - sort, isPrime
공간복잡도 : O(N)

처음에는 에라토스테네스의 체로 소수를 모두 구하고 팰린드롬을 확인하려 했으나 TLE를 받았습니다.
어찌 아슬하게 되지 않을까 기대했지만 아니었습니다..
그래서 다른 방법을 생각해 봤는데, 1억 이하의 수에서 팰린드롬인 수의 개수는 2*10^4 미만이었습니다.
팰린드롬인 수를 먼저 구하고, 소수인지 판별하면 되겠다 싶은데 소수인지 판별하는 것이 또 문제였습니다.
팰린드롬인 수(x)마다 1부터 x/2까지 나눠지는지 보면 시간이 또 터지죠..

그래서 갓구글에 "소수인지 판별"을 검색해보니 x의 제곱근까지만 검사해도 된다고 나왔습니다! 우와
n을 소수가 아니라고 가정, n=a*b (a<b) 로 두면 a는 sqrt(N) 이하입니다.
isPrime에서 2~sqrt(N) 까지 검사하는데 이것을 a로 둡니다.
n이 a로 나누어 떨어지지 않으면 결국 1*n만이 n을 만들 수 있으므로 n은 소수이게 됩니다.
증명 참고 - https://code.i-harness.com/ko-kr/q/58abcf

팰린드롬 구현은 현재 자릿수 - 2^1~..에 있는 팰린드롬 수의 앞 뒤에 1~9의 수를 붙이는 식으로 구현했습니다.
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

vector<int> vec[9];  // vec[자릿수-1] 에 해당 자릿수의 팰린드롬인 수가 들어갑니다. 
bool isPrime(int n) {  // n이 소수인지 판별
	int sn = (int)sqrt(n);
	for (int i = 2; i <= sn; i++) {
		if (n%i==0) return false;
	}
	return true;
}
int main() {
	int a, b, s, ss;
	scanf("%d %d", &a, &b);
	for (int i = 1; i <= 9; i++) {
		vec[0].push_back(i);
		vec[1].push_back(i * 10 + i);
	}
	sort(vec[0].begin(), vec[0].end());
	sort(vec[1].begin(), vec[1].end());
	for (int t = 2; t < 8; t++) { // 자릿수
		// s는 수를 맨앞에 붙이기 위한 10^t
		// ss는 j에 따른 중간 수 위치 변경
		s = pow(10, t); ss = 10; 
		for (int j = t - 2; j >= 0; j-=2) { // 짝수길이 홀수길이 따로
			for (int v : vec[j]) {
				// 1과 9를 수 앞뒤에 붙입니다.
				for (int i = 1; i <= 9; i++) { 
					vec[t].push_back(i*s + v * ss + i);
				}
			}
			ss *= 10; // j가 줄어듦에따라 중간수가 한칸 앞으로 가야함
		}
		s = pow(10, t);
		for (int i = 1; i <= 9; i++) {
			vec[t].push_back(i*s + i);  // 중간부가 모두 0인 팰린드롬수
		}
		sort(vec[t].begin(), vec[t].end());
	}
	for (int i = 0; i < 8; i++) {
		for (int v : vec[i]) {
			if (v < a) continue;
			if (v > b) break;
			if (isPrime(v)) {
				printf("%d\n", v);
			}
		}
	}
	printf("-1");

	return 0;
}