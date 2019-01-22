/*
BOJ 2870 - 수학숙제

숫자가 등장할 때 tmp문자열에 수를 넣어주었습니다.
그리고 문자가 등장할 때, 문자열을 끝까지 읽었을 때 vector에 tmp문자열을 넣어줍니다.

비내림차순 출력은 cmp함수에서 구현하였습니다.
길이가 짧은 문자열은 길이가 긴 문자열보다 수가 작을 수밖에 없고,
길이가 같다면 사전순으로 정렬해주면 작은 수가 앞으로 가게 됩니다.
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

vector<string> vec;
bool cmp(string &a, string &b) {
	// 두 문자의 길이가 같다면 사전순으로 정렬
	if (a.size() == b.size()) return a < b;
	return a.size() < b.size(); // 길이가 작은 것이 작은 값
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	int n, len;
	string st, tmp;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> st;
		len = st.size();
		tmp = "";
		for (int j = 0; j < len; j++) {
			if (st[j] <= '9' && st[j] >= '1') {
				// 맨 앞자리가 0일 때 0이 아닌 수가 나오면 0 삭제
				if (tmp.size() != 0 && tmp[0] == '0') {
					tmp = ""; tmp += st[j];
				}
				else
					tmp += st[j];
			}
			else if (st[j] == '0') {
				// 맨 앞자리가 0일 때 0이 나오면 넘어감
				if (tmp.size() != 0 && tmp[0] == '0') {
					continue;
				}
				tmp += st[j];
			} 
			else if (tmp.size() != 0) {  // 숫자가 아닌 경우
				vec.push_back(tmp);		 // vec배열에 저장된 숫자 문자열을 넣어줍니다
				tmp = "";
			}
		}
		if (tmp.size() != 0) vec.push_back(tmp);
	}
	sort(vec.begin(), vec.end(), cmp); // cmp기준 정렬
	for (string v : vec) cout << v << "\n";

	return 0;
}