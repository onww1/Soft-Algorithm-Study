/*
 *  BOJ 11053. 가장 긴 증가하는 부분 수열
 * 
 *  DP로 할 수 있지만 단순히 lis의 길이를 구하면 되는 문제이므로 lower_bound를 이용했습니다.
 *  우선, lis를 저장하는 vector를 만듭니다.
 *  그 다음 원소를 하나씩 받으면서 lis vector에 대하여 lower_bound를 합니다.
 *  만약 lis가 가장 오른쪽에 넣어져야 한다면 push_back을 하여 추가해주고,
 *  아니라면 그 위치에 값을 저장해줍니다.
 *  그렇게 하여 최종적인 lis vector의 size가 lis의 최대 길이가 됩니다.
 * 
 *  다만, 이렇게 했을 때 lis에 저장된 값은 정말 lis가 아닙니다.
 *  그저 이 방법은 lis의 최대 길이를 알려줄 뿐입니다.
 */

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector <int> lis;
int main() {
    int n, a, i;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) {
        scanf("%d", &a);
        auto it = lower_bound(lis.begin(), lis.end(), a);
        if (it == lis.end()) lis.push_back(a);
        else *it = a;
    }
    return !printf("%lu\n", lis.size());
}