/*
BOJ 1990 - �Ҽ����Ӹ����

�ð����⵵ : O(NlogN+Nsqrt(N))   - sort, isPrime
�������⵵ : O(N)

ó������ �����佺�׳׽��� ü�� �Ҽ��� ��� ���ϰ� �Ӹ������ Ȯ���Ϸ� ������ TLE�� �޾ҽ��ϴ�.
���� �ƽ��ϰ� ���� ������ ��������� �ƴϾ����ϴ�..
�׷��� �ٸ� ����� ������ �ôµ�, 1�� ������ ������ �Ӹ������ ���� ������ 2*10^4 �̸��̾����ϴ�.
�Ӹ������ ���� ���� ���ϰ�, �Ҽ����� �Ǻ��ϸ� �ǰڴ� ������ �Ҽ����� �Ǻ��ϴ� ���� �� ���������ϴ�.
�Ӹ������ ��(x)���� 1���� x/2���� ���������� ���� �ð��� �� ������..

�׷��� �����ۿ� "�Ҽ����� �Ǻ�"�� �˻��غ��� x�� �����ٱ����� �˻��ص� �ȴٰ� ���Խ��ϴ�! ���
n�� �Ҽ��� �ƴ϶�� ����, n=a*b (a<b) �� �θ� a�� sqrt(N) �����Դϴ�.
isPrime���� 2~sqrt(N) ���� �˻��ϴµ� �̰��� a�� �Ӵϴ�.
n�� a�� ������ �������� ������ �ᱹ 1*n���� n�� ���� �� �����Ƿ� n�� �Ҽ��̰� �˴ϴ�.
���� ���� - https://code.i-harness.com/ko-kr/q/58abcf

�Ӹ���� ������ ���� �ڸ��� - 2^1~..�� �ִ� �Ӹ���� ���� �� �ڿ� 1~9�� ���� ���̴� ������ �����߽��ϴ�.
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

vector<int> vec[9];  // vec[�ڸ���-1] �� �ش� �ڸ����� �Ӹ������ ���� ���ϴ�. 
bool isPrime(int n) {  // n�� �Ҽ����� �Ǻ�
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
	for (int t = 2; t < 8; t++) { // �ڸ���
		// s�� ���� �Ǿտ� ���̱� ���� 10^t
		// ss�� j�� ���� �߰� �� ��ġ ����
		s = pow(10, t); ss = 10; 
		for (int j = t - 2; j >= 0; j-=2) { // ¦������ Ȧ������ ����
			for (int v : vec[j]) {
				// 1�� 9�� �� �յڿ� ���Դϴ�.
				for (int i = 1; i <= 9; i++) { 
					vec[t].push_back(i*s + v * ss + i);
				}
			}
			ss *= 10; // j�� �پ�꿡���� �߰����� ��ĭ ������ ������
		}
		s = pow(10, t);
		for (int i = 1; i <= 9; i++) {
			vec[t].push_back(i*s + i);  // �߰��ΰ� ��� 0�� �Ӹ���Ҽ�
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