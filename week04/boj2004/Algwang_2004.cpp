/*
 * 공간복잡도 : O(1)
 * 시간복잡도 : O(logn) (밑 수는 2)
 * 
 * nCm의 결과는 n! / m! * (n-m)!입니다.
 * 처음에는 당연히 5의 배수가 더 적을 것이라고 생각하고
 * 5의 배수만 계산하다 맞왜틀 했습니다..
 * 26C2와 같은 예외가 있더라구요 !!
 * 그래서 2의 배수도 같은 방식으로 구해서
 * 둘 중에 최소값을 결과로 출력했습니다.
*/

#include<iostream>

using namespace std;

typedef long long ll;

int main(void){
    int a,b;
    cin>>a>>b;
    int c=a-b;
    int tempA,tempB,tempC;
    tempA=a; tempB=b; tempC=c;
    ll aCount1=0; ll bCount1=0; ll cCount1=0; // 2의 배수
    ll aCount2=0; ll bCount2=0; ll cCount2=0; // 5의 배수

    while(tempA>=2){
        tempA/=2;
        aCount1+=tempA;
    }
    while(tempB>=2){
        tempB/=2;
        bCount1+=tempB;
    }
    while(tempC>=2){
        tempC/=2;
        cCount1+=tempC;
    }
    while(a>=5){
        a/=5;
        aCount2+=a;
    }
    while(b>=5){
        b/=5;
        bCount2+=b;
    }
    while(c>=5){
        c/=5;
        cCount2+=c;
    }
    ll result1=aCount1-bCount1-cCount1;
    ll result2=aCount2-bCount2-cCount2;
    result1>result2?cout<<result2<<endl:cout<<result1<<endl;
}
