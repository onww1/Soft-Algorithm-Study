/*
 *  BOJ 2933. 미네랄 
 *
 *  시간 복잡도 : O(NRC)
 *  공간 복잡도 : O(RC)
 *
 *  먼저 입력을 x에 대해서는 1, .에 대해서는 0으로 해서 받았습니다. 그리고 나중을 위해 맨 아랫줄에 
 *  한 줄을 더 추가해서 모두 1로 처리를 했습니다. 이후 미네랄을 부수는 쿼리마다 그 지점을 찾아서 부수고, 
 *  맨 아랫줄부터 시작해서 바닥에 해당하는 클러스터를 구했습니다. 그리고 각 열마다 가장 위쪽에 있는 바닥 클러스터와 
 *  나머지 애들 중에서 가장 밑에 있는 애들 사이의 거리의 최솟값을 구합니다. 그리고 그만큼 이동시키고, 
 *  다음 쿼리를 진행합니다. 이런 식으로 반복하는 과정입니다.
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#define X first
#define Y second
using namespace std;
typedef pair <int, int> pii;

const int MAX = 100;
const int move_r[] = {0, -1, 0, 1, -1, -1, 1, 1};
const int move_c[] = {-1, 0, 1, 0, -1, 1, -1, 1};
int R, C, N, MAP[MAX + 2][MAX + 2];
bool visited[MAX + 1][MAX + 1];
char in[MAX + 1];
queue <pii> Q;

// BFS를 통해서 바닥과 연결된 클러스터를 찾는다.
void BFS() {
    memset(visited, false, sizeof(visited));
    Q.push({R, 0}); visited[R][0] = true;

    while (!Q.empty()) {
        int r = Q.front().X;
        int c = Q.front().Y;
        Q.pop();

        for (int k = 0; k < 4; ++k) {
            int dr = r + move_r[k];
            int dc = c + move_c[k];
            if (dr < 0 || dr > R || dc < 0 || dc >= C) continue;
            if (!visited[dr][dc] && MAP[dr][dc]) {
                visited[dr][dc] = true;
                Q.push({dr, dc});
            }
        }
    }
}

// 각 열에 있는 미네랄들을 통해서 얼마나 이동을 해야하는지 확인.
int check_dist() {
    int ret = INF;
    for (int j = 0; j < C; ++j) {
        for (int i = R - 1, last = R; i >= 0; --i) {
            if (visited[i][j]) last = i;
            else if (MAP[i][j]) {
                ret = min(ret, last - i - 1);
                break;
            }
        }
    }
    return ret;
}

// dist만큼 클러스터를 이동시키는 함수
void go(int dist) {
    // 아랫줄에서부터 이동 (겹치치 않기 위해서)
    for (int r = R - 1; r >= 0; --r) 
        for (int c = 0; c < C; ++c) 
            if (!visited[r][c] && MAP[r][c]) {
                MAP[r][c] = 0;
                MAP[r + dist][c] = 1;
            }
}

int main(int argc, char *argv[]) {
    open();
  
    scanf("%d %d", &R, &C);
    for (int i = 0; i < R; ++i) {
        scanf(" %s", in);
        for (int j = 0; in[j]; ++j) 
            MAP[i][j] = (in[j] == 'x' ? 1 : 0);
    }
    // 밑에 추가적으로 가상의 미네랄을 한 줄 깐다.
    for (int j = 0; j < C; ++j) MAP[R][j] = 1;

    scanf("%d", &N);
    for (int i = 0, F, r, c; i < N; ++i) {
        scanf("%d", &F);
        r = R - F;
        if (i % 2) { // 오른쪽에서 날아오는 상황
            for (c = C - 1; c >= 0; --c) if (MAP[r][c]) break;
            if (c >= 0) MAP[r][c] = 0;
        } else {     // 왼쪽에서 날아오는 상황
            for (c = 0; c < C; ++c) if (MAP[r][c]) break;
            if (c < C) MAP[r][c] = 0;
        }

        // 부순 것이 없으면 무시한다.
        if (c < 0 || c >= C) continue;

        // 바닥과 연결된 클러스터를 찾는다.
        BFS();

        // 얼마나 이동을 해야하는지 구한다.
        int dist = check_dist();

        // 유효한 이동이 있으면 이동한다.
        if (dist != INF && dist > 0) go(dist);
    }

    // 결과 출력
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) printf("%c", MAP[i][j] ? 'x' : '.');
        puts("");
    }

    return 0;
}