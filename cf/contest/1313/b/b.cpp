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
ll n, x, y;

ll calc1(ll mid) {
    ll l1 = mid + 1, r1 = n;
    ll l2 = mid + 1, r2 = n;
    if (x == n)
        --r1;
    if (l1 >= x)
        ++l1;
    if (y == n)
        --r2;
    if (l2 >= y)
        ++l2;
    //	dbg(mid, l1, r1, l2, r2);
    return min(l1 + r2, l2 + r1);
}

ll calc2(ll mid) {
    ll l1 = 1, r1 = mid;
    ll l2 = 1, r2 = mid;
    if (x == 1)
        ++l1;
    if (r1 >= x)
        ++r1;
    if (y == 1)
        ++l2;
    if (r2 >= y)
        ++r2;
    return max(l1 + r2, l2 + r1);
}

void run() {
    rd(n, x, y);
    if (n == 1)
        return pt(1, 1);
    ll res[2] = {n - 1, 0};
    // Min
    ll l = 0, r = n - 1;
    while (r - l >= 0) {
        ll mid = (l + r) >> 1;
        if (calc1(mid) > x + y) {
            res[0] = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    l = 0, r = n - 1;
    while (r - l >= 0) {
        ll mid = (l + r) >> 1;
        if (calc2(mid) <= x + y) {
            res[1] = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    pt(res[0] + 1, res[1] + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    int _T = nextInt();
    while (_T--) run();
    //	while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
