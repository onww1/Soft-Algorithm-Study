/*
 *  BOJ 10999. 구간 합 구하기 2
 * 
 *  시간 복잡도 : O((N + M + K) * logN) 
 *  공간 복잡도 : O(2^(logN + 1))
 * 
 *  사실 시간 복잡도는 정확하게는 모르겠습니다. 
 *  구간 변경이더라도 레이지하게 하므로 합을 구하는 것보다 빠르게 가능할 것 같아서 logN에 
 *  처리가 가능할 것이라고 생각했습니다.
 *  
 *  lazy propagation은 업데이트를 해야 하는 노드이더라도 당장 필요가 없으면 업데이트를 하지 않고,
 *  어디에 기록을 해둔 다음 나중에 필요할 때 한꺼번에 계산을 하겠다는 아이디어입니다.
 *  그래서 시간을 조금 더 효율적으로 사용할 수 있는 것이죠. 
 *  그런 업데이트 정보를 저장해두는 배열이 lazy 배열입니다. 
 *  lazy 배열에 업데이트 되어야 하는 값을 저장해두고, 나중에 그 값에 접근을 할 때, 
 *  먼저 lazy 배열을 확인하고 그 값을 반영해준 다음 가져다가 쓰는 것입니다.
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;

// Fast I/O
const int BUFFER_SIZE = 1 << 18;
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

const int SZ = 1 << 20;
int N, M, K;
ll A[SZ], tree[2 * SZ], lazy[2 * SZ];

ll init(int node, int start, int end);
void update_lazy(int node, int start, int end);
void update_range(int node, int start, int end, int left, int right, ll diff);
ll sum(int node, int start, int end, int left, int right);

int main(int argc, char *argv[]) {
  N = readInt(), M = readInt(), K = readInt();
  for (int i = 0; i < N; ++i) A[i] = readLL();
  init(1, 0, N - 1);

  M += K;
  int a, b, c; ll d;
  while (M--) {
    a = readInt(), b = readInt(), c = readInt();
    if (a == 1) {
      d = readLL();
      update_range(1, 0, N - 1, b - 1, c - 1, d);
    } else {
      printf("%lld\n", sum(1, 0, N - 1, b - 1, c - 1));
    }
  }

  return 0;
}

// 초기화 함수
ll init(int node, int start, int end) {
  if (start == end) return tree[node] = A[start];
  int mid = (start + end) / 2;
  return tree[node] = init(node * 2, start, mid) + 
                      init(node * 2 + 1, mid + 1, end);
}

// lazy 업데이트 함수
void update_lazy(int node, int start, int end) {
  if (lazy[node] != 0) {
    tree[node] += (end - start + 1) * lazy[node];
    if (start != end) {
      lazy[node * 2] += lazy[node];
      lazy[node * 2 + 1] += lazy[node];
    }
    lazy[node] = 0;
  }
}

// 구간 업데이트 함수
void update_range(int node, int start, int end, int left, int right, ll diff) {
  update_lazy(node, start, end);
  if (end < left || right < start) return;
  if (left <= start && end <= right) {
    tree[node] += (end - start + 1) * diff;
    if (start != end) {
      lazy[node * 2] += diff;
      lazy[node * 2 + 1] += diff;
    }
    return;
  }
  
  int mid = (start + end) / 2;
  update_range(node * 2, start, mid, left, right, diff);
  update_range(node * 2 + 1, mid + 1, end, left, right, diff);
  tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

// 구간 합을 구하는 함수
ll sum(int node, int start, int end, int left, int right) {
  update_lazy(node, start, end);
  if (end < left || right < start) return 0LL;
  if (left <= start && end <= right) return tree[node];
  int mid = (start + end) / 2;
  return sum(node * 2, start, mid, left, right) +
         sum(node * 2 + 1, mid + 1, end, left, right);
}