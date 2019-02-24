/*
 *  BOJ 2042. 구간 합 구하기 
 * 
 *  시간 복잡도 : O((N + M + K) * logN)
 *  공간 복잡도 : O(2^(logN + 1))
 * 
 *  세그먼트 트리를 만들어서 쿼리를 처리하기만 하면 되는 기본 문제였습니다. 
 *  우선 A 배열에 값을 모두 받고, init 함수를 통해 tree 배열에 세그먼트 트리를 만들어주고,
 *  M + K 번 쿼리가 들어올 때, 그것을 받아서 log N 만에 해결하게 되죠! 
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

// 완전 이진트리를 위해 2의 거듭제곱으로 SIZE를 정해줍니다.
const int SZ = 1 << 20;
int N, M, K;
ll A[SZ], tree[2 * SZ];

ll init(int node, int start, int end);
void update(int node, int start, int end, int idx, ll diff);
ll sum(int node, int start, int end, int left, int right);

int main(int argc, char *argv[]) {
  N = readInt(), M = readInt(), K = readInt();
  for (int i = 0; i < N; ++i) A[i] = readLL();
  init(1, 0, N - 1);

  M += K;
  int a, b; ll c;
  while (M--) {
    a = readInt(), b = readInt(), c = readLL();
    if (a == 1) {
      update(1, 0, N - 1, b - 1, c - A[b - 1]);
      A[b - 1] = c;
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

// 업데이트 함수
void update(int node, int start, int end, int idx, ll diff) {
  if (idx < start || end < idx) return;
  if (start == end) {
    tree[node] += diff;
    return;
  }
  int mid = (start + end) / 2;
  update(node * 2, start, mid, idx, diff);
  update(node * 2 + 1, mid + 1, end, idx, diff);
  tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

// 구간 합을 구하는 함수
ll sum(int node, int start, int end, int left, int right) {
  if (end < left || right < start) return 0LL;
  if (left <= start && end <= right) return tree[node];
  int mid = (start + end) / 2;
  return sum(node * 2, start, mid, left, right) +
         sum(node * 2 + 1, mid + 1, end, left, right);
}