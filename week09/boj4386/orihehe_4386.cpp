/*
BOJ 4386 - 별자리 만들기

시간복잡도 : O(ElogE)
공간복잡도 : O(E)

MST 기본 문제 입니다.
크루스칼 알고리즘으로 별자리를 만드는 최소비용을 구해줄 수 있습니다.
*/
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#define pdd pair<double,double>
using namespace std;

/* 🐣🐥 */
struct node {
	double val;
	int v1, v2;
	bool operator < (const node &a) const {
		return val < a.val;
	}
};
int n;
double ans = 0;
int p[100];
vector<node> vec;
pdd arr[100];
double dd(pdd a, pdd b) { // 거리 구하기
	a.first -= b.first;
	a.second -= b.second;
	return sqrt(a.first*a.first + a.second*a.second);
}
int getR(int a) { // 루트 구하기
	if (p[a] == a) return a;
	return p[a] = getR(p[a]);
}
void merge(int a, int b) { // 같은 그룹으로 만들어주기
	a = getR(a), b = getR(b);
	p[a] = b;
}
double kru() {
	double ret = 0;
	// 각각의 부모를 자기자신으로
	for (int i = 0; i < n; i++) p[i] = i;
	sort(vec.begin(), vec.end()); // 가중치 적은 순으로 정렬
	for (node v : vec) {
		// 이미 같은 그룹이라면 간선을 선택하지 않는다.
		if (getR(v.v1) == getR(v.v2)) continue;
		ret += v.val;
		merge(v.v1, v.v2);
	}
	return ret;
}
int main() {
	double a, b;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%lf %lf", &a, &b);
		arr[i] = { a,b };
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) continue;
			double x = dd(arr[i], arr[j]);
			vec.push_back({ x,i,j });
		}
	}
	printf("%lf", kru());

	return 0;
}