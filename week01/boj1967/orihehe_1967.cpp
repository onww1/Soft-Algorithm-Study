/*
BOJ 1967 - 트리의 지름

1번 노드를 루트로 한 트리에서 1번 노드로부터 가장 먼 정점을 구하게되면 가장 먼 리프노드가 나오게 됩니다.
위에서 구한 노드를 farnode로 두고 이 노드를 트리의 루트로 생각하고 가장 먼 정점을 구하게 되면
farnode에서 가장 먼 리프노드인 정점이 나오게 됩니다.

잘 이해가 안 되서 문제에 나와있는 그림을 보고 생각해봤습니다.
파랗게 칠해져 있는 두 노드가 트리의 지름 양 끝 노드들입니다.
만약 칠해져 있지 않은 노드 하나를 잡고 가장 먼 노드를 찾았을 때 칠해져 있지 않은 노드가 가장 멀다면
파란 노드 하나 대신 그 노드가 트리의 지름 양 끝 노드가 되어야 할 것입니다.
따라서 아무 노드 하나로 가장 먼 노드를 찾았을 때 트리의 지름을 이루는 노드가 나온다는 사실을 알 수 있습니다.
*/
#include <cstdio>
#include <vector>
#include <cstring>
#define P pair<int,int>
using namespace std;

bool visited[100001];
int far[100001];
vector<P> vec[10001];
int farnode = 1;
int maxdis = 0;
void dfs(int start) {
	visited[start] = 1;
	for (P &next : vec[start]) {
		if (visited[next.first]) {
			continue;
		}
		// 다음 노드까지의 거리는 현재까지의 거리 + 다음노드로 가는 간선 거리
		far[next.first] += far[start]+next.second;
		dfs(next.first);
	}
	if (maxdis < far[start]) {
		maxdis = far[start]; // 가장 먼 거리
		farnode = start;  // 가장 먼 노드
	}
	return;
}

int main(void) {
	int n, parent, child = 0, value;

	scanf("%d", &n);

	while(child!=n) {
		scanf("%d %d %d", &parent, &child, &value);
		vec[parent].push_back({ child,value });
		vec[child].push_back({ parent,value });
	}

	dfs(1);
	maxdis = 0;

	memset(visited, false, sizeof(visited));
	memset(far, 0, sizeof(far));

	dfs(farnode);
	printf("%d", maxdis);

	return 0;
}