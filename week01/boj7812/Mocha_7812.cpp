/*
 *  BOJ 7812. 중앙 트리
 * 
 *  어려웠던 문제들은 다 Tree DP죠..
 *  이 문제 또한 Tree DP입니다 ㅜㅜ
 * 
 *  이 문제 역시 모든 node 간의 관계가 필요하기 때문에 naive하게 풀면 O(n^2)이 됩니다.
 *  시간제한도 3초이고, 컴파일러의 최적화와 같은 것들이 잘 되면 한 두번 푸는건 괜찮은데
 *  이 문제는 여러 개의 쿼리가 존재하기 때문에 터질 수 밖에 없습니다. 
 *  따라서 이 문제를 풀기 위해서는 트리의 가중치나 색칠하기처럼 O(n)이 되도록 만들어야 합니다.
 * 
 *  저는 어떻게하면 될까 고민을 하다가 먼저 한 노드에서 시작해서 그 노드에 대한 전체 합을 구하도록
 *  하는데 그 과정에서 각각의 노드들이 그 서브트리의 합과 노드의 개수를 가지고 있도록 만들었습니다.
 *  그렇게 하면 처음 시작한 노드에 대해서는 완전한 정보가 되고, 각각 나머지에 대해서는 서브트리의 값이
 *  저장되는 것이었죠. 이러한 상황에서 한 번 더 순회하면서 완전한 값을 이용하여 보정하는 과정을 거쳤습니다.
 * 
 *  1. solve1 함수는 해당하는 노드를 루트로 하는 서브트리에 대하여 하위 노드들과의 거리의 합과 노드의 갯수를
 *  저장하도록 하는 함수였습니다. 따라서 모든 child에 대하여 solve1 함수를 재귀적으로 호출하고, 그 값을 통해서 
 *  얻은 값에서 노드의 갯수는 nn에 더하고, 합은 s에 더하는데 그 하위 노드에 연결되는 가중치에 노드 갯수를 곱해서 더했습니다.
 *  그렇게 함으로써 그 노드의 하위 노드에까지 연결되는 효과를 볼 수 있던 것이죠.
 *  
 *  2. solve2 함수는 완전하게 구했던 노드에서 시작하여서 다른 하위 노드들을 완전한 값으로 보정해주는 함수였습니다.
 *  전체 노드의 갯수는 처음 노드에서부터 계속 옮겨 저장하면서 유지하고, 완전한 값으로 바꾸기 위한 식은 
 *  (현재 노드에 대한 전체 합) + (가중치) * (전체 노드의 수 - 2 * 자식 노드의 노드 수)
 *  입니다. 이것은 먼저 현재 노드에 대한 전체 합에서 자식 노드가 주었던 효과를 지우면 자식 노드를 제외한 합이 되기 때문입니다.
 *  그래서 먼저 (가중치) * (자식 노드의 노드 수)를 빼주고, 그 다음 이것을 반대로 자식노드에게 연결해주는 효과를 줘야 하므로 
 *  자식 노드와 연결되지 않은 노드의 수를 계산해서 가중치를 곱해서 더해줘야 합니다.
 *  그런데 이것은 전체 노드에서 자식노드에 연결된 노드의 수를 빼주면 되므로 (가중치) * (전체 노드 수 - 자식 노드의 노드 수) 입니다.
 *  따라서 이것을 종합하면 계산해줘야 하는 것이 (가중치) * (전체 노드 수 - 2 * 자식 노드의 노드 수)이고, 
 *  이것을 (현재 노드에 대한 전체 합)에 대하여 더해준 것입니다.
 *  이렇게 하고 나서 전체 인덱스에 대해서 순회하면서 제일 작은 값을 찾아서 그것을 출력하면 되는 문제였습니다.
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
typedef pair<int, ll> pil;

struct edge {
    int v;
    ll w;
};

vector <edge> edges[10050];
pil dp[10050];

// node에 대하여 서브 트리의 경로 합을 구하는 함수
pil solve1(int node, int parent) {
    int nn = 1;  // node 포함 서브 트리의 노드 수
    ll s = 0;    // node에 연결된 서브트리의 경로의 합
    for (auto it : edges[node]) {
        if (it.v == parent) continue;
        pil val = solve1(it.v, node);
        nn += val.first;
        s += (val.second + it.w * val.first); // 현재 노드와 연결될 때 추가되는 값 계산
    }
    return dp[node] = {nn, s};
}

// node의 child 들의 전체 경로의 합을 구해주는 함수
void solve2(int node, int parent) {
    for (auto it : edges[node]) {
        if (it.v == parent) continue;
        dp[it.v].second = dp[node].second + (it.w * (dp[node].first - 2 * dp[it.v].first)); // 보정하는 식
        dp[it.v].first = dp[node].first; // 전체 노드의 수를 넘겨주는 식.
        solve2(it.v, node);
    }
}

int main(int argc, char *argv[]) {
    int n, i, u, v;
    ll w;
    while (1) {
        scanf("%d", &n);
        if (!n) break;
        for (i = 0; i < n; ++i) edges[i].clear();
        for (i = 1; i < n; ++i) {
            scanf("%d %d %lld", &u, &v, &w);
            edges[u].push_back({v, w});
            edges[v].push_back({u, w});
        }
        solve1(0, -1);
        solve2(0, -1);
        ll mn = 1LL << 60;
        for (i = 0; i < n; ++i) mn = min(mn, dp[i].second);
        printf("%lld\n", mn);
    }
    return 0;
}