#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) ((int)x.size())
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
inline int rd() {
    int x;
    cin >> x;
    return x;
}
template <class T>
inline void rd(T &x) {
    cin >> x;
}
template <class T>
inline void rd(vector<T> &vec) {
    for (auto &it : vec) cin >> it;
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
template <class T1, class T2>
T1 gcd(T1 a, T2 b) {
    return b ? gcd(b, a % b) : a;
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
constexpr int N = 3e5 + 10;
int n, m;

struct SEG {
    struct node {
        int cnt, v;
        node() {
            cnt = 1;
            v = 0;
        }
        node operator+(const node &other) const {
            node res = node();
            res.cnt = cnt + other.cnt;
            return res;
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r)
            return;
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update(int id, int l, int r, int ql, int qr, int v) {
        if (ql > qr)
            return;
        if (t[id].cnt == 0)
            return;
        if (l == r) {
            t[id].v = v;
            t[id].cnt = 0;
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            update(id << 1, l, mid, ql, qr, v);
        if (qr > mid)
            update(id << 1 | 1, mid + 1, r, ql, qr, v);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    int query(int id, int l, int r, int pos) {
        if (l == r)
            return t[id].v;
        int mid = (l + r) >> 1;
        if (pos <= mid)
            return query(id << 1, l, mid, pos);
        else
            return query(id << 1 | 1, mid + 1, r, pos);
    }
} seg;

void run() {
    seg.build(1, 1, n);
    for (int i = 1, l, r, x; i <= m; ++i) {
        cin >> l >> r >> x;
        seg.update(1, 1, n, l, x - 1, x);
        seg.update(1, 1, n, x + 1, r, x);
    }
    for (int i = 1; i <= n; ++i) cout << seg.query(1, 1, n, i) << " \n"[i == n];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n >> m) run();
    return 0;
}
