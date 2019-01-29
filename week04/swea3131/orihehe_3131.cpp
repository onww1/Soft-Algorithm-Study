/*
SWEA 3131 - 100만 이하의 모든 소수

시간복잡도 : O(Nlog(logN))
공간복잡도 : O(N)

에라스토테네스의 체를 이용하여 문제를 풀었습니다.
소수 배열에서 소수인 수의 배수를 모두 true로 만들어주는 과정을 반복합니다.
false로 남아있는 수들이 소수이게 됩니다.
*/
#include <cstdio>
#define MAX 1000000
using namespace std;

bool sosu[1000001];
int main() {
	for (int i = 2; i <= MAX; i++) {
		if (sosu[i]) continue;
		printf("%d ", i);
		for (int j = 2; j*i <= MAX; j++) {
			sosu[i*j] = true;
		}
	}

	return 0;
}