#include <bits/stdc++.h>
using namespace std;
#define endl "\n"
#define fi first
#define se second
#define SZ(x) ((int)(x).size())
#define mkp make_pair
#define all(x) (x).begin(), (x).end()
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
int n, m;

vector<vector<int>> G;
struct Tarjan {
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
    void gao() {
        memset(DFN, 0, sizeof(DFN[0]) * (n + 10));
        memset(Insta, 0, sizeof(Insta[0]) * (n + 10));
        memset(num, 0, sizeof(num[0]) * (n + 10));
        cntSCC = *sta = *Low = 0;
        for (int i = 1; i <= n; ++i)
            if (!DFN[i])
                dfs(i);
    }
    int work() {
        gao();
        memset(d_in, 0, sizeof(d_in[0]) * (cntSCC + 10));
        memset(d_out, 0, sizeof(d_out[0]) * (cntSCC + 10));
        int res = 0;
        for (int i = 1; i <= cntSCC; ++i) {
            res += num[i] - 1;
        }
        return res;
    }
} tarjan;

class Solution {
public:
    /**
     * @param nums: The server to which the server sends information (subscripts start from 1)
     * @return: At least there are access rights to a few servers
     */
    int authority(vector<int> &nums) {
        // write your code here
        n = m = SZ(nums);
        G.clear();
        G.resize(n + 1);
        for (int i = 0; i < SZ(nums); ++i) {
            G[i + 1].push_back(nums[i]);
        }
        return tarjan.work();
    }
};

void run() {}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = nextInt();
    while (_T--) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //	while (cin >> n) run();
    //	run();
    return 0;
}
