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
