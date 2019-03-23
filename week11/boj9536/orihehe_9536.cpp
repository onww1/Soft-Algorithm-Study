/*
BOJ 9536 - 여우는 어떻게 울지?

시간복잡도 : O(TN^2)
공간복잡도 : O(N)

goes가 나오기 전까지 한 단어씩 받아 fox배열에 넣어줍니다.
첫 goes가 나오면 fox배열 마지막에 첫 동물 이름이 들어가있으니 fp를 하나 빼줍니다.

이제 goes가 나올 때마다 다음 단어를 bw배열에 넣기위해 bb로 체크 해줍니다.
say?가 나왔다면 입력받는 것을 종료해주고 울음소리와 비교해줍니다.
*/
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

/* 🐣🐥 */
string bw[102], fox[102];
bool ans[102];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int t, bp, fp;
	string tmp;
	cin >> t;
	while (t--) {
		bp = fp = 0;
		memset(ans, true, sizeof(ans));
		bool ff = false, bb = false;
		while (cin >> tmp) {
			if (tmp == "say?") break;
			if (tmp == "goes") {
				ff = true;
				if (bp == 0) {
					fp--;
				}
				bb = true;
				continue;
			}
			// 울음 소리 저장
			if (bb) {
				bw[bp++] = tmp;
				bb = false;
			}
			// goes가 나오기 전까지 모든 단어 저장
			if (!ff) {
				fox[fp++] = tmp;
			}
		}
		for (int i = 0; i < bp; i++) {
			for (int j = 0; j < fp; j++) {
				if (fox[j] == bw[i]) ans[j] = false;
			}
		}
		for (int i = 0; i < fp; i++) if (ans[i]) cout << fox[i] << ' ';
		cout << "\n";
	}

	return 0;
}