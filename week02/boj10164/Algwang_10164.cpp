#include<iostream>
/*
 * 중학교 때 수학 시간에 배운 길찾기 방법을 사용했습니다.
 * 점1에서 점2까지의 최단경로의 수를 구하기 위해서
 * 점1의 오른쪽, 아래의 모든 점을 1로 초기화하고
 * 초기화되지 않은 점들 중 가장 왼쪽 위부터 시작해서
 * 자신의 오른쪽 위의 값과의 합을 오른쪽에 씁니다.
 * 즉, dp[i-1][j]+dp[i][j-1]=dp[i][j]가 됩니다.
 * 중단점이 없을 경우와 있을 경우를 구분해서 사용합니다.
 */
using namespace std;

int main(void){
    int dp[20][20]={0};
    int m,n,o;
    cin>>n>>m>>o;
    // 입력
    if(o!=0){
        int oI=(o-1)/m;
        int oJ=(o-1)%m;
        int path1=0;
        int path2=0;
        // ㅇ 까지의 경로(path1), ㅇ 이후의 경로(path2)
        for(int i=0;i<=oI;i++){
            dp[i][0]=1;
        }
        for(int j=0;j<=oJ;j++){
            dp[0][j]=1;
        }
        for(int i=oI+1;i<n;i++){
            dp[i][oJ]=1;
        }
        for(int j=oJ+1;j<m;j++){
            dp[oI][j]=1;
        }
        // 시작점의 가로(오른쪽) 세로(아래), ㅇ 의 가로(오른쪽) 세로(아래)를 1로 초기화한다.
        for(int i=1;i<=oI;i++){
            for(int j=1;j<=oJ;j++){
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }
        path1=dp[oI][oJ];
        // 시작점에서 ㅇ 까지의 1로 초기화 되어있지 않은 구간을 통해 dp를 구한다.
        for(int i=oI+1;i<n;i++){
            for(int j=oJ+1;j<m;j++){
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }
        path2=dp[n-1][m-1];
        // ㅇ 에서 끝점까지의 초기화 되어있지 않은 구간을 통해 dp를 구한다.
        
        cout<<path1*path2<<endl;
    }else{
        for(int i=0;i<n;i++){
            dp[i][0]=1;
        }
        for(int j=0;j<m;j++){
            dp[0][j]=1;
        }
        // 시작점의 가로(오른쪽) 세로(아래)를 1로 초기화한다.
        for(int i=1;i<n;i++){
            for(int j=1;j<m;j++){
                dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }
        // ㅇ 가 존재하지 않으므로 시작점부터 끝점까지의 초기화되지 않은 구간을 통해 dp를 구한다.
        cout<<dp[n-1][m-1]<<endl;
    }
}
