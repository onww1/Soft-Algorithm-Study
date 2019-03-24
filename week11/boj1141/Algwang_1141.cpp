#include<iostream>
#include<string>

using namespace std;

int main(void) {
	int n;
	cin >> n;
	string str[52];
	for (int i = 0; i < n; i++) {
		cin >> str[i];
	}
	int count = 0;
	for (int i = 0; i < n; i++) {
		bool check = false;
		bool sameFlag = false;
		for (int j = 0; j < n; j++) {			
			if (i != j&&str[i].length()<str[j].length()) {
				for (int k = 0; k < str[i].length(); k++) {
					if (str[i].at(k) != str[j].at(k)) {
						break;
					}
					else if (k == str[i].length()-1) {
						check = true;
					}
				}
			}
			else if (str[i] == str[j] && i > j) {
				sameFlag = true;
				continue;
			}
		}
		if (!check&&!sameFlag) count++;
	}
	cout << count << endl;
}
