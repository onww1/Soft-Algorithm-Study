/*
 *  BOJ 14438. 수열과 쿼리 17
 * 
 *  시간 복잡도 : O((N + M) * logN)
 *  공간 복잡도 : O(N)
 * 
 *  수열과 쿼리 시리즈 문제들이 다 비슷하죠. 
 *  이것도 구간에 대한 최솟값을 구하는 문제이므로 세그먼트트리를 만들어서 쿼리를 처리해주면 됐습니다!
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef long long ll;
typedef pair <int, int> pii;

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

const int SZ = 1 << 17;
int N, M, A[SZ];
int tree[2 * SZ];

int init(int node, int start, int end);
void update(int node, int start, int end, int idx, int val);
int get_min(int node, int start, int end, int left, int right);

int main(int argc, char *argv[]) {
  open();

  N = readInt();
  for (int i = 1; i <= N; ++i) A[i] = readInt();
  init(1, 1, N);

  M = readInt();
  int a, b, c;
  while (M--) {
    a = readInt(), b = readInt(), c = readInt();;
    if (a == 1) {
      update(1, 1, N, b, c);
    } else {
      printf("%d\n", get_min(1, 1, N, b, c));
    }
  }
  return 0;
}

// 초기화 함수
int init(int node, int start, int end) {
  if (start == end) return tree[node] = A[start];
  int mid = (start + end) / 2;
  return tree[node] = min(init(node * 2, start, mid),
                          init(node * 2 + 1, mid + 1, end));
}

// 업데이트 함수
void update(int node, int start, int end, int idx, int val) {
  if (idx < start || end < idx) return;
  if (start == end) {
    tree[node] = val;
    return;
  }

  int mid = (start + end) / 2;
  update(node * 2, start, mid, idx, val);
  update(node * 2 + 1, mid + 1, end, idx, val);
  tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
}

// 구간 최솟값을 구해주는 함수
int get_min(int node, int start, int end, int left, int right) {
  if (end < left || right < start) return INF;
  if (left <= start && end <= right) return tree[node];
  int mid = (start + end) / 2;
  return min(get_min(node * 2, start, mid, left, right),
             get_min(node * 2 + 1, mid + 1, end, left, right));
}