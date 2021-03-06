/*
 *  BOJ 6549. 히스토그램에서 가장 큰 직사각형
 *
 *  시간복잡도 : O(N)
 *  시간복잡도는 stack에 들어가는 값의 개수가 최대 N이고
 *  pop하는 것의 개수가 N이므로 O(N)인 것을 알 수 있다.
 *  
 *  stack에 계속 순서대로 직사각형을 넣으면서 현재(i)의 직사각형의 높이
 *  가 stack.top()에있는 것 보다 더 낮을 때는 스택 pop하여 빠져나온 
 *  직사각형의 높이 h를 기준으로 하고 너비는 i와 stack.top()의 인덱스의 차이로
 *  하여 직사각형을 계산해 더 큰 값을 ret에 집어 넣는다. 이 때 빠져나온
 *  직사각형 h보다 높이가 큰 직사각형은 stack에 없다. h가 스택에 들어가기 전에
 *  h보다 큰 직사각형은 모두 스택에서 빠져나가면서 계산되었기 때문이다.
 *  이렇게 한 이유는 현재 값보다 큰 직사각형은 stack에서 빼면 스택에는
 *  h 높이 보다 낮은 직사각형만 스택에 담겨져 있을 테고, 너비를
 *  너비를 i와 stack.top()읜 인덱스로 간단하게 구할 수 있다. 
 *  h와 stack.top() 사이에는 h보다 큰 직사각형만 있다는 뜻이다.
 *  
 */
#define fastio() ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#include <iostream>
#include <stack>
using namespace std;
#define MXN 100001
typedef long long ll;

int N;
ll het[MXN + 1];// height
stack<ll> st;

ll max(ll a, ll b) {
	return a > b ? a : b;
}

int main() {
	fastio();
	while (1) {
		cin >> N;
		while (!st.empty()) st.pop();
		if (N == 0) break;
		// 0~N-1의 인덱스를 사용하여 직사각형 담는다.
		for (int i = 0; i < N; i++) cin >> het[i];
		// 1 2 3 4 5 6 0이 되어서 모든 직사각형은 0보다 작을 수는 없으니
		// while (!st.empty() && het[st.top()] >= het[i])여기서 계산 되게 하기
		// 위해서 인덱스 N에 0을 집어 넣었다.
		het[N] = 0;
		ll ret = 0;
		for (int i = 0; i <= N; i++) {
			while (!st.empty() && het[st.top()] >= het[i]) {
				ll j = st.top();
				st.pop();
				ll width;
				if (st.empty()) width = i;
				else width = (i - st.top() - 1);
				ret = max(ret, het[j] * width);
			}
			st.push(i);
		}
		cout << ret << '\n';
	}
	return 0;
}