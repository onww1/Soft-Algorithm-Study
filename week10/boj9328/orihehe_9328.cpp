/*
BOJ 9328 - 열쇠

시간복잡도 : O(TNM*27)
공간복잡도 : O(NM*27)

상근이는 밖에서부터 건물로 들어갑니다.
따라서 주어진 빌딩 외부를 '.'칸으로 둘러쌓고, 상근이를 0,0부터 위치시킵니다.
갖고있는 열쇠정보또한 갖고 bfs를 돌려줍니다. 아무 열쇠가 없는 경우도 있으니 26을 없는 경우로 하여 넣습니다.

대문자 칸을 만나면 열쇠가 없다면 q에 넣지 않습니다.
소문자 칸을 만나면 열쇠가 없을 시 그 열쇠를 줍고 key배열에 체크를 해준 뒤 그 열쇠정보와 위치 또한 큐에 넣어줍니다.
문서와 열쇠는 한번만 주우면 되니 방문시 '.'로 없애줍니다.
*/
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

/* 🐣🐥 */
char b[102][102], st[27];
int rgo[4] = { 1,0,-1,0 }, cgo[4] = { 0,-1,0,1 };
bool key[27], visited[27][102][102];
struct sg {
	int r, c, k;
};
queue<sg> q;
int main() {
	int t, n, m, len, ans;
	scanf("%d", &t);
	while (t--) {
		ans = 0;
		memset(key, false, sizeof(key));
		memset(visited, false, sizeof(visited));
		memset(b, '.', sizeof(b));
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			scanf("%s", b[i] + 1);
		}
		scanf("%s", st);
		if (st[0] != '0') {
			len = strlen(st);
			for (int i = 0; i < len; i++) {
				key[st[i] - 'a'] = true;
				q.push({ 0,0,st[i] - 'a' });
				visited[key[st[i] - 'a']][0][0] = true;
			}
		}
		q.push({ 0,0,26 }); // 열쇠 없을 때
		visited[26][0][0] = true;
		while (!q.empty()) {
			sg cur = q.front();
			q.pop();
			for (int i = 0; i < 4; i++) {
				int nr = cur.r + rgo[i], nc = cur.c + cgo[i];
				if (nr < 0 || nc < 0 || nr > n+1 || nc > m+1
					|| visited[cur.k][nr][nc] || b[nr][nc]=='*') continue; 
				// 문을 만났는데 열쇠가 없을 시
				if (b[nr][nc] <= 'Z' && b[nr][nc] >= 'A' && !key[b[nr][nc] - 'A']) continue;
				// 열쇠를 만났는데 없는 것이라면
				if (b[nr][nc] <= 'z' && b[nr][nc]>= 'a' && !key[b[nr][nc]-'a']) {
					q.push({ nr,nc,b[nr][nc] - 'a' });
					key[b[nr][nc] - 'a'] = true;
					visited[b[nr][nc] - 'a'][nr][nc] = true;
					b[nr][nc] = '.';
				}
				// 문서
				else if (b[nr][nc] == '$') {
					ans++;
					b[nr][nc] = '.';
				}
				q.push({ nr,nc,cur.k });
				visited[cur.k][nr][nc] = true;
			}
		}
		printf("%d\n", ans);
	}

	return 0;
}