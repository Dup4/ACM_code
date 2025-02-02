#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int n, m;
vector<vector<int>> G;
struct Tarjan {
    // Low[i] 点i第一次访问的时间戳
    // DFN[i] 点i能访问到的点中的Low的最小值
    // Belong[i] 点i属于哪个scc
    // num[i] 第i个scc有几个点
    int Low[N], DFN[N], sta[N], Belong[N], num[N], cntSCC;
    bool Insta[N];
    int d_in[N], d_out[N];
    void dfs(int u) {
        Low[u] = DFN[u] = ++*Low;
        sta[++*sta] = u;
        Insta[u] = 1;
        for (auto &v : G[u]) {
            if (!DFN[v]) {
                dfs(v);
                Low[u] = min(Low[u], Low[v]);
            } else if (Insta[v])
                Low[u] = min(Low[u], DFN[v]);
        }
        if (Low[u] == DFN[u]) {
            ++cntSCC;
            int v;
            do {
                v = sta[(*sta)--];
                Insta[v] = 0;
                Belong[v] = cntSCC;
                ++num[cntSCC];
            } while (v != u);
        }
    }
    void gao(int n) {
        memset(DFN, 0, sizeof(DFN[0]) * (n + 10));
        memset(Insta, 0, sizeof(Insta[0]) * (n + 10));
        memset(num, 0, sizeof(num[0]) * (n + 10));
        cntSCC = *sta = *Low = 0;
        for (int i = 1; i <= n; ++i)
            if (!DFN[i])
                dfs(i);
    }
    void work(int n) {
        gao(n);
        memset(d_in, 0, sizeof(d_in[0]) * (cntSCC + 10));
        memset(d_out, 0, sizeof(d_out[0]) * (cntSCC + 10));
        for (int u = 1; u <= n; ++u) {
            for (auto &v : G[u]) {
                if (Belong[u] == Belong[v])
                    continue;
                ++d_out[Belong[u]];
                ++d_in[Belong[v]];
            }
        }
        int zero = 0;
        for (int i = 1; i <= cntSCC; ++i)
            if (d_out[i] == 0)
                ++zero;
        if (zero != 1)
            puts("0");
        else
            printf("%d\n", num[1]);
    }
} tarjan;

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        G.clear();
        G.resize(n + 1);
        for (int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
        }
        tarjan.work(n);
    }
    return 0;
}
