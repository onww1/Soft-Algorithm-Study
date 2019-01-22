# Soft-Algorithm-Study
#### [Baekjoon Online Judge](https://www.acmicpc.net) based Online algorithm study 



### Todo

1. **코드 공유**

   * 주차별 문제 풀어서 해당 디렉토리에 업로드

   * 파일 이름 컨벤션 : {nickname} _ {problem number}

     - ex ) mocha_1000.cpp

   * 코드 상단에 주석을 이용하여 해당 문제를 해결한 아이디어를  정리

   * 코드 중간에 주석을 이용하여 코드에 대한 간단한 설명

     ```c++
     /*
      *	BOJ 1000을 이용한 템플릿입니다.
      *	
      *	이 문제는 A와 B를 입력받은 다음 코드의 양을 줄이기 위해서
      *	바로 return문에 printf를 넣었습니다.
      */
     
     #include <cstdio>
     using namespace std;
     
     int main(int argc, char *argv[]) {
         int a, b;
         scanf("%d %d", &a, &b);
         return !printf("%d\n", a + b); // !printf(...)를 하면 0을 리턴할 수 있습니다.
     }
     ```

     

2. **스터디 시간**
   - **주말 13시 ~ 18시 사이**
   - [Discord](http://discord.com)에 접속하여 서로 푼 방법을 설명



3. **주차별 주제**
   - **1주차** : Tree
   - **2주차** : Dynamic Programming
   - **3주차** : Parsing & Implementation



4. **문제 선정** 
   * **기본** : 3 ~ 6문제 (주제에 해당하는 기본적인 문제)
   * **심화** : 2 ~ 4문제 (생각해봐야 하는 문제)