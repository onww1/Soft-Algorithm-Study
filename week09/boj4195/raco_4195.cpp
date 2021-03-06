/*
 *  BOJ 4195. 친구 네트워크
 *
 *  시간복잡도 : O(NlogN)
 * 
 *  기본적인 union-find를 이용하여 친구 간의 관계를 트리로
 *  만들어 주면 된다. 보통 각 정점은 숫자로 주어지는데 여기서는
 *  사람의 이름으로 주어 졌으므로 사람의 이름에 따라 gc(global_count)를
 *  통해 번호를 할당하고 map에 담아 logN에 해당 사람의 번호를 찾았다.
 *  
 */

#pragma warning(disable:4996)
#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <map>
#include <string>
using namespace std;
#define MXN 100002

int N;
map<string, int> mp;
int gc;
int par[MXN * 2];
int cnt[MXN * 2];

int find(int u) {
	if (u == par[u]) return u;
	return par[u] = find(par[u]);
}

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

int merge(int a, int b) {
	a = find(a), b = find(b);
	// 같은 트리에 있으면 a나 b중 하나의 개수만 리턴하면 된다.
	if (a == b) return cnt[a];
	// 같은 트리 없으면 a가 루트이니 cnt[b]의 값을 cnt[a]에 합치고 리턴하면 된다.
	if (cnt[a] < cnt[b]) swap(a, b);
	par[b] = a;
	cnt[a] += cnt[b];
	return cnt[a];
}

int main() {
	fastio();
	int TC;
	cin >> TC;
	string a, b;
	while (TC--) {
		cin >> N;
		gc = 0;
		for (int i = 0; i < MXN * 2; i++) par[i] = i, cnt[i] = 1;
		for (int i = 0; i < N; i++) {
			cin >> a >> b;
			// 각 사람의 이름에 대한 번호 할당
			if (mp.count(a) == 0) mp[a] = ++gc;
			if (mp.count(b) == 0) mp[b] = ++gc;
			cout << merge(mp[a], mp[b]) << '\n';
		}
	}
	return 0;
}