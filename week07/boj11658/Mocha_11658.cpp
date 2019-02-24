/*
 *  BOJ 11658. 구간 합 구하기 3
 * 
 *  시간 복잡도 : O((N + M) * (logN)^2)
 *  공간 복잡도 : O(N^2)
 * 
 *  2D 펜윅트리 문제였습니다. 
 *  2D 세그먼트 트리도 가능한지는 모르겠지만 어떻게 구현해야 할지 모르겠어서..
 * 
 *  2D 펜윅트리는 1D 펜윅트리를 나머지 차원에 대해서도 똑같이 적용해주는 것입니다.
 *  1D 펜윅트리가 여러개 있고, 그것들을 하나의 item으로 생각하여 그것을 1D 배열로 생각하고,
 *  그 배열에 대하여 펜윅트리를 똑같이 적용하는 것입니다. 
 * 
 *  그렇게 하면 이러한 2D 배열에 대한 구간합 구하는 것도 간단해지죠!
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

const int MAX = 1024; 
int N, M, A[MAX + 1][MAX + 1], tree[MAX + 1][MAX + 1];

void update(int x, int y, int diff);
int sum(int x, int y);

int main(int argc, char *argv[]) {
  N = readInt(), M = readInt();
  for (int i = 1; i <= N; ++i) 
    for (int j = 1; j <= N; ++j) {
      A[i][j] = readInt();
      update(i, j, A[i][j]);  // 인풋으로 바로 업데이트함으로써 초기화
    }
  
  int w, x, y, xx, yy;
  while (M--) {
    w = readInt();
    if (w) {
      x  = readInt(), y  = readInt();
      xx = readInt(), yy = readInt();
      printf("%d\n", sum(xx, yy) - sum(xx, y - 1) - sum(x - 1, yy) + sum(x - 1, y - 1));
    } else {
      x = readInt(), y = readInt(), xx = readInt();
      update(x, y, xx - A[x][y]);
      A[x][y] = xx;
    }
  }

  return 0;
}

// 업데이트 함수
void update(int x, int y, int diff) {
  while (x <= N) {
    int yy = y;
    while (yy <= N) {
      tree[x][yy] += diff;
      yy += yy & -yy;
    }
    x += x & -x;
  }
}

// 구간 합을 구하는 함수
int sum(int x, int y) {
  int ret = 0;
  while (x > 0) {
    int yy = y;
    while (yy > 0) {
      ret += tree[x][yy];
      yy -= yy & -yy;
    }
    x -= x & -x;
  }
  return ret;
}