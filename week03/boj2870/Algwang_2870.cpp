/*
 * string에서 숫자를 추출해서 정렬하는 문제입니다.
 * 먼저 문자열에서 숫자를 뽑아내는 과정은
 * 숫자를 만날경우 flag를 true로 바꾸고 string에 추가합니다.
 * 그리고 문자를 만날 경우 flag를 false로 해줌과 동시에
 * 한 자리 0을 제외하고 나머지 숫자들의 앞 0들을 substr을 이용해서 제거해주고
 * vector에 넣어주는 방법을 사용했습니다.
 * 정렬은 compare 함수를 구성해서 길이 비교 -> 값 비교의 순서로 진행했습니다.
*/

#include<iostream>
#include<string.h>
#include<vector>
#include<algorithm>

using namespace std;

vector<string> strarr;

bool compare(string a,string b){
    int aLen=a.length();
    int bLen=b.length();
    if(aLen>bLen){
        return false;
    }else if(aLen<bLen){
        return true;
    }else{
        return a<b;
    }
}

int main(void){
    int n;
    cin>>n;
    for(int l=0;l<n;l++){
        char line[101];
        scanf(" %s",line);
        string temp="";
        bool flag=false;
        for(int i=0;i<strlen(line);i++){
            if(line[i]>='0'&&line[i]<='9'){
                temp+=line[i];
                flag=true;
            }else{
                if(flag){
                    while(true){
                        if(temp.length()>1&&temp.at(0)=='0'){
                            temp=temp.substr(1,temp.length()-1);
                        }else{
                            break;
                        }
                    }
                    strarr.push_back(temp);
                }
                flag=false;
                temp="";
            }
        }
        if(flag){
            while(true){
                if(temp.length()>1&&temp.at(0)=='0'){
                    temp=temp.substr(1,temp.length()-1);
                }else{
                    break;
                }
            }
            strarr.push_back(temp);
        }
    }
    sort(strarr.begin(),strarr.end(),compare);
    for(int i=0;i<strarr.size();i++){
        printf("%s\n",strarr.at(i).c_str());
    }
}
