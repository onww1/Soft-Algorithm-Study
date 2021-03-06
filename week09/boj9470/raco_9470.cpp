/*
 *  BOJ 9470. Strahler 순서 
 *
 *  시간복잡도 : O(TP)
 *  
 *  위상정렬을 이용해 현 노드는 모든 부모의 순서 값을 받아 가장 큰 값을 기억하며
 *  부모의 각 순서값의 개수를 기억해 둔다. 그리고 현 노드의 indegree가 0이 되면
 *  현 노드도 부모가 되어 자식들을 탐색하며 똑같은 과정을 반복한다.
 *  M번째 노드의 순서를 출력하면 된다.
 *  
 *  바다와 인접하는 노드는 하나로 나가는 길이 없는 노드이다.
 *  맨 밑의 첫 번째 예제를 예로 들어 부모의 노드의 순서 값이 1,1,2이면
 *  현 노드의 순서 값은 2가 나와야 한다. 처음에 1이 들어오면 1로 바꾸고
 *  같은 것이 들어오면 ++시켜 2로 바꾸고 또 2가 들어보니 3이 되어 틀렸다.
 *
 *  두 번째 예제를 예로 들어 dfs에서 모든 indegree를 없애니
 *  main에서 indegree가 0인 정점만 dfs를 실행하도록 하였는데
 *  모든 노드가 나중에는 0이 되어 시작점이 되어 버리게 하였다.
 *  모든 노드의 adj[cur]값은 지우지 않고 유지되니 영향을 미치면 안 되는데
 *  영향을 미치게 만들어 버려 틀렸다.
 * 
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
#define MXN 1002

class Stat {
public:
	int v, cnt[MXN + 1];// 가장 큰 값, 인덱스 번호의 개수
};

int indegree[MXN + 1];
Stat state[MXN + 1];
vector<int> adj[MXN + 1];
vector<int> start;
int K, M, P;

int max(int a, int b) {
	return a > b ? a : b;
}

void dfs(int cur) {
	if (state[cur].cnt[state[cur].v] >= 2) state[cur].v++;
	for (int i = 0; i < adj[cur].size(); i++) {
		int next = adj[cur][i];
		indegree[next]--;
		state[next].cnt[state[cur].v]++;
		if (state[next].v < state[cur].v) state[next].v = state[cur].v;
		if (indegree[next] == 0) dfs(next);
	}
}

int main() {
	fastio();
	int TC;
	cin >> TC;
	while (TC--) {
		cin >> K >> M >> P;
		memset(indegree, 0, sizeof(indegree));
		memset(state, 0, sizeof(state));
		for (int i = 0; i < MXN; i++) adj[i].clear();
		start.clear();
		int a, b;
		for (int i = 0; i < P; i++) {
			cin >> a >> b;
			indegree[b]++;
			adj[a].push_back(b);
		}
		for (int i = 1; i <= M; i++) {
			if (indegree[i] == 0) start.push_back(i);
		}

		for (int i = 0; i < start.size(); i++) {
			state[start[i]].v = 1;
			dfs(start[i]);
		}
		if (state[M].cnt[state[M].v] >= 2) state[M].v++;
		cout << K << " " << state[M].v << '\n';
	}
	return 0;
}

/*
첫 번째 틀린 반례
1
1 6 5
1 6
2 6
5 6
3 5
4 5
*/

/*
두 번째 틀린 반례
1
1 4 3
2 1
3 1
1 4
*/