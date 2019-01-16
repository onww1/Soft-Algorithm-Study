/*
BOJ 11725 - 트리의 부모 찾기

루트에서부터 dfs방식으로 연결된 노드들을 탐색해줍니다.
자신의 부모를 제외한 자신과 연결된 노드들은 자신의 자식들입니다.
따라서 부모 외의 연결된 노드들의 부모를 자신으로 저장 후 dfs로 타고 내려가면 됩니다.
*/
#include <cstdio>
#include <vector>
using namespace std;

vector<int> vec[100001];
int parent[100001];
void dfs(int cur) {
	for (int &v : vec[cur]) {
		if (parent[cur] != v) {
			parent[v] = cur; // v의 부모는 나
			dfs(v);
		}
	}
}
int main() {
	int n, a, b;
	scanf("%d", &n);
	for (int i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b);
		vec[a].push_back(b);
		vec[b].push_back(a);
	}
	dfs(1);
	for (int i = 2; i <= n; i++) printf("%d\n", parent[i]);

	return 0;
}