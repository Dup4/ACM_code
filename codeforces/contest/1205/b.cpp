#include <bits/stdc++.h>
using namespace std;
#define debug(...)           \
    {                        \
        printf("#  ");       \
        printf(__VA_ARGS__); \
        puts("");            \
    }
#define ll long long
const int N = 1e5 + 10;
const int mod = 1e9 + 7;
const int INF = 1e9;
template <class T1, class T2>
inline void chadd(T1 &x, T2 y) {
    x += y;
    if (x >= mod)
        x -= mod;
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
inline int rd() {
    int x;
    cin >> x;
    return x;
}
template <class T>
inline void out(T s) {
    cout << s << "\n";
}
inline ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}
inline ll qpow(ll base, ll n) {
    ll res = 1;
    while (n) {
        if (n & 1)
            res = res * base % mod;
        base = base * base % mod;
        n >>= 1;
    }
    return res;
}
int n, res;
ll a[N];
vector<set<int>> G;
vector<vector<int>> vec;
int vis[N], deep[N], used[N];
void DFS(int u, int fa) {
    used[u] = 1;
    vis[u] = 1;
    for (auto v : G[u])
        if (v != fa) {
            if (vis[v]) {
                //	cout << u << " " << v << " " << deep[u] << " " << deep[v] << endl;
                res = min(res, deep[u] - deep[v] + 1);
                //	cout << res << endl;
            } else {
                deep[v] = deep[u] + 1;
                DFS(v, u);
            }
        }
    vis[u] = 0;
}
void run() {
    for (int i = 1; i <= n; ++i) cin >> a[i];
    vec.clear();
    vec.resize(110);
    for (int i = 1; i <= n; ++i) {
        for (int j = 63; j >= 0; --j) {
            if ((a[i] >> j) & 1) {
                vec[j].push_back(i);
            }
        }
    }
    G.clear();
    G.resize(n + 1);
    for (int i = 0; i <= 63; ++i) {
        if (vec[i].size() >= 3) {
            return out("3");
        }
        if (vec[i].size() == 2) {
            int u = vec[i][0], v = vec[i][1];
            G[u].insert(v);
            G[v].insert(u);
        }
    }
    res = INF;
    memset(vis, 0, sizeof vis);
    memset(used, 0, sizeof used);
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            deep[i] = 1;
            DFS(i, i);
        }
    }
    if (res == INF)
        res = -1;
    cout << res << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    return 0;
}
