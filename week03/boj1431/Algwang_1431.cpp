/*
 * 문제에서 제시한 조건을 최대한 따라갔습니다.
 * for문이 길어지고 귀찮을 수 있는 자릿수의 합 더하기의 경우
 * 입력을 받으면서 처리해서 나온 결과와 함께 Serial이라는 구조체에 포함했습니다.
 * 다음으로 길이는 strlen을 활용했고
 * 사전순 비교는 '0'~'9'가 'A'~'Z'보다 ASCII 상으로 작다는 점을 이용해서 구분했습니다.
 * 비교의 우선순위는 if - else if - else if의 우선순위를 이용해서 해결했습니다.
*/
#include<iostream>
#include<string.h>

using namespace std;

struct Serial{
    char str[51];
    int numSum;  
};

int main(void){
    int n;
    cin>>n;
    Serial serial[1005];
    char temp[52];
    int tempSum=0;
    for(int i=0;i<n;i++){
        tempSum=0;
        scanf("%s",&serial[i].str);
        for(int j=0;j<strlen(serial[i].str);j++){
            if(serial[i].str[j]>='0'&&serial[i].str[j]<='9'){
                tempSum+=(int)serial[i].str[j]-(int)'0';
            }
        }
        serial[i].numSum=tempSum;
    }

    for(int i=0;i<n-1;i++){
        for(int j=i;j<n;j++){
            bool flag=false;
            // 비교 1 문자열 길이 비교
            if(strlen(serial[i].str)>strlen(serial[j].str)){
                flag=true;
            }else if(strlen(serial[i].str)==strlen(serial[j].str)){
                //비교 2 자리수 합 비교
                if(serial[i].numSum>serial[j].numSum){
                    flag=true;
                }
                else if(serial[i].numSum==serial[j].numSum){
                    //비교 3 사전순 비교
                    for(int k=0;k<strlen(serial[i].str);k++){
                        if(serial[i].str[k]!=serial[j].str[k]){
                            if((int)serial[i].str[k]>(int)serial[j].str[k]){
                                flag=true;
                                break;
                            }
                            else{
                                break;
                            }
                        }
                    }
                }
            }
            if(flag){
                Serial compareTemp=serial[j];
                serial[j]=serial[i];
                serial[i]=compareTemp;
            }
        }
    }
    for(int i=0;i<n;i++){
        printf("%s\n",serial[i].str);
    }
}
