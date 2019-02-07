/*
BOJ 1981 - �迭���� �̵�

�ð����⵵ : O(N^2*KlogK) ?    n^2-dfs �� mid���� k��, logk-�̺�Ž��, k=200
�������⵵ : O(N^2)

mid ���� �ִ񰪰� �ּڰ��� ���̷� �����մϴ�.
�迭�� �� ���� 0<=x<=200 �� �����̹Ƿ� 0~0+mid, 1~1+mid ... �� ���� �ȿ� �ִ� ���鸸 �湮�Ͽ�
1,1���� n,n�� ������ �� �ִ��� dfs�� �˻����ݴϴ�.
n,n�� ���� �ߴٸ� mid���̷� �̵��� �� �����Ƿ� r=mid-1�� ���� mid���� �ٿ��ְ�,
�������� ���ߴٸ� l=mid+1�� ���� mid���� �÷��ݴϴ�.
*/
#include <cstdio>
#include <cstring>
using namespace std;

int rgo[4] = { 0,-1,0,1 };
int cgo[4] = { 1,0,-1,0 };
bool visited[101][101], suc;
int b[101][101];
int n, l, r, mid, ans, mx, mn;
void dfs(int r, int c) {
	// mn~mx������ ����ٸ� return
	if (b[r][c] > mx || b[r][c] < mn) { 
		return;
	}
	visited[r][c] = true;
	if (r == n - 1 && c == n - 1) { // ����
		suc = true; return; // suc������ ���������� ǥ��
	}
	for (int i = 0; i < 4; i++) {
		int nr = r + rgo[i], nc = c + cgo[i];
		// �̹� �湮�߰ų�, ���� ���̶��
		if (visited[nr][nc] || nr >= n || nr < 0 || nc < 0 || nc >= n) continue;
		if (suc) return; // �����ߴٸ� return
		dfs(nr, nc);
	}
}
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			scanf("%d", &b[i][j]);
	}
	l = 0; r = 200;
	while (l <= r) {
		mid = (l + r) / 2;
		suc = false;
		// i~i+mid ������ ���鸸 �湮�Ͽ� ������ �� �ִ���
		for (int i = 0; i + mid <= 200; i++) {
			memset(visited, false, sizeof(visited));
			mx = i + mid; mn = i;
			dfs(0, 0);
			if (suc) break; // �����ߴٸ� �� �� �ʿ� ����
		}
		if (suc) {
			r = mid - 1;
			ans = mid;
		}
		else {
			l = mid + 1;
		}
	}
	printf("%d", ans);

	return 0;
}