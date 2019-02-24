/*
 *	BOJ 7578. 공장 
 *
 * 	시간 복잡도 : O(NlogN)
 *  공간 복잡도 : O(N)
 * 
 *  각 공장 번호에 대하여 좌표압축을 한 뒤, 윗 줄과 아랫 줄의 좌표를 다시 넣어주고, 
 *  각 좌표에 대해서 아랫 줄의 공장은 몇 번째 인덱스에 있는지도 pos 배열에 따로 저장을 해주었습니다. 
 * 
 *  그렇게 하여 맨 처음부터 시작해서 확인하면서 자신보다 앞서 확인했던 공장의 아랫줄이 자신보다 오른쪽에 있다면 
 *  그것을 카운트해서 추가하는 것입니다!
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 5e5;
const int MOD = 1e9 + 7;
const int INF = 0x7f7f7f7f;
ll N, A[MAX + 1][2], idx[MAX + 1], tree[MAX + 1], pos[MAX + 1];

// 업데이트 함수
void update(int node, ll diff) {
	while (node <= N) {
		tree[node] += diff;
		node += node & -node;
	}
}

// 1 ~ node의 합을 구해주는 함수
ll sum(int node) {
	ll ret = 0;
	while (node > 0) {
		ret += tree[node];
		node -= node & -node;
	}
	return ret;
}

int main(int argc, char *argv[]) {
	scanf("%lld", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%lld", &A[i][0]);
		idx[i] = A[i][0];
	}

	// 좌표 압축
	sort(idx, idx + N);
	for (int i = 0; i < N; ++i) {
		scanf("%lld", &A[i][1]);
		A[i][0] = lower_bound(idx, idx + N, A[i][0]) - idx;
		A[i][1] = lower_bound(idx, idx + N, A[i][1]) - idx;
		pos[A[i][1]] = i;
	}
	
	ll cnt = 0;
	update(pos[A[0][0]] + 1, 1);
	for (int i = 1; i < N; ++i) {
		int p = pos[A[i][0]];
		cnt += sum(N) - sum(p + 1);
		update(p + 1, 1);
	}

	return !printf("%lld\n", cnt);
}