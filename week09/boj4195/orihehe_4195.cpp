/*
BOJ 4195 - 친구 네트워크

시간복잡도 : O(TNlogN)
공간복잡도 : O(N)

이름을 맵에서 관리하며 인덱스를 부여해줍니다.
유니온 파인드로 같은 집합내의 인원 수를 구해줍니다.
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

/* 🐣🐥 */
int p[200001], h[200001];
map<string, int> m;
// 가장 윗 부모 구해주기
int getR(int a) {
	if (p[a] == a) return a;
	return p[a] = getR(p[a]);
}
// 같은 그룹으로
void merge(int a, int b) {
	a = getR(a), b = getR(b);
	if (a == b) return;
	p[a] = b;
	h[b] += h[a];
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int t, n, cnt;
	string f, s;
	cin >> t;
	while (t--) {
		m.clear();
		cnt = 0;
		cin >> n;
		for (int i = 0; i <= 2*n; i++) {
			p[i] = i;
			h[i] = 1;
		}
		while (n--) {
			cin >> f >> s;
			// f가 아직 등록되지 않았다면
			if (m.find(f) == m.end()) {
				m[f] = cnt++;
			}
			if (m.find(s) == m.end()) {
				m[s] = cnt++;
			}
			// 같은그룹으로 만들어주기
			merge(m[f], m[s]);
			cout << h[getR(m[f])] << "\n";
		}
	}

	return 0;
}