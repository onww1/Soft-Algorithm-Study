/*
BOJ 6581 - HTML

우선 한 단어씩 입력받습니다. l변수에는 한 줄의 길이를 담아둡니다.
<br>의 경우 \n 출력 후 l=0
<hr>의 경우 이미 줄의 첫 부분 (l==0)이라면 hr출력, 아니라면 \n후 hr출력 후 l=0
위의 두 단어 외의 단어가 들어왔을 때 (l+단어의 길이)가 80을 넘지 않는다면 이어서 출력합니다.
이때 띄어쓰기를 하므로 l에는 len+1값을 더해줍니다.
80을 넘는다면 \n후 단어를 출력해주고 l을 len+1값으로 초기화 해줍니다.
*/
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
	char hr[83] = "--------------------------------------------------------------------------------\n";
	char st[83];
	int l = 0, len;
	while (~scanf("%s", st)) {
		len = strlen(st);
		if (st[0] == '<') {
			if (st[1] == 'b') {
				printf("\n");
				l = 0;
			}
			else if (st[1] == 'h') {
				if(l!=0) printf("\n%s", hr);
				else printf("%s", hr);
				l = 0;
			}
		}
		else if (l + len > 80) {
			printf("\n%s ", st);
			l = len + 1;
		}
		else {
			printf("%s ", st);
			l += len + 1;
		}
	}

	return 0;
}