/*
 * 먼저 가로 세로 크기와 같은 char 배열에 입력을 받았습니다.
 * 그리고 다음으로 가로를 살피며 '-'가 이어지다가 끊기는 부분 혹은 line의 끝에서 count를 증가시켰습니다.
 * 세로 방향으로도 같은 방법으로 시행을 해줬고 그렇게 모인 count를 합해서 출력했습니다.
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