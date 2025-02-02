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
int n;
string g[30];
int G[30][30];

bool valid(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= n)
        return false;
    return true;
}

int Move[][2][2] = {
        {{-1, 0}, {1, 0}},
        {{0, -1}, {0, 1}},
        {{-1, -1}, {1, 1}},
        {{-1, 1}, {1, -1}},
};

bool ok(int fir) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (G[i][j] == fir) {
                for (int k = 0; k < 4; ++k) {
                    int now = 1;
                    for (int _i = 0; _i < 2; ++_i) {
                        int nx = i, ny = j;
                        while (1) {
                            nx = nx + Move[k][_i][0];
                            ny = ny + Move[k][_i][1];
                            if (valid(nx, ny) && G[nx][ny] == fir)
                                ++now;
                            else
                                break;
                        }
                    }
                    if (now >= 5)
                        return true;
                }
            }
        }
    }
    return false;
}

void run() {
    n = 25;
    for (int i = 0; i < n; ++i) rd(g[i]);
    int cnt[2] = {0, 0};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            G[i][j] = -1;
            if (g[i][j] == 'o')
                ++cnt[1], G[i][j] = 1;
            else if (g[i][j] == 'x')
                ++cnt[0], G[i][j] = 0;
        }
    }
    int fir = cnt[0] > cnt[1];
    assert(!ok(fir));
    //	dbg(fir);
    vector<pII> res;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (G[i][j] == -1) {
                G[i][j] = fir;
                if (ok(fir))
                    res.push_back(pII(i, j));
                G[i][j] = -1;
            }
        }
    }
    if (res.empty())
        pt("tie");
    else {
        sort(all(res));
        for (auto &it : res) pt(it.fi, it.se);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = 1;
    while (_T--) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ": ";
    //        run();
    //    }
    //	while (cin >> n) run();
    //	run();
    return 0;
}
