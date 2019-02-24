/*
 *	BOJ 3653. 영화 수집 
 *
 * 	시간 복잡도 : O(NlogN) 
 *  공간 복잡도 : O(N) 
 * 
 *  초기 책의 위치를 가장 밑에 있는 책을 가장 왼쪽에, 가장 위에 있는 책을 오른쪽으로 해서 
 *  정리해두고, 새로 뽑은 책은 그 자리에서 지우고, 배열에 있는 값 중에서 가장 오른쪽 값의 
 *  오른쪽에 두고, 그것을 펜윅트리에 업데이트하여 그 책보다 밑에 있는 책이 몇개 있는지를 확인하고, 
 *  전체 갯수인 N에서 빼서, 자신보다 위에 있는 책이 몇개였는지를 계산하도록 하였습니다.
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

// Fast I/O
const int BUFFER_SIZE = 1 << 17;
char buf[BUFFER_SIZE];
inline char read() {
	static int idx = BUFFER_SIZE;
	if (idx == BUFFER_SIZE) {
		int nidx = fread(buf, 1, BUFFER_SIZE, stdin);
		if (!nidx) return 0;
		idx = 0;
	}
	return buf[idx++];
}
inline int readInt() {
	int sum = 0, flg = 1;
	char now = read();
	while (now == ' ' || now == '\n') now = read();
	if (now == '-') flg = 0, now = read();
	while ('0' <= now && now <= '9') sum = sum * 10 + now - '0', now = read();
	return flg ? sum : -sum;
}
inline ll readLL() {
	ll sum = 0, flg = 1;
	char now = read();
	while (now == ' ' || now == '\n') now = read();
	if (now == '-') flg = 0, now = read();
	while ('0' <= now && now <= '9') sum = sum * 10 + now - '0', now = read();
	return flg ? sum : -sum;
}

const int MAX = 1e5;
int T, N, M, A[MAX + 1], tree[2 * MAX + 1];

void update(int node, int diff);
int sum(int node);

int main(int argc, char *argv[]) {
	T = readInt();
	while (T--) {
		N = readInt(), M = readInt();
		memset(tree, 0, sizeof(tree));
		for (int i = N; i > 0; --i) {
			A[N + 1 - i] = i;
			update(i, 1);
		}
		
		int P;
		for (int i = 1; i <= M; ++i) {
			P = readInt();
			printf("%d ", N - sum(A[P]));
			update(A[P], -1);
			A[P] = N + i;
			update(A[P], 1);
		}

		puts("");
	}

	return 0;
}

// 업데이트 함수
void update(int node, int diff) {
	while (node <= N + M) {
		tree[node] += diff;
		node += node & -node;
	}
}

// 1 ~ node의 합을 구하는 함수
int sum(int node) {
	int ret = 0;
	while (node > 0) {
		ret += tree[node];
		node -= node & -node;
	}
	return ret;
}