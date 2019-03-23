/*
BOJ 3098 - 소셜네트워크

시간복잡도 : O(N^3)
공간복잡도 : O(N^2)

fr배열에 처음의 친구관계를 표시해줍니다.
그리고나서 fr배열을 기준으로 i의 친구인 j의 친구들 k를 봐주며 i와 k를 친구로 만들어줍니다.
그 결과를 cur배열에 저장해주고 한 턴이 끝날 때마다 fr 배열에 cur배열을 복사해줍니다.
모든 사람이 친구가 될 수 있는 경우만 주어지므로 새로운 관계가 더이상 생기지 않을 때까지 봐주면 됩니다.
*/
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

/* 🐣🐥 */
bool fr[51][51];
bool cur[51][51];
vector<int> ans;
int main() {
	int n, m, a, b, cnt;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < 4; i++) {
		scanf("%d %d", &a, &b);
		fr[a][b] = true; 
		fr[b][a] = true;
	}
	memcpy(cur, fr, sizeof(cur));
	while (true) {
		cnt = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if (fr[i][j]) {
					for (int k = 1; k <= n; k++) {
						if (fr[j][k] && k!=i) {
							if (!cur[k][i]) {
								cur[k][i] = true;
								cur[i][k] = true;
								cnt++;
							}
						}
					}
				}
			}
		}
		if (cnt == 0) break;
		memcpy(fr, cur, sizeof(fr));
		ans.push_back(cnt);
	}
	printf("%d\n", ans.size());
	for (int i : ans) printf("%d\n", i);

	return 0;
}