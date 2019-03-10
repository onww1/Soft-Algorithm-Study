/*
 * 일단 코드 올립니다 !
*/
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int main(void) {
	int T;
	cin >> T;
	for (int test_case = 1, k, m, p; test_case <= T; test_case++) {
		scanf("%d %d %d", &k, &m, &p);
		vector<int> edges[1001];
		int indegree[1001] = { 0 };
		int r[1001] = { 0 };
		int c[1001] = { 0 };
		int result = 0;

		for (int i = 0, a, b; i < p; i++) {
			scanf("%d %d", &a, &b);
			edges[a].push_back(b);
			indegree[b]++;
		}
		queue<int> myQ;
		for (int i = 1; i <= m; i++) {
			if (indegree[i]==0) {
				r[i] = 1;
				myQ.push(i);
			}
		}
		while (!myQ.empty()) {
			int cur = myQ.front();
			myQ.pop();
			if (c[cur] > 0) r[cur]++;
			result = max(r[cur], result);
			for (int i = 0; i < edges[cur].size(); i++) {
				if (r[edges[cur][i]] < r[cur]) {
					r[edges[cur][i]] = r[cur];
					c[edges[cur][i]] = 0;
				}
				else if (r[edges[cur][i]] == r[cur]) {
					c[edges[cur][i]]++;
				}
				indegree[edges[cur][i]]--;
				if (!indegree[edges[cur][i]]) {
					myQ.push(edges[cur][i]);
				}
			}
		}
		printf("%d %d\n", test_case, result);
	}
}
