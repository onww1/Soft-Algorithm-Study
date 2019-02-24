/*
 *	BOJ 7469. K번째 수 
 *
 *  시간 복잡도 : O(N * (logN)^2)
 *  공간 복잡도 : O(N) 
 * 
 *  주어진 값들을 0 ~ N - 1로 좌표 압축을 한 다음, 다시 배열에 그 압축된 값을 넣습니다. 
 *  그리고 그 값들을 가지고 세그먼트 트리를 만드는데, 이때 만드는 트리는 각 노드가 그 구간에 대한 
 *  값들을 모두 정렬된 상태로 가지고 있는 것입니다. 이후, 쿼리로 들어오는 구간에 대해서 
 *  0부터 N - 1을 이분탐색하여 그 구간에서 특정한 수 X보다 작은 값이 작은 것이 K개가 되는 값을 
 *  파라메트릭 서치를 하여 찾아냅니다.
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
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

const int SZ = 1 << 17;
const int MAX = 1e5;

int N, M, A[SZ], idx[MAX];
vector <int> tree[2 * SZ];

vector <int> init(int node, int start, int end);
int count(int node, int start, int end, int left, int right, int x);

int main(int argc, char *argv[]) {
	N = readInt(), M = readInt();

	// 좌표 압축
	for (int i = 0; i < N; ++i) A[i] = readInt(), idx[i] = A[i];
	sort(idx, idx + N);
	for (int i = 0; i < N; ++i) A[i] = lower_bound(idx, idx + N, A[i]) - idx;

	// 세그먼트 트리 초기화
	init(1, 0, N - 1);

	int a, b, k;
	while (M--) {
		a = readInt(), b = readInt(), k = readInt();
		int l = 0, r = N - 1, m, cnt, ans;
		while (l <= r) {	// 이분 탐색으로 k번째 수 탐색
			m = (l + r) / 2;
			cnt = count(1, 0, N - 1, a - 1, b - 1, m);
			if (cnt >= k) {
				r = m - 1;
				ans = m;
			}
			else l = m + 1;
		}
		printf("%d\n", idx[ans]);
	}

	return 0;
}

// 초기화 함수
vector <int> init(int node, int start, int end) {
	if (start == end) {
		tree[node].push_back(A[start]);
		return tree[node];
	}

	int mid = (start + end) / 2;
	vector <int> left = init(node * 2, start, mid);
	vector <int> right = init(node * 2 + 1, mid + 1, end);
	
	int l = 0, r = 0;
	while (l < left.size() && r < right.size()) {
		if (left[l] == right[r]) {
			tree[node].push_back(left[l++]);
			tree[node].push_back(right[r++]);
		}
		else if (left[l] < right[r]) tree[node].push_back(left[l++]);
		else tree[node].push_back(right[r++]);
	}
	while (l < left.size()) tree[node].push_back(left[l++]);
	while (r < right.size()) tree[node].push_back(right[r++]);
	return tree[node];
}

// x보다 작은 수가 몇 개 있는지 그 값을 리턴해주는 함수
int count(int node, int start, int end, int left, int right, int x) {
	if (end < left || right < start) return 0;
	if (left <= start && end <= right) {
		int idx = lower_bound(tree[node].begin(), tree[node].end(), x) - tree[node].begin();
		if (idx < end - start + 1 && tree[node][idx] == x) return idx + 1;
		return idx;
	}
	int mid = (start + end) / 2;
	return count(node * 2, start, mid, left, right, x) +
		   count(node * 2 + 1, mid + 1, end, left, right, x);
}