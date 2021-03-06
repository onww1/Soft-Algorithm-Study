/*
 *  BOJ 1654. 랜선 자르기
 *  
 *  시간복잡도 : O(Klog(2^31-1))
 *  공간복잡도 : O(K)
 * 
 *  lan배열에 모든 랜선 길이를 담습니다. 이분 탐색의 처음 인덱스
 *  1, 끝 인덱스 2^31-1로 설정하여 mid값을 구합니다. mid값으로
 *  모든 lan배열 원소들을 나눈 값의 합(길이 mid인 랜선의 개수)을 구해 
 *  그 합이 N보다 크다면 ans값과 비교해 더 큰 값을 ans에 갱신합니다.
 *  이 과정을 이분탐색이 끝날 때 까지 반복하여 ans를 구합니다.
 * 
 */

#include <iostream>
using namespace std;
#define MXN 10002
typedef long long ll;

int N, M;
ll lan[MXN];

ll get_cnt(ll v) {
	ll cnt = 0;
	for (int i = 0; i < N; i++) {
		cnt += (lan[i] / v);
	}
	return cnt;
}

ll max(ll a, ll b) {
	return a > b ? a : b;
}

ll bs(ll s, ll e) {
	ll ans = 0;
	while (s <= e) {
		ll m = (e + s) / 2;
		if (M <= get_cnt(m)) {
			ans = max(m, ans);
			s = m + 1;
		}
		else e = m - 1;
	}
	return ans;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> lan[i];
	}
	// e값의 최대값은 2^31-1 == 2147483647이다. 하지만 bs를 통해
	// mid값을 구할 때 자료형을 int로 한다면 e+s에서 오버플로우 
	// 의도치 않은 값이 발생한다.
	// s값을 1이 아닌 0으로 주는 실수를 했다.
	// 이 값을 0으로 두면 bs의 m값이 0이 될 경우가 생길 수 있고
	// 이 값은 get_cnt함수에서 분모가 되는 경우가 발생한다. 주의!
	cout << bs(1, 2e10) << '\n';
	return 0;
}