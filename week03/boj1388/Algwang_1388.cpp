/*
 * ���� ���� ���� ũ��� ���� char �迭�� �Է��� �޾ҽ��ϴ�.
 * �׸��� �������� ���θ� ���Ǹ� '-'�� �̾����ٰ� ����� �κ� Ȥ�� line�� ������ count�� �������׽��ϴ�.
 * ���� �������ε� ���� ������� ������ ����� �׷��� ���� count�� ���ؼ� ����߽��ϴ�.
*/
#include<iostream>

using namespace std;

int main(void) {
	char arr[101][101];
	int H, W;
	scanf("%d %d", &H, &W);

	for (int i = 0; i < H; i++) {
		scanf("%s", arr[i]);
	}
	int horizonCount = 0;
	int verticalCount = 0;
	for (int i = 0; i < H; i++) {
		bool horizonFlag = false;
		for (int j = 0; j < W; j++) {
			if (arr[i][j] == '-') {
				horizonFlag = true;
			}
			else {
				if (horizonFlag) {
					horizonFlag = false;
					horizonCount++;
				}
			}
		}
		if (horizonFlag) {
			horizonCount++;
		}
	}
	for (int i = 0; i < W; i++) {
		bool verticalFlag = false;
		for (int j = 0; j < H; j++) {
			if (arr[j][i] == '|') {
				verticalFlag = true;
			}
			else {
				if (verticalFlag) {
					verticalFlag = false;
					verticalCount++;
				}
			}
		}
		if (verticalFlag) {
			verticalCount++;
		}
	}
	printf("%d\n", verticalCount + horizonCount);
}