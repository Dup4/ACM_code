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
constexpr int mod = 998244353;
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
constexpr int N = 5e5 + 10;
int n, k, m, l[N], r[N], x[N];
ll a[N];

struct SEG {
    struct node {
        ll val, lazy;
        node() {
            val = lazy = 0;
        }
        void up(ll x) {
            val |= x;
            lazy |= x;
        }
    } t[N << 2];
    void down(int id) {
        ll &lazy = t[id].lazy;
        t[id << 1].up(lazy);
        t[id << 1 | 1].up(lazy);
        lazy = 0;
    }
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }
    void update(int id, int l, int r, int ql, int qr, ll v) {
        if (l >= ql && r <= qr) {
            t[id].up(v);
            return;
        }
        int mid = (l + r) >> 1;
        down(id);
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, v);
    }
    ll query(int id, int l, int r, int pos) {
        if (l == r)
            return t[id].val;
        int mid = (l + r) >> 1;
        down(id);
        if (pos <= mid)
            return query(id << 1, l, mid, pos);
        else
            return query(id << 1 | 1, mid + 1, r, pos);
    }
} seg;

void run() {
    seg.build(1, 1, n);
    for (int i = 1; i <= m; ++i) {
        rd(l[i], r[i], x[i]);
        seg.update(1, 1, n, l[i], r[i], x[i]);
    }
    for (int i = 1; i <= n; ++i) a[i] = seg.query(1, 1, n, i);
    ll A = 1, B = 1;
    for (int i = 1; i <= n; ++i) {
        int bit = __builtin_popcountll(a[i]);
        A = A * (k - bit + 1) % mod;
        B = B * (k - bit) % mod;
    }
    pt((A - B + mod) % mod);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> k >> m) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
