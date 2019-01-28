/*
 * 시간복잡도 : O(N)
 * 공간복잡도 : O(1)
 * 
 * 연속된 숫자의 합이라는 성질을 이용했습니다.
 * 특정 수 n의 절반+1까지 탐색을 하며 지금까지의 합에서 n을 뺀 값이
 * 등차수열을 만족하는 경우를 찾아서 count를 늘려줬습니다.
 * 마지막에 +1하는 부분은 자기 자신의 경우입니다.
 * 5 + 6 + 7 + 8은 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8에서 1 + 2 + 3 + 4를 뺀 값이라는
 * 성질을 이용했습니다.
*/
#include<iostream>
#include<math.h>

using namespace std;

typedef long long ll;

int main(void){
    ll n;
    cin>>n;

    int count=0;
    
    for(int i=1;i<=n/2+1;i++){
        ll temp=((ll)i*(ll)(i+1))/2; // 1부터 i까지의 합
        if(temp-n>=0){ // 합이 주어진 수 n보다 크거나 같다면
            ll myT=(ll)sqrt((temp-n)*2); // 차이가 n*(n+1)/2를 만족하는 자연수 n이 존재하는지 확인합니다.
            if(1ll*myT*(myT+1)==1ll*(temp-n)*2){ // 만약 존재한다면 count++
                count++;
            }
        }
    }
    if(n==1||n==2){
        cout<<1<<endl;
        return 0;
    }
    cout<<count+1<<endl;
}
