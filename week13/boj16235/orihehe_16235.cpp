/*
BOJ 16235 - 나무 재테크

시간복잡도 : O(K*N^2)
공간복잡도 : O(N^2)

덱을 사용하여 가을에 번식하는 나무를 앞에 넣어 
봄에 어린 나무부터 양분을 먹을 수 있도록 해줍니다.
*/
#include <cstdio>
#include <queue>
using namespace std;

/* 🐣🐥 */
int rgo[8] = { -1,-1,-1,0,0,1,1,1 };
int cgo[8] = { -1,0,1,-1,1,-1,0,1 };
// arr : 양분, b : 현재 양분, dd : 죽은 양분
int arr[11][11], b[11][11], dd[11][11]; 
deque<int> q[11][11], tmp;
int n, m, k, x, y, z;
void bun(int r, int c) { // 8방향 번식
	for (int i = 0; i < 8; i++) {
		int nr = r + rgo[i], nc = c + cgo[i];
		if (nr < 0 || nc < 0 || nr >= n || nc >= n) continue;
		q[nr][nc].push_front(1);
	}
}
void spr() { // 봄
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tmp.clear();
			for (int &v : q[i][j]) {
				if (b[i][j] < v) {
					// 죽은 나무 양분 저장
					dd[i][j] += v / 2;
				}
				else {
					// 나이만큼 양분 없애고
					b[i][j] -= v;
					// 한살 추가
					tmp.push_back(v+1);
				}
			}
			q[i][j] = tmp;
		}
	}
}
void sm() { // 여름
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			b[i][j] += dd[i][j];
			dd[i][j] = 0;
		}
	}
}
void fa() { // 가을
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int &v : q[i][j]) {
				// 5의 배수일 때 번식
				if (!(v % 5)) {
					bun(i,j);
				}
			}
		}
	}
}
void wt() { // 겨울
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			b[i][j] += arr[i][j];
		}
	}
}
int main() {
	int ans = 0;
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &arr[i][j]);
			b[i][j] = 5;
		}
	}
	for (int i = 0; i < m; i++) {
		scanf("%d %d %d", &x, &y, &z);
		x--, y--;
		q[x][y].push_back(z);
	}
	while (k--) {  // 년도
		spr();
		sm();
		fa();
		wt();
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ans += q[i][j].size();
		}
	}
	printf("%d", ans);

	return 0;
}