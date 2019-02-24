/*
 *  BOJ 1275. 커피숍 2 
 * 
 *  시간 복잡도 : O((N + Q) * logN)
 *  공간 복잡도 : O(N)
 * 
 *  세그먼트 트리의 전형적인 문제라고 생각될 수 있는 문제네요. (전 펜윅트리)
 *  각 쿼리마다 구간 합도 구하고, 값 변경도 하니까 세그먼트리가 절실한 문제에요. 
 * 
 *  이 문제에서 함정은 구간이 무조건 x < y인 x, y가 주어지지 않는다는 것이죠. 
 *  이 점만 주의하면 무난하게 풀 수 있는 문제였습니다.
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

const int MAX = 1e5;
int N, Q;
ll A[MAX + 1], tree[MAX + 1];

void update(int node, ll diff);
ll sum(int node);
void swap(int &a, int &b);

int main(int argc, char *argv[]) {
  N = readInt(), Q = readInt();
  for (int i = 1; i <= N; ++i) {
    A[i] = readLL();
    update(i, A[i]);
  }

  int x, y, a; ll b;
  while (Q--) {
    x = readInt(), y = readInt();
    a = readInt(), b = readLL();
    if (x > y) swap(x, y);
    printf("%lld\n", sum(y) - sum(x - 1));
    update(a, b - A[a]);
    A[a] = b;
  }
  
  return 0;
}

// 업데이트 함수
void update(int node, ll diff) {
  while (node <= MAX) {
    tree[node] += diff;
    node += node & -node;
  }
}

// 1 ~ node 까지 합을 구하는 함수
ll sum(int node) {
  ll ret = 0;
  while (node > 0) {
    ret += tree[node];
    node -= node & -node;
  }
  return ret;
}

// SWAP!
void swap(int &a, int &b) {
  int tmp = a;
  a = b;
  b = tmp;
}