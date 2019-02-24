/*
 *  BOJ 2094. 강수량
 * 
 *  시간 복잡도 : O((N + M) * logN)
 *  공간 복잡도 : O(N)
 * 
 *  세그먼트 트리로 구간의 최댓값을 관리하고, 또한 lower_bound를 통해서 연도의 인덱스를 찾아서 
 *  주어진 구간 사이의 모든 연도의 정보가 있는지도 확인합니다. 
 * 
 *  그렇게 얻은 정보들을 잘 조합해서 이것이 true인지 false인지 확인하고 나머지 경우는 maybe로 출력합니다.
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

const int SZ = 1 << 16;
int N, M, Y[SZ], A[SZ], tree[2 * SZ];

int init(int node, int start, int end);
int get_max(int node, int start, int end, int left, int right);

int main(int argc, char *argv[]) {
  N = readInt();
  for (int i = 0; i < N; ++i) {
    Y[i] = readInt();
    A[i] = readInt();
  }
  init(1, 0, N - 1); // 세그먼트 트리 만들기

  M = readInt();
  while (M--) {
    int y = readInt(), x = readInt();
    int yidx = lower_bound(Y, Y + N, y) - Y;  // y에 대한 index
    if (yidx == N || Y[yidx] != y) yidx--;
    int xidx = lower_bound(Y, Y + N, x) - Y;  // x에 대한 index
    int mx = get_max(1, 0, N - 1, yidx + 1, xidx - 1); // 사이 구간에 대한 최댓값
    
    bool y_valid = !(yidx == -1 || Y[yidx] != y);
    bool x_valid = !(xidx == N || Y[xidx] != x);
    if (y_valid && x_valid && x - y == xidx - yidx && A[yidx] >= A[xidx] && 
        mx < A[xidx])
        puts("true");
    else if ((x_valid && y_valid && A[yidx] < A[xidx]) ||
             (x_valid && mx >= A[xidx]) ||
             (y_valid && mx >= A[yidx]))
        puts("false");
    else
        puts("maybe");
  }
  
  return 0;
}

// 초기화 함수
int init(int node, int start, int end) {
  if (start == end) return tree[node] = A[start];
  int mid = (start + end) / 2;
  return tree[node] = max(init(node * 2, start, mid),
                          init(node * 2 + 1, mid + 1, end));
}

// 구간 최댓값을 구하는 함수
int get_max(int node, int start, int end, int left, int right) {
  if (end < left || right < start) return 0;
  if (left <= start && end <= right) return tree[node];
  int mid = (start + end) / 2;
  return max(get_max(node * 2, start, mid, left, right),
             get_max(node * 2 + 1, mid + 1, end, left, right));
}