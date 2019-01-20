// dp의 현재 인덱스를 mi라고 하겠다. mi는 0부터 시작하며, dp[0]에 arr[0]값을 넣고
// dp[mi]와 arr[i]를 비교한다. (i는 1부터 N과 같을 때까지 1씩 증가)
// arr[i]값이 더 크면 mi의 값을 1증가시켜주고 dp[mi]에 arr[i]값을 넣어준다.
// arr[i]값이 작거나 같다면 오름차순으로 정렬되어 있는 dp에 arr[i]의 자리를
// lower_bound로 찾아서 넣어준다. 이렇게 하는 이유는 큰 값을 더 작은 값으로 바꾸기 위해서다
// 예를 들어 dp에 4, 7 이 있다고 하고 5가 들어오면 7값은 5로 바뀐다.
// 그러면 4, 5가 되고 이후에 6이 들어오면 6을 dp에 넣어 4,5,7로 길이를 증가시킬 수 있다.
// 그러면 dp의 가장 큰 값만 바꾸어 주면 되는거 아니냐라고 생각 할 수 있다.
// 또 한 가지 예로 dp에 4, 7이 있는데 1이 들어오면 4, 7은 1, 7로 바뀌고
// 2가 들어오면 1, 7은 1, 2로 바뀐다. 그리고 3이 들어오면
// 3을 dp에 넣어 1,2,3으로 바꿀 수 있다. 첫 번째 인덱스인 4를 1로 바꾸어
// 2번째 인덱스에 2를 넣었고, 마지막으로 세 번째 인덱스에 3을 넣어 길이를 증가시킬 수 있었다.

#include <iostream>
#include <algorithm>
using namespace std;

#define MXN 1001

int N;
int arr[MXN];
int dp[MXN];

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) cin >> arr[i];

	int mi = 0;// max_index
	dp[mi] = arr[0];
	for (int i = 1; i < N; i++) {
		if (dp[mi] < arr[i]) {
			mi++;
			dp[mi] = arr[i];
			continue;
		}
		// 밑의 코드를 통해 dp는 항상 오름차순으로 정렬되어 있다.
		// right_position
		int rp = lower_bound(dp, dp + mi, arr[i]) - dp;
		dp[rp] = arr[i];
	}
	cout << mi + 1 << '\n';
	return 0;
}