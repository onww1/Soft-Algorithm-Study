#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define pi pair<int,int>
#define pii pair<int,pi>
#define x first
#define y second

vector<pii> myVec;

int main(void) {
	int a, b, c;
	cin >> a >> b >> c;
	int check[305];
	fill_n(check, 305, 2);
	int checkCount;
	cin >> checkCount;
	
	for (int i = 0,tempA,tempB,tempC,res; i < checkCount; i++) {
		scanf("%d %d %d %d", &tempA, &tempB, &tempC, &res);
		if (res == 1) {
			check[tempA] = check[tempB] = check[tempC] = 1;
		}
		else {
			myVec.push_back({ tempA, {tempB, tempC } });
		}
	}
	for (int i = 0; i < myVec.size(); i++) {
		if (check[myVec[i].x] == 1 && check[myVec[i].y.x] == 1) {
			check[myVec[i].y.y] = 0;
		}
		if (check[myVec[i].x] == 1 && check[myVec[i].y.y] == 1) {
			check[myVec[i].y.x] = 0;
		}
		if (check[myVec[i].y.x] == 1 && check[myVec[i].y.y] == 1) {
			check[myVec[i].x] = 0;
		}
	}
	for (int i = 1; i <= a + b + c; i++) {
		printf("%d\n", check[i]);
	}
}
