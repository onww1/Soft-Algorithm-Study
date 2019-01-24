/*
BOJ 3005 - ũ�ν����� ���� �Ĵٺ���

ó������ �߰��� #�� ���ִٸ� �ܾ ���� ���ϴ� ������ �߸� �����߽��ϴ�(...)
�� ��(r)�� ������ �� ���� �̻��� �ܾ st�迭�� �־��־����ϴ�.
�д� �߿� #�� ������ ������ tmp�� �� ���� �̻��̶�� �־��ְ�, �������ϴ�.
���� ��� �а� ������ �־��ݴϴ�.
�� ĭ(c)�� �д� ������ ���� �����ϴ�.
st �迭 sort �� �� ���� �ܾ ���������� ���� �ռ��� �ܾ �˴ϴ�.
*/
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string st[400];
int tp;  // �ܾ��� ����
int main() {
	int r, c;
	char b[21][21];
	scanf("%d %d", &r, &c);
	for (int i = 0; i < r; i++) {
		scanf("%s", b[i]);
	}
	for (int i = 0; i < r; i++) {  // �� �پ�
		string tmp = "";
		for (int j = 0; j < c; j++) {
			if (b[i][j] != '#') tmp += b[i][j];
			else { // #�� ������!
				// �� ���� �̻��� �� st�迭�� �־��ش�.
				if (tmp.size() > 1) st[tp++] = tmp;
				tmp = "";  //  ����ֱ�
			}
		}
		if (tmp.size() > 1) st[tp++] = tmp;
	}
	for (int i = 0; i < c; i++) {  //  �� ĭ��
		string tmp = "";
		for (int j = 0; j < r; j++) {
			if (b[j][i] != '#') tmp += b[j][i]; 
			else {
				if (tmp.size() > 1) st[tp++] = tmp;
				tmp = "";
			}
		}
		if (tmp.size() > 1) st[tp++] = tmp;
	}
	sort(st, st + tp);
	cout << st[0];

	return 0;
}