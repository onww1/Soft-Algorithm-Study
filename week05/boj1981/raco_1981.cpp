/*
 *  BOJ 1981. 배열에서 이동
 *
 *  시간복잡도 O(N^2 * KlogK), K=200
 *
 *  이분탐색에서 m값을 방문할 칸 숫자의 최소값과 최대값의 차이로 한다.
 *  for (int i = 0; i + m <= 200; i++) 이런식으로 i가 최소값이 되고
 *  i+m값이 최대값이 된다. 그러면서 i를 1씩 증가시키며 m차이로
 *  (0, 0)부터 (N-1, N-1)까지 방문할 수 있다면 m을 ans에집어넣는다.
 *  이 과정을 이분탐색이 끝날 때까지 반복해 준다.
 * 
 *  처음 푼 풀이방법은 m값을 최대값(mxv)의 범위로만 정해서 0부터mxv
 *  까지의 범위에 모든 숫자들이 들어오면서 (0, 0)부터 (N-1, N-1)까지
 *  방문할 수 있는지 체크했다. 하지만 반례가 있었다.
 *  3
 *  2 4 9
 *  1 2 2
 *  9 2 4
 *  답은 2가 나와야 하는데 잘못된 풀이에서는 3이 나왔다. 왜냐하면
 *  방문할수 있는 칸의 숫자의 최대값과 최소값의 차이가 가장 작은 것을
 *  구했다. 그렇게 하면 위와 같은 예에서 9를 제외한 모든 수를 방문해
 *  최대값은 4, 최소값은 1이 나와 답이 3이 나온다. 답은 1을 방문하지
 *  않고 2, 4만 방문하며서 끝지점에 도달하는 것이 답이다.
 *  정답 풀이에서는 범위를 최소값~최대값으로 설정해주어 1을 방문하지
 *  못하도록 하여 정답을 받았다!
 *  
 */

#include <iostream>
#include <string.h>
using namespace std;
#define loop(i,x,y) for (int i=(x);i<(y);i++)
#define MXN 101

int N;
int area[MXN][MXN];
int visited[MXN][MXN];
int mxv, miv;
int dy[4] = { -1, 0, 1, 0 };
int dx[4] = { 0, 1, 0, -1 };

int min(int a, int b) {
	return a > b ? b : a;
}

int max(int a, int b){
	return a > b ? a : b;
}

// 범위를 정해서 (0, 0)부터 (N-1, N-1)까지 범위를 벗어나지 않으면서
// 방문할 수 있다면 true를 아니면 false를 리턴한다.
bool dfs(int y, int x) {
	if (area[y][x] > mxv || area[y][x] < miv) return false;
	if (y == N - 1 && x == N - 1) return true;
	visited[y][x] = true;
	int i;
	loop(i, 0, 4) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (nx < 0 || nx >= N || ny < 0 || ny >= N || visited[ny][nx]) continue;
		bool ret = dfs(ny, nx);
		if (ret) return ret;
	}
	return false;
}

int bs(int s, int e) {
	int ans = 0;
	while (s <= e) {
		int m = (e + s) / 2;
		bool chk;
		// 최소값과 최대값을 설정해서 dfs를 돌린다.
		for (int i = 0; i + m <= 200; i++) {
			memset(visited, 0, sizeof(visited));
			mxv = i + m, miv = i;
			chk = dfs(0, 0);
			if (chk) break;
		}
		// chk가 true이면 (0, 0)부터 (N-1, N-1)까지 방문할 수 있다는 소리로
		// ans에 m값을 넣고 그 다음은 m값을 더 작게 만들어 되는지 확인한다.
		// chk가 false이면 안 된다는 뜻으로 m값을 증가시켜 되는지 확인한다.
		if (chk) {
			ans = m;
			e = m - 1;
		}
		else s = m + 1;
	}
	return ans;
}

int main() {
	cin >> N;
	int i, j;
	loop(i, 0, N) {
		loop(j, 0, N) {
			cin >> area[i][j];
		}
	}
	cout << bs(0, 200) << '\n';
	return 0;
}