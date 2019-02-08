/*
 *  BOJ 1981. 배열에서 이동
 * 
 *  시간복잡도 : O(n^2 * klogk)  ( k == 200 )
 *  공간복잡도 : O(n^2) 
 * 
 *  이분탐색으로 접근을 하는건 똑같은데, 그 값이 되는지, 안되는지 체크하는 방식을 
 *  어떻게 할 지를 고민하는데에서 너무 오래걸렸던 문제입니다.
 *  
 *  이분탐색을 해서 차이의 값을 정하고, 그 차이 내에서 (1, 1)에서 (n, n)으로 도달할 수 
 *  있는지를 확인하는데, 그냥 가능한 범위에서 모든 경우를 확인해도 되는 시간 범위인데 
 *  그걸 한 번의 BFS로 확인해보려고 하다가 메모리 초과도 나고 대환장파티였습니다. 
 */

#include <cstdio>
#include <queue>
#include <algorithm>
#define X first
#define Y second
using namespace std; 
typedef pair<int,int> pii;

const int MAX = 100;
const int move_r[4] = {-1, 0, 1, 0};
const int move_c[4] = {0, -1, 0, 1};
int a[MAX][MAX], n;

// 범위 내의 인덱스인지 확인하는 함수
bool check(int r, int c) { return r >= 0 && r < n && c >= 0 && c < n; }

// diff의 차이로 통과가 되는지 확인하는 함수
bool solve(int diff) {

  // diff 범위 내의 모든 [mn, mx]의 경우를 모두 확인
  for (int mn = a[0][0]; mn >= 0 && mn >= a[0][0] - diff; mn--) {
      int mx = mn + diff;
      queue <pii> q; q.push({0, 0});
      bool visited[MAX][MAX] = {1};

      // BFS!
      while (!q.empty()) {
          pii cur = q.front();
          q.pop();
          
          // (n, n)에 도달하면 바로 true를 리턴
          if (cur.X == n - 1 && cur.Y == n - 1) return true;
          
          for (int k = 0; k < 4; k++) {
              int dr = cur.X + move_r[k];
              int dc = cur.Y + move_c[k];
              if (check(dr, dc) && !visited[dr][dc] && mn <= a[dr][dc] && a[dr][dc] <= mx) {
                  visited[dr][dc] = true;
                  q.push({dr, dc});
              }
          }
      }
  }
  // 모든 경우를 확인했는데도 여기에 도달하면 불가능한 것이므로 false를 리턴
  return false;
}

int main(int argc, char *argv[]) {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) 
    for (int j = 0; j < n; ++j) 
      scanf("%d", &a[i][j]);

  // 이분탐색으로 차이의 최솟값을 탐색.
  int s = 0, e = 201, m;
  while (s < e) {
    m = (s + e) / 2;
    if (solve(m)) e = m;
    else s = m + 1;
  }

  return !printf("%d\n", solve(s) ? s : s + 1);
}

/*
 *  이 코드는 킹도킹님의 코드를 보고 비슷하게 짠 코드입니다.
 *  생각해보면 처음 위치와 도달 위치의 값의 차이가 가능한 가장 작은 값이죠. 
 *  그래서 그것을 한계선으로 정해두고, 작은 값보다 작은 left와 큰 값보다 큰 right를 두고, 
 *  그것에 대해서만 확인을 하는 것입니다.
 * 
 *  그렇게 함으로써 bfs를 덜 시행하게 되어서 시간이 짧아집니다.
 */

// #include <cstdio>
// #include <cstring>
// #include <queue>
// #include <vector>
// #include <algorithm>
// #define X first
// #define Y second
// using namespace std; 
// typedef pair<int,int> pii;

// const int MAX = 100;
// const int move_r[4] = {-1, 0, 1, 0};
// const int move_c[4] = {0, -1, 0, 1};
// bool visited[MAX][MAX], exists[201];
// int a[MAX][MAX], n;

// bool check(int r, int c) { return r >= 0 && r < n && c >= 0 && c < n; }

// bool solve(int lb, int ub) {
//   queue <pii> q; q.push({0, 0});
//   visited[0][0] = true;

//   int dr, dc, r, c;
//   while (!q.empty()) {
//     r = q.front().X;
//     c = q.front().Y;
//     q.pop();

//     for (int k = 0; k < 4; ++k) {
//       dr = r + move_r[k];
//       dc = c + move_c[k];
//       if (check(dr, dc) && !visited[dr][dc] && lb <= a[dr][dc] && a[dr][dc] <= ub) {
//         visited[dr][dc] = true;
//         q.push({dr, dc});
//       } 
//     }
//   }
  
//   return visited[n-1][n-1];
// }

// int main(int argc, char *argv[]) {
//   scanf("%d", &n);
//   for (int i = 0; i < n; ++i) 
//     for (int j = 0; j < n; ++j) {
//       scanf("%d", &a[i][j]);
//       exists[a[i][j]] = true;
//     }

//   vector <int> vec;
//   int llim = min(a[0][0], a[n-1][n-1]);
//   int rlim = max(a[0][0], a[n-1][n-1]);
//   for (int i = 0; i <= 200; ++i) {
//     if (exists[i]) vec.push_back(i);
//     if (i == llim) llim = vec.size() - 1;
//     if (i == rlim) rlim = vec.size() - 1;
//   }

//   int left = 0, right = rlim, ans = 2e9;
//   while (left <= llim && right < vec.size()) {
//     memset(visited, false, sizeof(visited));
//     if (solve(vec[left], vec[right])) {
//       ans = min(ans, vec[right] - vec[left]);
//       left++;
//     } else right++;
//   }
//   return !printf("%d\n", ans);
// }
