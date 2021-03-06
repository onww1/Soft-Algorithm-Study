/*
 *  BOJ 4386. 별자리 만들기
 *
 *  시간복잡도 : O(N^2)
 *
 *  모든 별들 사이의 간선을 구한 뒤 크루스컬 알고리즘을 통해
 *  가장 작은 간선 부터 스패닝 트리를 만들면서 사이클이 생기면
 *  현재 간선을 무시하고 사이클이 생기지 않으면 현재 간선의 dist를
 *  ans에 누적하여 답을 구했다.
 * 
 *  사이클이 생기면 절대 답이 될 수 없다. 왜냐하면 사이클이 생겼다는 것은
 *  이미 별자리로 선택된 두 별의 거리를 구할 필요가 없는데 구하기 때문이다.
 *  
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
typedef pair<double, double> pi;
#define MXN 102

class Edge {
public:
	double dist, x, y;
	Edge() {}
	Edge(double _dist, double _x, double _y) : dist(_dist), x(_x), y(_y) {}
};

int N;// 0부터 N-1까지
pi star[MXN + 1];
vector<Edge> edge;
int par[MXN + 1];
int level[MXN + 1];

bool cmp(const Edge &a, const Edge &b) {
	return a.dist < b.dist;
}

double get_dist(pi a, pi b) {
	return sqrt((a.first - b.first)*(a.first - b.first) + (a.second - b.second)*(a.second - b.second));
}

int find(int u) {
	if (u == par[u]) return u;
	return par[u] = find(par[u]);
}

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

bool merge(int u, int v) {
	u = find(u), v = find(v);
	if (u == v) return false;
	if (level[u] > level[v]) swap(u, v);
	par[u] = v;
	if (level[u] == level[v]) level[v]++;
	return true;
}

int main() {
	fastio();
	cin >> N;

	for (int i = 0; i < N; i++) par[i] = i, level[i] = 1;

	for (int i = 0; i < N; i++) {
		cin >> star[i].first >> star[i].second;
		for (int j = 0; j < i; j++) {
			edge.push_back(Edge(get_dist(star[j], star[i]), j, i));
		}
	}

	sort(edge.begin(), edge.end(), cmp);

	double ans = 0.0;
	for (int i = 0; i < edge.size(); i++) {
		double dist = edge[i].dist;
		double u = edge[i].x;
		double v = edge[i].y;
		
		if (merge(u, v)) ans += dist;
	}
	cout << fixed;
	cout.precision(2);
	cout << ans << '\n';
	return 0;
}