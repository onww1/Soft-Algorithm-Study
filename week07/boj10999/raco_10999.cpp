/*
 *  BOJ 10999. 구간 합 구하기2
 *
 *  시간복잡도 : O((M+K)logN)
 *
 *  세그먼트 트리와 lazy_propagation을 이용하여 특정 구간에 대한 query들을
 *  처리하였다. 간결하면서 이해가 잘 되도록 설명할 자신이 없다. 코드를 보며 설명을 읽거나
 *  https://www.acmicpc.net/blog/view/26 이 블로그를 참조하는 것이 best라 생각한다.
 */

#define fastio() ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <iostream>
using namespace std;
#define MXN 1000001
typedef long long ll;

int N, M, K;
ll tree[MXN * 4];// 세그트리이다.
ll lazy[MXN * 4];// 처리해야할 일을 담는다. 처리가 된 인덱스의 값은 0으로 초기화 된다.
ll a[MXN * 2];// 입력 받는 값의 배열이다.

/*
void init() {
	pli = 1;
	while (pli < N) pli *= 2;
	pli--;
	for (int i = 1; i <= N; i++) cin >> tree[pli + i];

	for (int i = pli; i >= 1; i--) tree[i] = tree[i * 2] + tree[i * 2 + 1];
}

위의 init은 모든 입력 값을 같은 레벨의 노드에 순서대로 집어 넣어서 세그먼트 트리를 구성하는 방법이다.
10 0 0
3 6 2 7 6 4 11 12 8 4
이것을 예로 트리를 만들면
깊이                                  tree
1                                      63                     
2                   51                                   12
3          18                33                 12                  0
4      9       9        10        23       12        0         0          0
5    3   6   2   7    6    4   11    12  8    4    0   0     0   0      0    0
이 된다. sum함수와 update함수를 단말노드 부터 루트로 올라가면서 처리를 하면 이런식으로 만들어도 상관이 없다.
하지만 lazy_propagation을 사용하여 특정 구간[l,r]의 값들을 모두 변경하려면 현재의 구간[s,e]가 [l,r]안에 포함 되는지
안 되는지를 파악하면 쉽게 풀 수 있다. 하지만 단말노드부터 처리 해버리면 맨 왼쪽 단말노드는 위치 l를 가지고 있고
맨 오른쪽 단말노드는 위치r을 가지고 있다. 이런식이면 구간[s,e]가[l,r]안에 포함 되는지 파악할 수 없다.
루트부터 파악한다면 루트는 항상 [1,N] = [s,e]구간의 합을 뜻한다. 그러면 [l,r]의 범위 안에 자기의 구간을 포함되는지
아닌지 파악하기가 수월하다. 그러므로 밑과 같이 init을 구현하는 것이 해답이다.

똑같은 예제로 트리를 만들면
깊이                                  tree
1                                      63
2                   24                                   39
3          11                13                 27                  12
4      9       2         7        6        15       12         8          4
5    3   6   0   0    0    0    0   0    4    11  0    0     0   0      0    0
이 된다. 이걸 [s,e]구간에 따라 트리를 그려보면

깊이                                  tree
1                                    [1,10]
2                  [1,5]                                [6,10]
3         [1,3]             [4,5]             [6,8]               [9,10]
4    [1,2]     [3,3]   [4,4]     [5,5]   [6,7]     [8,8]     [9,9]      [10,10]
5                               생                략
이 된다. 구간의 범위는 항상 짝수 일 수 없고 [3,3]같은 구간이 나온다. 그림을 통해 보듯이
루트부터 시작해 재귀적으로 계속 구간을 나누면서 처리하는 것이 편하다. 
*/

ll init(int idx, int s, int e) {
	if (s == e) return tree[idx] = a[s];
	else {
		int m = (e + s) / 2;
		// 자식을 idx * 2, idx * 2+1 이런식으로 찾을 수 있는 것은 완전이진트리를 가정하에 두고 할 수 있는 코드다. 
		return tree[idx] = init(idx * 2, s, m) + init(idx * 2 + 1, m + 1, e);
	}
}

