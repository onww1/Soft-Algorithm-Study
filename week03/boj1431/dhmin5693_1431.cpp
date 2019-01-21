/*
 * BOJ 1431. 시리얼 번호
 * 주어진 대로 입력받은 뒤 sort 함수가 정렬합니다.
 * sort는 compare 함수를 기준으로 삼습니다.
 * 문제에서 주어진 순서대로 답을 도출했습니다.
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> g;

bool compare(const string& a, const string& b) {

    int aSize = (int)a.size();
    int bSize = (int)b.size();

    // 길이 비교
    if(aSize != bSize) {
        return aSize < bSize;
    }


    // 합 비교
    int aSum = 0, bSum = 0;
    for(int i = 0; i < aSize; ++i) {
        aSum += ('0' <= a[i] && a[i] <= '9')? a[i] - '0': 0;
        bSum += ('0' <= b[i] && b[i] <= '9')? b[i] - '0':0;
    }

    if(aSum != bSum) {
        return aSum < bSum;
    }

    // 사전순 비교
    return a < b;
}

int main() {

    int n;
    cin >> n;

    // 버퍼 비우기
    cin.ignore();

    for(int i = 0; i < n; ++i) {
        string serial;
        getline(cin, serial);
        g.push_back(serial);
    }

    sort(g.begin(), g.end(), compare);

    for(int i = 0; i < n; ++i) {
        cout << g[i] << "\n";
    }

    return 0;
}