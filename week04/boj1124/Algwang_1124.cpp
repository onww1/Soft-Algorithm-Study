/*
 * 시간 복잡도 : ?
 * 공간 복잡도 : O(N) (check 배열 + arr 배열)
 * 
 * 에라토스테네스의 체를 이용했습니다.
 * 2부터 10만까지 탐색을 하며 해당 수( i )가 소수일 경우
 * i를 제외한 i의 배수들에 대해 모두 소수가 아님을 체크해주고
 * i로 나눠지는 횟수를 구해 소인수 분해했을 때의 소수의 개수를 나타내는
 * arr배열의 값을 증가시켜줬습니다.
 * arr[n] -> 소인수 분해 시 소수의 개수
 * check[arr[n]] -> 소인수 분해 시 소수의 개수가 소수인지 여부
 * 이렇게 구한 값을 바탕으로 A에서 B까지 check[arr[n]]이 true인 수들의 숫자를 count했습니다.
*/

#include<iostream>

using namespace std;

int main(void){
    int A,B;
    cin>>A>>B;

    bool check[100002];
    fill_n(check,100002,true);
    check[1]=false; // 1과 0은 소수가 아님 !
    check[0]=false;
    int arr[100002]={0};
    int result=0;

    for(int i=2;i<=100000;i++){
        if(check[i]){ // 만약 i가 소수라면
            for(int j=i*2;j<=B;j+=i){ // i의 배수들을 찾아서
                check[j]=false; // 소수가 아님을 처리
                int curNum=j;
                while(curNum%i==0){
                    curNum/=i;
                    arr[j]++;
                } // 그리고 i로 나누어지는 횟수만큼 증가
            }
        }
    }
    for(int i=A;i<=B;i++){
        if(check[arr[i]]) result++;
    }
    cout<<result<<endl;
}
