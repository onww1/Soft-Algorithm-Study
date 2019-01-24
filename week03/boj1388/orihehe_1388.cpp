/*
BOJ 1388 - 바닥 장식

-가 가로로, |가 세로로 이어져있다면 한 판자입니다.
-를 예로 들면
한 줄씩 봐주며 tmp에 이전 판자가 - 라면 -를, 아니라면 공백문자를 넣어
현재 - 가 나왔을 때 이전 판자가 -가 아니라면 카운트 해줬습니다.
*/
#include <cstdio>
using namespace std;

char b[101][101];
int main() {
	int n, m, cnt = 0;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%s", b[i]);
	for (int i = 0; i < n; i++) {
		char tmp = ' '; // 시작은 공백문자
		for (int j = 0; j < m; j++) {
			if (b[i][j] == '-') {  // 현재 - 판자
				if (tmp == ' ') {  // 이전 판자가 | or 첫시작
					tmp = '-';
					cnt++;
				}
			}
			else tmp = ' '; // |판자라면 공백으로 채움
		}
	}
	for (int i = 0; i < m; i++) {
		char tmp = ' ';
		for (int j = 0; j < n; j++) {
			if (b[j][i] == '|') {
				if (tmp == ' ') {
					tmp = '|';
					cnt++;
				}
			}
			else tmp = ' ';
		}
	}
	printf("%d", cnt);

	return 0;
}