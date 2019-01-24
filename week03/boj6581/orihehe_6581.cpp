/*
BOJ 6581 - HTML

�켱 �� �ܾ �Է¹޽��ϴ�. l�������� �� ���� ���̸� ��ƵӴϴ�.
<br>�� ��� \n ��� �� l=0
<hr>�� ��� �̹� ���� ù �κ� (l==0)�̶�� hr���, �ƴ϶�� \n�� hr��� �� l=0
���� �� �ܾ� ���� �ܾ ������ �� (l+�ܾ��� ����)�� 80�� ���� �ʴ´ٸ� �̾ ����մϴ�.
�̶� ���⸦ �ϹǷ� l���� len+1���� �����ݴϴ�.
80�� �Ѵ´ٸ� \n�� �ܾ ������ְ� l�� len+1������ �ʱ�ȭ ���ݴϴ�.
*/
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
	char hr[83] = "--------------------------------------------------------------------------------\n";
	char st[83];
	int l = 0, len;
	while (~scanf("%s", st)) {
		len = strlen(st);
		if (st[0] == '<') {
			if (st[1] == 'b') {
				printf("\n");
				l = 0;
			}
			else if (st[1] == 'h') {
				if(l!=0) printf("\n%s", hr);
				else printf("%s", hr);
				l = 0;
			}
		}
		else if (l + len > 80) {
			printf("\n%s ", st);
			l = len + 1;
		}
		else {
			printf("%s ", st);
			l += len + 1;
		}
	}

	return 0;
}