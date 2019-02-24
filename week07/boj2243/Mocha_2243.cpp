/*
 *  BOJ 2243. 사탕상자 
 * 
 *  시간 복잡도 : O(N(logK)^2)  (K : 100만)
 *  공간 복잡도 : O(K) 
 * 
 *  인덱스 트리로 1부터 100만까지의 배열에 사탕의 종류별로 몇개씩 있는지를 관리하고, 
 *  그것을 이분탐색으로 찾아나가서 해당되는 사탕의 인덱스를 출력하는 것이었습니다.
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

const int MAX = 1e6;
int N, tree[MAX + 1];

void update(int node, int diff);
int sum(int node);

int main(int argc, char *argv[]) {
  N = readInt();
  int a, b, c;
  while (N--) {
    a = readInt(), b = readInt();
    if (a == 1) {
      int l = 1, r = MAX, m, s, ans = 1;
      while (l <= r) {  // 이분탐색으로 해당되는 사탕을 찾음
        m = (l + r) / 2;
        s = sum(m);
        if (s >= b) r = m - 1, ans = m;
        else l = m + 1;
      }
      printf("%d\n", ans);
      update(ans, -1);
    } else {
      c = readInt();
      update(b, c);
    }
  }
  
  return 0;
}

// 업데이트 함수
void update(int node, int diff) {
  while (node <= MAX) {
    tree[node] += diff;
    node += node & -node;
  }
}

// 1 ~ node 까지의 합을 구하는 함수
int sum(int node) {
  int ret = 0;
  while (node > 0) {
    ret += tree[node];
    node -= node & -node;
  }
  return ret;
}