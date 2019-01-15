#include<iostream>

using namespace std;

int main(void){
    int dp[1001]={0};
    int n;
    cin>>n;
    dp[1]=1;
    dp[2]=3;
    // 계단을 뛰는 것과 비슷한 문제이다.
    // 1칸 이전, 2칸 이전의 경우의 수를 더해주면 된다.
    // 주의해야할 점은 2칸 전의 데이터에 2를 곱한 뒤 더해줘야한다는 것!
    for(int i=3;i<=n;i++){
        dp[i]=((dp[i-2]*2)+dp[i-1])%10007;
    }
    cout<<dp[n]<<endl;
}
