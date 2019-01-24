/*
BOJ 3005 - 크로스워드 퍼즐 쳐다보기

처음에는 중간에 #이 들어가있다면 단어가 되지 못하는 것으로 잘못 이해했습니다(...)
한 줄(r)씩 읽으며 두 글자 이상인 단어를 st배열에 넣어주었습니다.
읽는 중에 #이 등장할 때마다 tmp가 두 글자 이상이라면 넣어주고, 비워줬습니다.
또한 모두 읽고 나서도 넣어줍니다.
한 칸(c)씩 읽는 과정도 위와 같습니다.
st 배열 sort 후 맨 앞의 단어가 사전순으로 제일 앞서는 단어가 됩니다.
*/
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string st[400];
int tp;  // 단어의 개수
int main() {
	int r, c;
	char b[21][21];
	scanf("%d %d", &r, &c);
	for (int i = 0; i < r; i++) {
		scanf("%s", b[i]);
	}
	for (int i = 0; i < r; i++) {  // 한 줄씩
		string tmp = "";
		for (int j = 0; j < c; j++) {
			if (b[i][j] != '#') tmp += b[i][j];
			else { // #을 만났다!
				// 두 글자 이상일 때 st배열에 넣어준다.
				if (tmp.size() > 1) st[tp++] = tmp;
				tmp = "";  //  비워주기
			}
		}
		if (tmp.size() > 1) st[tp++] = tmp;
	}
	for (int i = 0; i < c; i++) {  //  한 칸씩
		string tmp = "";
		for (int j = 0; j < r; j++) {
			if (b[j][i] != '#') tmp += b[j][i]; 
			else {
				if (tmp.size() > 1) st[tp++] = tmp;
				tmp = "";
			}
		}
		if (tmp.size() > 1) st[tp++] = tmp;
	}
	sort(st, st + tp);
	cout << st[0];

	return 0;
}