void lazy_propagation(int s, int e, int idx) {
	// 0이면 처리해야 할 일이 없으므로 리턴
	if (lazy[idx] == 0) return;
	// 현재 인덱스의 일을 처리
	tree[idx] += (e - s + 1)*lazy[idx];
	// 단말노드가 아니면 자식이 있으므로 자식들에게 일을 전파
	if (s != e) {
		lazy[idx * 2] += lazy[idx];
		lazy[idx * 2 + 1] += lazy[idx];
	}
	// 현재 인덱스의 일은 처리했으므로 0으로 초기화
	lazy[idx] = 0;
}

ll sum(int idx, int s, int e, int l, int r) {
	// update를 하면서 특정 구간에서 리턴되어 현재 구간의 일을 처리 하지 않고 자식에게 처리해야 할 일을
	// 넘겨주지 못 한 경우가 있다. 그럴 때를 없애기 위해 lazy_propagation을 호출한다. 
	lazy_propagation(s, e, idx);
	if (e<s || l > e || r < s) return 0;
	
	// 범위 안에 들면 현 인덱스의 트리 값을 리턴하면 된다. 예를 들어
	// [1,3]구간의 합이 필요하면 [1,2]구간과 [3,3]구간의 합을 리턴하면 된다.
	if (l <= s && e <= r) return tree[idx];
	
	int m = (e + s) / 2;
	return sum(idx * 2, s, m, l, r) + sum(idx * 2 + 1, m + 1, e, l, r);
}

// l~r까지의 수에 diff값을 더한다. s와 e는 현재 함수의 구간이다.
void update(int s, int e, int idx, int l, int r, ll diff) {
	lazy_propagation(s, e, idx);
	// 밑의 코드 보다 lazy_propagation이 먼저 쓰인 이유는 종료되기 전에 현재 인덱스의 tree값을 갱신하고
	// 자식 노드에게 처리해야 할 일을 전파해야 하기 때문이다.
	if (e<s || e<l || r<s) return;

	if (l <= s && e <= r) {
		// l <= s && e <= r 조건을 만족하면 현재 인덱스에서 리턴된다. 현재 인덱스의 diff일을 처리하여 tree[idx]를 갱신하고
		// 현재 인덱스의 모든 자손들이 diff일을 처리해야하므로 일단 자식에게 diff일을 전파한다.
		// 그럼 나중에 자식이 손자에게 일을 전파해서 처리하게 된다.
		tree[idx] += (e - s + 1) * diff;
		// s==e가 같다는 뜻은 단말노드란 뜻이다. 단말노드의 자식은 없기 때문에 그것을 막기 위한 조건
		if (s != e) {
			lazy[idx * 2] += diff;
			lazy[idx * 2 + 1] += diff;
		}
		// 루트 부터 시작해서 특정 레벨에서 리턴할 수 있기 때문에 맨 위에서 lazy_propagation를 통해  
		return;
	}
	int m = (e + s) / 2;
	// 구간 나누기
	update(s, m, idx * 2, l, r, diff);
	update(m + 1, e, idx * 2 + 1, l, r, diff);
	// 자식이 전파 받은 일을 처리한 우에는 자식들의 합이 곧 부모의 값이므로 부모를 갱신해 준다.
	tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
}

int main() {
	fastio();
	cin >> N >> M >> K;
	for (int i = 1; i<=N; i++) {
		cin >> a[i];
	}
	init(1, 1, N);

	ll a, b, c, d;
	for (int i = 0; i < M + K; i++) {
		cin >> a >> b >> c;
		if (a == 1) {
			cin >> d;
			update(1, N, 1, b, c, d); // update
		}
		else cout << sum(1, 1, N, b, c) << '\n'; // sum
	}
	return 0;
}