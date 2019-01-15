/*
BOJ 1068 - 트리

vector를 사용하여 각 노드를 잇는 간선 정보를 넣어주었습니다.
search함수에서 dfs방식으로 간선을 타고 내려가 리프노드를 탐색해줍니다.
이 때 연결된 노드가 삭제된 노드라면 탐색하지 않도록 하였고, 탐색한 횟수를 c변수에 카운트 해줬습니다.
만약 c가 0이라면 그 노드는 리프노드이므로 카운트 해주었습니다.
*/
#include <cstdio>
#include <vector>
using namespace std;

vector<int> tree[51];
int cnt, x;
void search(int cur) {
	if (cur == x) return;
	int c = 0;
	for (int v : tree[cur]) {
		// 삭제한 노드로는 들어가지 않음
		if (v == x) continue;
		search(v); c++;
	}
	// 다음 노드가 없다면 리프노드
	if (c == 0) cnt++;
}
int main() {
	int n, root;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		if (x == -1) root = i;
		else tree[x].push_back(i);
	}
	scanf("%d", &x);
	search(root);
	printf("%d", cnt);

	return 0;
}