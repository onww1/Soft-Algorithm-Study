/*
 *  BOJ 2098. 외판원 순회
 *
 *  시간복잡도 : O(2^N * N^2) => 왜 이렇게 나오는지는 정확히 이해가 안 간다..
 *  공간복잡도 : O(2^N * N)
 *  
 *  c = 현재 정점, m = 방문한 정점을 체크한 비트마스크
 *  cache[c][m] : 현재 정점 시작으로 앞으로 방문해야 할 
 *  모든 정점 방문하고 시작점으로 갈 때의 최소비용
 *  
 *  정점을 zero base로 하여 예제를 예로 들어보겠습니다.
 *  깊이              트리
 *  0                  0
 *  1        1         2         3   
 *  2     2     3   1     3   1     2
 *  3     3     2   3     1   2     1
 *  4                  0
 *  깊이 3의 모든 정점은 모두 마지막에 0으로 다시 돌아간다.
 *  깊이 1의 2정점에서 방문하지 않은 모든 정점을 방문하고 0으로 갈 때의 
 *  비용은 25이고, 깊이 1의 3정점에서 방문하지 않은 모든 정점을 방문하고
 *  0으로 갈 때의 비용은 23이다. 어떤 정점에서 시작했느냐에 따라서 비용값이
 *  달라질 수 있다. cache[1<<16]이 아닌 cache[N][1<<16]이 되는 이유이다.
 *  만약 정점 간의 누가 먼저 방문해야 될지 순서를 신경쓰지 않아도 되면 cache[1<<16]
 *  으로 처리가 가능하다. swea. 1865번 문제를 풀면 이해가 쉬울 것이다.
 */

#include <iostream>
#include <string.h>
using namespace std;
#define MXN 16

int wet[MXN][MXN];// weight
int N;
int cache[MXN][1 << 16];
const int INF = 2e9;

int min(int a, int b) {
	return a > b ? b : a;
}

int dfs(int c, int m) {
	if (m == (1 << N) - 1) {
		if(wet[c][0]) return wet[c][0];
		else return INF;
	}
	int &ret = cache[c][m];
	if (ret != -1) return ret;
	ret = INF;

	for (int i = 0; i < N; i++) {
		if (m & (1 << i) || wet[c][i] == 0) continue;
		ret = min(ret, dfs(i, m | (1 << i)) + wet[c][i]);
	}
	return ret;
}

int main() {
	fastio();
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> wet[i][j];
		}
	}
	memset(cache, -1, sizeof(cache));
	cout << dfs(0, 1) << '\n';
	return 0;
}