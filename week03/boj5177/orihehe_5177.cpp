/*
BOJ 5177 - ��� ������ �߸��Ǿ����ϴ�

���� ��찡 ������ �����ϴ�...
Ư�� ��ȣ �յ� ������ ������ٴ� ���� �����ϰ�, ���Ǵ�� ¥�ָ� �˴ϴ�.
�������� ap�� ���� �� �ؿ��� bp�� ���������ִ� ������ üũ�ϴ� ��쿡�� ap�� bp�� �ѹ��� �ٿ�����ϴ�. 
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
		// ���ڿ��� �� �� ������ �������
		while (ap<alen && a[ap] == ' ') ap++;
		while (bp<blen && b[bp] == ' ') bp++;

		for (; ap < alen; ap++) {
			// b���ڿ� ������ �ôٸ� �ݺ��� Ż��
			if (bp == blen) break;
			// �ϳ��� ������ �� Ư����ȣ�� �ƴ϶�� not equal
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
			//  �� �� ������ ��� ���ڰ� ���� ������ ap, bp ��ġ ����
			else if (a[ap] == ' ' && b[bp] == ' ') {
				while (ap<alen && a[ap] == ' ') ap++;
				while (bp<blen && b[bp] == ' ') bp++;
				bp--; ap--;
			}
			// ���� ��ȣ
			else if (a[ap] == '(' || a[ap] == '[' || a[ap] == '{') {
				if (b[bp] != '(' && b[bp] != '[' && b[bp] != '{') {
					eq = false; break;
				}
			}
			// �ݴ� ��ȣ
			else if (a[ap] == ')' || a[ap] == ']' || a[ap] == '}') {
				if (b[bp] != ')' && b[bp] != ']' && b[bp] != '}') {
					eq = false; break;
				}
			}
			// ,�� ;
			else if (a[ap] == ',' || a[ap] == ';') {
				if (b[bp] != ',' && b[bp] != ';') {
					eq = false; break;
				}
			}
			// ����
			else if (a[ap] <= '9' && a[ap] >= '0') {
				if (b[bp] > '9' || b[bp] < '0') {
					eq = false; break;
				}
			}
			// ���� ��ҹ���
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
		// �� ���ڿ� �� �ϳ��� �̹� ������ Ž������
		// ���� ���ڿ� Ž�� ���� ���ڰ� ���´ٸ� not equal
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