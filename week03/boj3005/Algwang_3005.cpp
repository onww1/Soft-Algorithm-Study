#include<iostream>
#include<algorithm>
#include<string.h>
#include<vector>

using namespace std;

bool comp(string a, string b) {
	if (a.compare(b) < 0) {
		return true;
	}
	else {
		return false;
	}
}

int main(void) {
	int H, W;
	cin >> H >> W;
	char puzzle[21][21];
	vector<string> strVec;

	for (int i = 0; i < H; i++) {
		scanf("%s", puzzle[i]);
	}

	for (int i = 0; i < H; i++) {
		bool isWallFlag = false;
		string str = "";
		for (int j = 0; j < W; j++) {
			if (puzzle[i][j] == '#') {
				if (isWallFlag&&str.size() >= 2) {
					strVec.push_back(str);
				}
				isWallFlag = false;
				str = "";
			}
			else {
				str += puzzle[i][j];
				isWallFlag = true;
			}
		}
		if (isWallFlag&&str.size() >= 2) {
			strVec.push_back(str);
		}
	}
	for (int i = 0; i < W; i++) {
		bool isWallFlag = false;
		string str = "";
		for (int j = 0; j < H; j++) {
			if (puzzle[j][i] == '#') {
				if (isWallFlag&&str.size() >= 2) {
					strVec.push_back(str);
				}
				isWallFlag = false;
				str = "";
			}
			else {
				str += puzzle[j][i];
				isWallFlag = true;
			}
		}
		if (isWallFlag&&str.size() >= 1) {	
			strVec.push_back(str);
		}
	}
	sort(strVec.begin(), strVec.end(), comp);
	printf("%s\n", strVec[0].c_str());
}
