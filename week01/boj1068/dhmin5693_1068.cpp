/*
 *  BOJ 1068. 트리
 *  
 *	노드를 저장할 Node 구조체를 만들었습니다.
 *	문제의 입력으로는 주어지지 않는 부모-자식간의 연결을 만들고
 *  자식 노드를 dfs로 순회하며 leaf에 해당하는 노드의 개수를 하나씩 더한 값을 정답으로 출력합니다.
 */

#include <cstdio>
#include <vector>

using namespace std;

typedef struct {
	int num;
	int parent;
	vector<int> child;
} Node;

Node node[50] = { 0, };
bool isVisited[50] = { false, }; // 방문 여부

int dfs(int nodeNumber, int deletedNode) {
	
    // 방문했던 노드는 탐색하지 않는다.
	if (isVisited[nodeNumber]) {
		return 0;
	}

    // 현재 노드 방문 처리
	isVisited[nodeNumber] = true;

    // 지워야 하는 노드는 방문하지 않는다. 이 부분에서 하위 depth로 가지 않으므로 연결이 끊긴 것.
	if (nodeNumber == deletedNode) {
		return 0;
	}

    // 자식 노드가 없고 부모 노드가 루트가 아니면 leaf 노드이다.
	if (node[nodeNumber].child.size() == 0 && node[nodeNumber].parent != -1) {
		return 1;
	}

    // 유일한 자식 노드가 삭제 대상인 경우엔 현재 노드를 leaf로 인식한다.
	if (node[nodeNumber].child.size() == 1 && node[nodeNumber].child[0] == deletedNode) {
		return 1;
	}

	int childSize = node[nodeNumber].child.size();

	int num = 0;

    // 자식 노드 순회
	for (int i = 0; i < childSize; ++i) {
		num += dfs(node[nodeNumber].child[i], deletedNode);
	}

	return num;
}

int main() {

    // 노드 개수 N
	int n;
	scanf("%d", &n);

	int root;

    
	for (int i = 0; i < n; ++i) {
		node[i].num = i; // 각 노드의 번호는 앞부터 0, 1, ..., n-1
		scanf("%d", &node[i].parent);

		if (node[i].parent != -1) {
			node[node[i].parent].child.push_back(i); // root가 아닌 노드는 부모-자식관계로 연결
		} else {
			root = i; // 부모가 -1일 때 root로 지정
		}
	}

    // 삭제할 대상이 되는 노드
	int deletedNode;
	scanf("%d", &deletedNode);

	printf("%d\n", dfs(root, deletedNode));

	return 0;
}