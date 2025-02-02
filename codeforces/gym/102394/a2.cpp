#include <bits/stdc++.h>
using namespace std;
using pII = pair<int, int>;
#define fi first
#define se second
const int N = 1e5 + 10;
const int INF = 0x3f3f3f3f;
struct Edge {
    int v, w;
    Edge() {}
    Edge(int v, int w) : v(v), w(w) {}
};
vector<vector<Edge>> G;
struct node {
    int l, r, k;
    void input() {
        scanf("%d %d %d", &l, &r, &k);
    }
} q1[N], q2[N];
int n, M1, M2;
int dis[N], inq[N], cnt[N];
int que[N], ql, qr;

inline void Init() {
    G.clear();
    G.resize(n + 1);
    for (int i = 0; i <= n; ++i) {
        inq[i] = 0, cnt[i] = 0, dis[i] = INF;
    }
}

inline void addedge(int u, int v, int w) {
    G[u].push_back(Edge(v, w));
}

bool SPFA(int x) {
    for (int i = 0; i <= n; ++i) {
        inq[i] = cnt[i] = 0;
        dis[i] = INF;
    }
    dis[0] = 0;
    inq[0] = 1;
    ql = 1, qr = 0;
    que[++qr] = 0;
    while (ql <= qr) {
        int u = que[++ql];
        inq[u] = 0;
        for (auto &it : G[u]) {
            int v = it.v, w = it.w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!inq[v]) {
                    inq[v] = 1;
                    que[++qr] = v;
                    if (++cnt[v] > n)
                        return false;
                }
            }
        }
    }
    return dis[n] == x;
}

bool check(int x) {
    for (int i = 1; i <= M1; ++i) {
        int l = q1[i].l - 1, r = q1[i].r, k = q1[i].k;
        addedge(r, l, -k);
    }
    for (int i = 1; i <= M2; ++i) {
        int l = q2[i].l - 1, r = q2[i].r, k = q2[i].k;
        addedge(l, r, x - k);
    }
    for (int i = 1; i <= n; ++i) {
        addedge(i, i - 1, 0);
        addedge(i - 1, i, 1);
    }
    addedge(0, n, x);
    addedge(n, 0, -x);
    return SPFA(x);
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &M1, &M2);
        for (int i = 1; i <= M1; ++i) q1[i].input();
        for (int i = 1; i <= M2; ++i) q2[i].input();

        int l = 0, r = n - 1, res = n;
        while (r - l >= 0) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                r = mid - 1;
                res = mid;
            } else {
                l = mid + 1;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
