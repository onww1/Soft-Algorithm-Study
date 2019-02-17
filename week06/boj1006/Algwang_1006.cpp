#include<iostream>
#include<algorithm>

using namespace std;

#define MAX 987654321;

int dp[10002][2];
int memory[10002][2];

int myDP(int n,int w,int idx, int type) {
	if (idx >= n) return 0;

	int& ret = memory[idx][type];
	if (ret != -1) return ret; // 이미 특수부대가 있음
	if (idx == n - 1) { // 끝에 도달
		if (type == 0) { // 안쪽이라면
			if (dp[n - 1][0] + dp[n - 1][1] <= w) { //바깥쪽과의 합이 w보다 작으면
				return 1; // 특수부대 1개 배치
			}
			return 2; // 아니면 2개 배치
		}
		else if (type == 1) { // 바깥쪽이라면
			return 1; // 1개 배치하고 끝
		}
	}
	ret = MAX;
	// 이제 끝이 아닌 경우
	if (type == 0) { // 안쪽이라면
		if (dp[idx][0] + dp[idx][1] <= w) { // 바깥쪽과의 합이 w보다 작다면
			ret = min(ret, 1 + myDP(n, w, idx + 1, 0)); // 다음 안쪽을 따져준다.
		}
		if (dp[idx][0] + dp[idx + 1][0] <= w) { // 바깥쪽과의 합이 w보다 작지 않고 다음 안쪽과의 합이 w보다 작다면
			if (dp[idx][1] + dp[idx + 1][1] <= w) { // 바깥쪽과 다음 바깥쪽의 합을 한번 더 확인
				ret = min(ret, 2 + myDP(n, w, idx + 2, 0)); // 이 경우는 안쪽-다음안쪽 바깥쪽-다음바깥쪽 이므로 특수부대 2개 배치하고 2칸 건너 뛰기
			}
			ret = min(ret, 2 + myDP(n, w, idx + 1, 1)); // 특수부대 1개 배치하고 다음 바깥쪽으로 건너 뛰기
		}
		ret = min(ret, 1 + myDP(n, w, idx, 1)); // 모든 경우에 해당하지 않으므로 내 칸에 특수부대 1개 배치하고 바깥쪽 보기
	}
	else if (type == 1) { // 바깥쪽도 안쪽과 마찬가지로 확인
		if (dp[idx][1] + dp[idx + 1][1] <= w) { // 안쪽은 이미 거치고 왔으므로 다음 바깥쪽과의 합을 확인
			if (dp[idx + 1][0] + dp[idx + 2][0] <= w) { // 만약 다음 안쪽과 그 다음 안쪽의 합이 w보다 작다면
				ret = min(ret, 2 + myDP(n,w,idx + 2, 1)); // 2개를 배치하고 다다음 바깥쪽을 본다.
			}
			ret = min(ret, 2 + myDP(n,w,idx + 2,0)); // 아니면 내 칸과 다음 안쪽에 각각 특수부대를 1개씩 배치하고 다다음 안쪽을 본다.
		}
		ret = min(ret, 1 + myDP(n, w, idx + 1, 0)); // 모두 아닐 경우 내 칸에 배치하고 다음 안쪽으로 점프!
	}
	return ret;
}
int main(void) {
	int T;
	cin >> T;
	for (int test_case = 0,n,w; test_case < T; test_case++) {
		fill_n(&dp[0][0], 10002 * 2, 0);
		fill_n(&memory[0][0], 10002 * 2, -1);
		int result = MAX;
		scanf("%d %d", &n, &w);
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &dp[j][i]);
			}
		}
		result = min(result, myDP(n,w,0, 0));

		int start0 = dp[0][0];
		int start1 = dp[0][1];
		int end0 = dp[n - 1][0];
		int end1 = dp[n - 1][1];

		if (n == 1) {
			printf("%d\n", result);
			continue;
		}
		fill_n(&memory[0][0], 10002 * 2, -1);
		if (dp[0][0] + dp[n - 1][0] <= w && dp[0][1] + dp[n - 1][1] <= w) {
			dp[0][0] = dp[n - 1][0] = dp[0][1] = dp[n - 1][1] = MAX;
			result = min(result, myDP(n, w, 0, 0) - 2);
			dp[0][0] = start0;
			dp[0][1] = start1;
			dp[n - 1][0] = end0;
			dp[n - 1][1] = end1;
		}
		fill_n(&memory[0][0], 10002 * 2, -1);
		if (dp[0][0] + dp[n - 1][0] <= w) {
			dp[0][0] = dp[n - 1][0] = MAX;
			result = min(result, myDP(n, w, 0, 0) - 1);
			dp[0][0] = start0;
			dp[n - 1][0] = end0;
		}
		fill_n(&memory[0][0], 10002 * 2, -1);
		if (dp[0][1] + dp[n - 1][1] <= w) {
			dp[0][1] = dp[n - 1][1] = MAX;
			result = min(result, myDP(n, w, 0, 0) - 1);
			dp[0][1] = start1;
			dp[n - 1][1] = end1;
		}
		printf("%d\n", result);
	}
}
