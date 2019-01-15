/*
 *  기본적인 아이디어는 문제 설명과 동일합니다.
 *  [ 0(딸기우유) 1(초코우유) 2(바나나우유) ]
 *  각각 0일 경우 이전의 2, 2일 경우 이전의 1, 1일 경우 이전의 0의 dp값들을 확인하여 최대값+1을 줬습니다.
 *  여기서 주의할 점은 무조건 0(딸기우유)부터 마셔야한다는 점입니다.
 *  따라서 0(딸기우유)를 가진 가게의 값이 0인 경우만 1로 초기화를 시켜주고
 *  이전의 dp값들을 확인할 때 0으로 되어있는 경우는 값을 갱신하지 않는 조건을 넣어줬습니다.
 */
 
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
