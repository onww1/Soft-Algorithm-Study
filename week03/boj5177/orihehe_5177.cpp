/*
BOJ 5177 - 출력 형식이 잘못되었습니다

봐줄 경우가 굉장히 많습니다...
특수 부호 앞뒤 공백은 상관없다는 점을 주의하고, 조건대로 짜주면 됩니다.
포문에서 ap를 포문 맨 밑에서 bp를 증가시켜주니 공백을 체크하는 경우에서 ap와 bp를 한번씩 줄여줬습니다. 
*/
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
	int n, ap, bp, alen, blen;
	char a[1001], b[1001];
	bool eq;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf(" %[^\n] %[^\n]", a, b);
		ap = bp = 0;
		alen = strlen(a);
		blen = strlen(b);
		eq = true;
		// 문자열의 맨 앞 공백은 관계없음
		while (ap<alen && a[ap] == ' ') ap++;
		while (bp<blen && b[bp] == ' ') bp++;

		for (; ap < alen; ap++) {
			// b문자열 끝까지 봤다면 반복문 탈출
			if (bp == blen) break;
			// 하나만 공백일 때 특수부호가 아니라면 not equal
			if (a[ap] == ' ' && b[bp] != ' ') { 
				while (ap<alen && a[ap] == ' ') ap++;
				if (a[ap] >= '0' && a[ap] <= '9') {
					eq = false; break;
				}
				if (a[ap] >= 'a' && a[ap] <= 'z') {
					eq = false; break;
				}
				if (a[ap] >= 'A' && a[ap] <= 'Z') {
					eq = false; break;
				}
				ap--;
				bp--;
			}
			else if (a[ap] != ' ' && b[bp] == ' ') {
				while (bp<blen && b[bp] == ' ') bp++;
				if (b[bp] >= '0' && b[bp] <= '9') {
					eq = false; break;
				}
				if (b[bp] >= 'a' && b[bp] <= 'z') {
					eq = false; break;
				}
				if (b[bp] >= 'A' && a[bp] <= 'Z') {
					eq = false; break;
				}
				bp--;
				ap--;
			}
			//  둘 다 공백일 경우 문자가 나올 때까지 ap, bp 위치 변경
			else if (a[ap] == ' ' && b[bp] == ' ') {
				while (ap<alen && a[ap] == ' ') ap++;
				while (bp<blen && b[bp] == ' ') bp++;
				bp--; ap--;
			}
			// 여는 괄호
			else if (a[ap] == '(' || a[ap] == '[' || a[ap] == '{') {
				if (b[bp] != '(' && b[bp] != '[' && b[bp] != '{') {
					eq = false; break;
				}
			}
			// 닫는 괄호
			else if (a[ap] == ')' || a[ap] == ']' || a[ap] == '}') {
				if (b[bp] != ')' && b[bp] != ']' && b[bp] != '}') {
					eq = false; break;
				}
			}
			// ,와 ;
			else if (a[ap] == ',' || a[ap] == ';') {
				if (b[bp] != ',' && b[bp] != ';') {
					eq = false; break;
				}
			}
			// 숫자
			else if (a[ap] <= '9' && a[ap] >= '0') {
				if (b[bp] > '9' || b[bp] < '0') {
					eq = false; break;
				}
			}
			// 영어 대소문자
			else if ((a[ap] <= 'Z' && a[ap] >= 'A') || (a[ap] <= 'z' && a[ap] >= 'a')) {
				if ((b[bp] <= 'Z' && b[bp] >= 'A')|| (b[bp] <= 'z' && b[bp] >= 'a')) {
					
				}
				else {
					eq = false; break;
				}
			}
			// .
			else if (a[ap] == '.' && b[bp] != '.') {
				eq = false; break;
			}
			// :
			else if (a[ap] == ':' && b[bp] != ':') {
				eq = false; break;
			}
			bp++;
		}
		// 두 문자열 중 하나는 이미 끝까지 탐색했음
		// 남은 문자열 탐색 도중 문자가 나온다면 not equal
		while (ap < alen) {
			if (a[ap] != ' ') {
				eq = false; break;
			}
			ap++;
		}
		while (bp < blen) {
			if (b[bp] != ' ') {
				eq = false; break;
			}
			bp++;
		}
		printf("Data Set %d: %s\n", i, eq ? "equal" : "not equal");
		if (i != n) printf("\n");
	}

	return 0;
}