/*
BOJ 1141 - 접두사

시간복잡도 : O(N^3)
공간복잡도 : O(N^2)

접두사X 집합의 크기가 가장 크게 하려면 다른 단어의 접두사가 아닌 단어들을 모두 선택하면 됩니다.
따라서 다른 단어의 접두사가 되는 단어의 deg를 올려주어 deg가 0인 것의 개수를 세줬습니다.
*/
#include <cstdio>
#include <cstring>
using namespace std;

/* 🐣🐥 */
int deg[51];
char st[51][51];
int main() {
	int n, cnt = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%s", st[i]);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j || strlen(st[j]) < strlen(st[i])) continue;
			if (strcmp(st[i], st[j]) == 0 && i > j) continue;
			bool f = false;
			for (int k = 0; k < strlen(st[i]); k++) {
				if (st[i][k] != st[j][k]) f = true;
			}
			if (!f) {
				deg[i]++;
			}
		}
	}
	for (int i = 0; i < n; i++) if (deg[i] == 0) cnt++;
	printf("%d", cnt);

	return 0;
}