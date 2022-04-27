#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n"
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long;
using pII = pair<int, int>;
using pLL = pair<ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y, int Mod = mod) {
    x += y;
    while (x >= Mod) x -= Mod;
    while (x < 0) x += Mod;
}
template <class T1, class T2>
inline void chmax(T1 &x, T2 y) {
    if (x < y)
        x = y;
}
template <class T1, class T2>
inline void chmin(T1 &x, T2 y) {
    if (x > y)
        x = y;
}
inline int nextInt() {
    int x;
    cin >> x;
    return x;
}
void rd() {}
template <class T, class... Ts>
void rd(T &arg, Ts &...args) {
    cin >> arg;
    rd(args...);
}
#define dbg(x...)                             \
    do {                                      \
        cout << "\033[32;1m" << #x << " -> "; \
        err(x);                               \
    } while (0)
void err() {
    cout << "\033[39;0m" << endl;
}
template <class T, class... Ts>
void err(const T &arg, const Ts &...args) {
    cout << arg << ' ';
    err(args...);
}
template <template <typename...> class T, typename t, typename... A>
void err(const T<t> &arg, const A &...args) {
    for (auto &v : arg) cout << v << ' ';
    err(args...);
}
void ptt() {
    cout << endl;
}
template <class T, class... Ts>
void ptt(const T &arg, const Ts &...args) {
    cout << ' ' << arg;
    ptt(args...);
}
template <class T, class... Ts>
void pt(const T &arg, const Ts &...args) {
    cout << arg;
    ptt(args...);
}
void pt() {}
template <template <typename...> class T, typename t, typename... A>
void pt(const T<t> &arg, const A &...args) {
    for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1];
    pt(args...);
}
inline ll qpow(ll base, ll n) {
    assert(n >= 0);
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
// head
constexpr int N = 1e5 + 10;
int n, m, fa[N], deep[N], InSta[N], vis[N], use[N], limit;
vector<vector<int>> G;

void dfs(int u) {
    vis[u] = 1;
    InSta[u] = 1;
    for (auto &v : G[u])
        if (v != fa[u]) {
            if (InSta[v]) {
                if (deep[u] - deep[v] + 1 >= limit) {
                    vector<int> res;
                    int it = u;
                    while (1) {
                        res.push_back(it);
                        if (it == v)
                            break;
                        it = fa[it];
                    }
                    pt(2);
                    pt(SZ(res));
                    for (int i = 0; i < SZ(res); ++i) cout << res[i] << " \n"[i == SZ(res) - 1];
                    exit(0);
                }
            }
            if (!vis[v]) {
                fa[v] = u;
                deep[v] = deep[u] + 1;
                dfs(v);
            }
        }
    if (!use[u]) {
        for (auto &v : G[u]) {
            use[v] = 1;
        }
    }
    InSta[u] = 0;
}

void run() {
    limit = int(sqrt(n));
    while (limit * limit < n) ++limit;
    G.clear();
    G.resize(n + 1);
    for (int i = 1, u, v; i <= m; ++i) {
        rd(u, v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    memset(InSta, 0, sizeof InSta);
    memset(vis, 0, sizeof vis);
    memset(fa, 0, sizeof fa);
    fa[1] = 1;
    dfs(1);
    memset(vis, 0, sizeof vis);
    vector<int> res;
    for (int i = 1; i <= n; ++i) {
        if (!use[i])
            res.push_back(i);
    }
    assert(SZ(res) >= limit);
    pt(1);
    for (int i = 0; i < limit; ++i) cout << res[i] << " \n"[i == limit - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
