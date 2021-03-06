#include <iostream>
using namespace std;
#define MXN 1000001
typedef long long ll;

int N, M, K;
// N이 5라고 한다면 16개의 배열공간이 필요하다.
// 최대 가능한 N값의 4배의 배열공간이면 런타임 에러를
// 피할 수 있다.
ll tree[MXN * 4];
int pli;// parent_last_index 부모 노드 중에 가장 인덱스가 큰 값을 저장한다.

void init() {
	pli = 1;// root는 1부터 시작한다.
	while (pli < N) pli *= 2;
	pli--;
	// 왼쪽 노드부터 오른쪽으로 차례대로 값을 입력받는다.
	for (int i = 1; i <= N; i++) cin >> tree[pli + i];
	// 위에서 얻은 단말 노드 정보를 통해 부모의 값을 갱신시킨다.
	for (int i = pli; i >= 1; i--) tree[i] = tree[i * 2] + tree[i * 2 + 1];
}
//                          15 
//           10                           5
//     3             7             5             0
//  1      2      3      4      5      0      0      0
// 예제를 예로 들면 위와 같은 트리가 구성된다.
// s가 2이고 e가 5이면 ret = 2+3+4+5를 가 되어 14가 된다.
// s의 인덱스가 홀수이면 ret에 더해주고, e의 인덱스가 짝수면
// ret에 더해주고 s에 (s+1)/2를 넣는다. e에 (e-1)/2를 넣는다.
// s가 짝수이면 s뿐 아니라 s+1도 ret에 포함되어야 한다. s = (s + 1) / 2;
// 해서 부모의 인덱스도 짝수면 부모의 부모가 이 부모 값을 포함한다는 뜻이다.
// 이렇게 s의 값을 거의 1/2로 줄여가며 홀수가 되면 ret에 더해준다.
// s가 홀수가 되었다는 것은 이 s-1은 구간 합에 포함되지 말아야 한다는 소리이고
// 이 s의 조상들은 볼 필요가 없어졌다는 뜻이므로 (s+1)/2의 조상을 보면서
// 이 과정을 반복하면 된다.
// e는 끝 인덱스라는 점만 생각하고 s와 같은 방식으로 처리하면 된다.
ll sum(int s, int e) {
	ll ret = 0;
	s += pli;
	e += pli;
	while (s <= e) {
		if (s % 2 == 1) ret += tree[s];
		if (e % 2 == 0) ret += tree[e];
		s = (s + 1) / 2;
		e = (e - 1) / 2;
	}
	return ret;
}

// 바꾸어야 하는 단말노드의 값과 바꿀 숫자의 값의 차이(diff)를 구해 단말 노드부터
// 시작하여 이 단말 노드를 자손으로 갖는 모든 노드에 그 차이만큼 더해준다.
void update(int idx, ll chg) {// 바꿔야 할 순서의 인덱스 index, 바꿀 숫자 change
	idx += pli;
	ll diff = chg - tree[idx];
	while (idx) {
		tree[idx] += diff;
		idx /= 2;
	}
}

int main() {
	cin >> N >> M >> K;
	init();

	ll a, b, c;
	for (int i = 0; i < M + K; i++) {
		cin >> a >> b >> c;
		if (a == 1) update(b, c); // update
		else cout << sum(b, c) << '\n'; // sum
	}
	return 0;
}
