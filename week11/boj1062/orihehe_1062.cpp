/*
BOJ 1062 - 가르침

시간복잡도 : O(2^21*N*26)
공간복잡도 : O(26N)

a,c,i,n,t 는 미리 켜두고, 나머지 알파벳의 모든 조합을 봐줍니다.
그 조합에서 읽을 수 있는 단어 개수의 최댓값을 구해 출력해줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

/* 🐣🐥 */
bool st[50][26];
bool alp[26];
int n, k, mv;
char x;
void dfs(int cur, int cnt) {
	if (cnt == k) {
		int j, xx = 0;
		for (int i = 0; i < n; i++) {
			for (j = 0; j < 26; j++) {
				if (!alp[j] && st[i][j]) break;
			}
			if (j == 26) xx++;
		}
		mv = max(mv, xx);
		return;
	}
	if (cur == 26) return;
	if (!alp[cur]) {
		alp[cur] = true;
		dfs(cur + 1, cnt + 1);
		alp[cur] = false;
	}
	dfs(cur + 1, cnt);
}
int main() {
	char ss[16];
	int len;
	scanf("%d %d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%s", ss);
		len = strlen(ss);
		for (int j = 0; j < len; j++) {
			st[i][ss[j] - 'a'] = true;
		}
	}
	if (k < 5) return !printf("0");
	alp[0] = alp[2] = alp['i' - 'a'] = alp['n' - 'a'] = alp['t' - 'a'] = true;
	dfs(0, 5);
	printf("%d", mv);

	return 0;
}