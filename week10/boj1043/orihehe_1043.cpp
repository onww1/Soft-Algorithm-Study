/*
BOJ 1043 - 거짓말

시간복잡도 : O(NM)
공간복잡도 : O(NM)

먼저 진실을 아는 사람을 모두 큐에 넣습니다.
큐에서 하나씩 봐주면서 현재 사람이 속한 파티의 사람을 모두 진실을 아는 사람으로 생각하여
새로 진실을 아는 사람을 다시 큐에 넣는 식으로 탐색을 해준 뒤
진실을 모르는 사람으로만 구성된 파티 수를 세줍니다.
*/
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

/* 🐣🐥 */
bool w[51];
vector<int> p[51];
int main() {
	queue<int> q;
	int n, m, x, k, cnt = 0;
	scanf("%d %d %d", &n, &m, &k);
	for (int i = 0; i < k; i++) {
		scanf("%d", &x);
		w[x] = true;
		q.push(x);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d", &k);
		for (int j = 0; j < k; j++) {
			scanf("%d", &x);
			p[i].push_back(x);
		}
	}
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < m; i++) {
			for (int v : p[i]) {
				// 진실을 아는 현재 사람이 파티에 있을 때
				if (v == cur) {
					for (int vv : p[i]) {
						// 진실을 몰랐던 사람을 큐에 넣어준다.
						if (!w[vv]) {
							q.push(vv);
							w[vv] = true;
						}
					}
					break;
				}
			}
		}
	}
	for (int i = 0; i < m; i++) {
		bool suc = true;
		for (int v : p[i]) {
			if (w[v]) {
				suc = false;
				break;
			}
		}
		// 모든 이가 진실을 모를 때
		if (suc) cnt++;
	}
	printf("%d", cnt);

	return 0;
}