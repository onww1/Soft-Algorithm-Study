#include <iostream>
#include <algorithm>

using namespace std;

int main(void){
    int arr[1002] = {0}; // 무슨 우유인지 받을 배열
    int dp[1002] = {0};
    int n;
    cin >> n;

    for (int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < n; i++){
        if (dp[i] == 0 && arr[i] == 0){
            dp[i] = 1;
            // 가장 먼저 딸기우유를 마셔야 한다. (예외1)
            // 따라서 dp가 0이지만 arr도 0일 경우만 1로 만들어준다.
        }
        for (int j = i - 1; j >= 0; j--){
            if (dp[j] != 0){
            // 가장 먼저 딸기우유를 마셔야한다.(예외1)
            // 따라서 아무리 이전 순서인 우유가 있어도 딸기우유가 나오기 전에는
            // 먹지 못한다.(예외2)
                if (arr[i] == 2){
                    if (arr[j] == 1){
                        dp[i] = max(dp[i], dp[j] + 1);
                    }
                }
                else if (arr[i] == 1){
                    if (arr[j] == 0){
                        dp[i] = max(dp[i], dp[j] + 1);
                    }
                }
                else{
                    if (arr[j] == 2){
                        dp[i] = max(dp[i], dp[j] + 1);
                    }
                }
            }
        }
    }
    int result = 0;
    for (int i = 0; i < n; i++){
        // printf("%d ", dp[i]);
        result = max(result, dp[i]);
    }
    // cout << endl;
    cout << result << endl;
}
