#include <cstdio>
using namespace std;

int a[10050], n;
void solve(int s, int e) {
  if (s >= e) return;
  int l = s + 1, r = e;
  while (l < r) {
    int m = (l + r) / 2;
    if (a[m] > a[s]) r = m;
    else l = m + 1;
  }
  solve(s + 1, r);
  solve(r, e);
  printf("%d\n", a[s]);
}

int main(int argc, char *argv[]) {
  while (~scanf("%d", &a[n++]));
  solve(0, n-1);
  return 0;  
}