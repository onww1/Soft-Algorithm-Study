// 아무 정점에서 시작해서 이 정점과 가장 멀리 있는 정점을 찾는다.
// 그러면 찾은 정점은 단말 정점이 된다. 단말 정점에서
// 가장 먼 정점까지의 거리가 곧 트리의 지름이 된다.

#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

int n;
int visited[10002] = { 0 };
vector<pair<int, int>> node[10002];

int ans = 0; //지름 길이
int end_point = 0; //지름에 해당하는 끝점
void dfs(int point, int length) {

	if (visited[point])
		return;

	visited[point] = 1;
	if (ans<length) {
		ans = length;
		end_point = point;
	}

	for (int i = 0; i<node[point].size(); i++) {
		dfs(node[point][i].first, length + node[point][i].second);
	}
}

int main() {

	cin >> n;

	int parent, child, length;
	for (int i = 0; i<n - 1; i++) {
		scanf("%d %d %d", &parent, &child, &length);
		node[parent].push_back(make_pair(child, length));
		node[child].push_back(make_pair(parent, length));
	}

	//가장 멀리 있는 정점(end_point) 구하기
	dfs(1, 0);

	ans = 0;
	memset(visited, 0, sizeof(visited));

	//end_point와 가장 멀리 있는 정점과의 거리 구하기
	dfs(end_point, 0);
	cout << ans << endl;


	return 0;
}