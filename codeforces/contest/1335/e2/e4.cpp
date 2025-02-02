#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define SZ(x) int((x).size())
#define endl "\n"
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
constexpr int N = 2e5 + 10;
int n, a[N], f[N], g[N], s[N], cnt[230], h[230];

void run() {
    rd(n);
    memset(cnt, 0, sizeof cnt);
    for (int i = 1; i <= n; ++i) rd(a[i]);
    int res = 0;
    for (int o = 1; o <= 200; ++o) {
        for (int i = 1; i <= n; ++i) cnt[a[i]] = 0;
        int Max = 0;
        for (int i = 1; i <= n; ++i) {
            ++cnt[a[i]];
            chmax(Max, cnt[a[i]]);
        }
        chmax(res, Max);
        int l = 0, r = n + 1;
        int num = 0, tot = cnt[o];
        for (int i = 1; i <= n; ++i) {
            cnt[a[i]] = 0;
            if (a[i] == o) {
                ++num;
                if (num == tot / 2)
                    l = i;
                if (num == tot - (tot / 2) + 1)
                    r = i;
            }
        }
        if (l < 1 || r > n)
            continue;
        Max = 0;
        for (int i = l + 1; i < r; ++i) {
            ++cnt[a[i]];
            chmax(Max, cnt[a[i]]);
        }
        num = tot / 2;
        chmax(res, Max + num * 2);
        while (l > 1 && r < n) {
            while (l >= 1) {
                --l;
                if (!l)
                    break;
                if (a[l] == o)
                    break;
                ++cnt[a[l]];
                chmax(Max, cnt[a[l]]);
            }
            while (r <= n) {
                ++r;
                if (r == n + 1)
                    break;
                if (a[r] == o)
                    break;
                ++cnt[a[r]];
                chmax(Max, cnt[a[r]]);
            }
            if (l >= 1 && r <= n) {
                --num;
                chmax(res, Max + num * 2);
            }
        }
        //	dbg(o, res);
    }
    pt(res);
}

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
