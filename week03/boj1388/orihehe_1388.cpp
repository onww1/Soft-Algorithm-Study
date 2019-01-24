/*
BOJ 1388 - �ٴ� ���

-�� ���η�, |�� ���η� �̾����ִٸ� �� �����Դϴ�.
-�� ���� ���
�� �پ� ���ָ� tmp�� ���� ���ڰ� - ��� -��, �ƴ϶�� ���鹮�ڸ� �־�
���� - �� ������ �� ���� ���ڰ� -�� �ƴ϶�� ī��Ʈ ������ϴ�.
*/
#include <cstdio>
using namespace std;

char b[101][101];
int main() {
	int n, m, cnt = 0;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%s", b[i]);
	for (int i = 0; i < n; i++) {
		char tmp = ' '; // ������ ���鹮��
		for (int j = 0; j < m; j++) {
			if (b[i][j] == '-') {  // ���� - ����
				if (tmp == ' ') {  // ���� ���ڰ� | or ù����
					tmp = '-';
					cnt++;
				}
			}
			else tmp = ' '; // |���ڶ�� �������� ä��
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