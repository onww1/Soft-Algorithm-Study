/*
 *  이 문제는 부분 증가 수열을 확인하기 위해서
 *  각 index마다 해당 위치에서의 최대값을 저장하고
 *  이전 수열들을 보며 현재 위치의 수 보다 작거나 같은 수의 dp값들을 확인하며
 *  Max 값에 +1 하는 방법을 사용했습니다.
 */

#include<iostream>
#include<algorithm>

using namespace std;

int dp[1002];
int arr[1002];

int main(void){
    fill_n(dp,1002,0);

    int n;
    cin>>n;

    int result=0;
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
        if(dp[i]==0){
            dp[i]=1;
        }
        for(int j=0;j<i;j++){
            if(arr[j]<arr[i]){
                dp[i]=max(dp[j]+1,dp[i]);  
            }
        }
        result=max(result,dp[i]);
    }
    cout<<result<<endl;
}
