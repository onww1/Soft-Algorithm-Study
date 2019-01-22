/*
BOJ 1431 - 시리얼 번호

info 구조체를 만들어 문자열, 문자열 길이, 자릿수 합 정보를 저장합니다.
문제에서 원하는 대로 정렬하기 위한 operator 를 만들어줬습니다.
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

struct info {
	char st[51];
	int len, hap;   // len - 문자열 길이, hap - 자릿수 합
};
bool operator < (info &a, info &b) {
	// 길이와 자릿수 합이 같다면 사전순 비교
	if (a.len == b.len && a.hap == b.hap) {
		for (int i = 0; i < a.len; i++) {
			if (a.st[i] != b.st[i]) {
				return a.st[i] < b.st[i];
			}
		}
	}
	// 길이가 같다면 자릿수 합 비교
	if (a.len == b.len) return a.hap < b.hap;
	return a.len < b.len;  // 길이 비교
}
int main() {
	char x[51];
	int n, sum, l;
	info sr[1001];
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		sum = 0;
		scanf("%s", x);
		strcpy(sr[i].st, x);
		l = strlen(x);
		sr[i].len = l;    // 시리얼번호 길이
		for (int j = 0; j < l; j++) {
			// 숫자인 것만 더하기
			if (x[j] <= '9' && x[j] >= '1') 
				sum += x[j] - '0';
		}
		sr[i].hap = sum;  // hap엔 자릿수 합
	}
	sort(sr, sr + n);
	for (int i = 0; i < n; i++) {
		printf("%s\n", sr[i].st);
	}

	return 0;
}