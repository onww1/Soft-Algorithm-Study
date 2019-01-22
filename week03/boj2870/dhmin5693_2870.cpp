/*
 * BOJ 2870. 수학숙제
 *
 * 받은 문자열을 첫 문자부터 끝 문자까지 순회합니다.
 * 0 ~ 9까지의 문자이면 임시 문자열 s에 넣습니다.
 * 아닌 경우 임시 문자열 s를 벡터에 삽입합니다.
 *
 * 모든 입력값을 벡터에 넣었으면 각 원소에서 0을 제거합니다.
 * int형을 사용했으면 0이 알아서 제거되었겠지만
 * 최대 100문자의 숫자가 올 수 있으므로 처리 가능한 정수 범위를 넘어서기 때문에 문자열로 처리해야 합니다.
 *
 * 마지막으로 정리된 벡터를 오름차순 배열하고 출력합니다.
 */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// 벡터에 저장될 문자열의 길이를 필요할 때마다 매번 구하는 수고를 덜기 위해 구조체를 선언했습니다.
typedef struct num {
    num(string _str, int _size) : str(_str), size(_size) {}

    string str;
    int size;
} num;

// 오름차순 정렬
bool compare(const num &a, const num &b) {

    if(a.size != b.size) {
        return a.size < b.size;
    }

    for(int i = 0; i < a.size; ++i) {
        if(a.str[i] != b.str[i]) {
            return a.str[i] < b.str[i];
        }
    }
}

int main() {
    int n;
    cin >> n;
    cin.ignore();

    vector<num> v;

    while(n-- > 0) {
        string input;
        getline(cin, input);

        int size = (int)input.size();

        string s;
        int sSize = 0;

        for(int i = 0; i < size; ++i) {
            // 숫자인 경우 s에 삽입
            if('0' <= input[i] && input[i] <= '9') {
                s.push_back(input[i]);
                ++sSize;
            } else {
                if(sSize > 0) {
                    num tmp(s, sSize);
                    v.push_back(tmp);
                    s.clear();
                    sSize = 0;
                }
            }
        }

        if(sSize > 0) {
            num tmp(s, sSize);
            v.push_back(tmp);
        }
    }

    int vSize = (int)v.size();

    // 벡터에 저장된 문자열 변환(0 제거)
    for(int i = 0; i < vSize; ++i) {
        if(v[i].size == 1) {
            continue;
        }

        // 0의 개수 세기
        int j;
        for(j = 0; v[i].str[j] == '0' && j < v[i].size; ++j);

        if(j > 0) {

            // 문자열 전체가 0인 경우 j를 1 줄임(0을 최소 하나 남기기 위해)
            if(j == v[i].size) {
                --j;
            }

            v[i].str = v[i].str.substr(j, v[i].size - j);
            v[i].size -= j;
        }
    }

    sort(v.begin(), v.end(), compare);

    for(int i = 0; i < vSize; ++i) {
        cout << v[i].str << "\n";
    }

    return 0;
}