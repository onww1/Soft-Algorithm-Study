/*
BOJ 15678 - 연세워터파크

시간복잡도 : O(NlogN)
공간복잡도 : O(1)

pq에 현재 징검다리를 밟았을 때 점수, 인덱스 를 넣어줍니다.
i번째 징검다리를 밟을 때 만약 pq의 top이 음수라면, 현재 값만을 pq에 넣어줍니다.
그렇지 않다면 top값+현재값을 넣어줍니다.

세그먼트 트리로 푸는 방법은 i-d~i-1 구간의 최댓값을 가져와서 
같은 방식으로 생각하여 i번째에 업데이트를 해주면 될 것 같습니다.
*/
#include <cstdio>
#include <queue>
#define ll long long
#define pli pair<ll,int>
using namespace std;

/* 🐣🐥 */
priority_queue<pli> pq;
int main() {
	int n, d;
	ll mV, x;
	scanf("%d %d", &n, &d);
	scanf("%lld", &x);
	pq.push({ x,0 });
	mV = x;
	for (int i = 1; i < n; i++) {
		scanf("%lld", &x);
		while (pq.top().second < i - d) {
			pq.pop();
		}
		if (pq.top().first < 0) pq.push({ x,i });
		else pq.push({ pq.top().first + x,i });
		mV = max(mV, pq.top().first);
	}
	printf("%lld", mV);

	return 0;
}