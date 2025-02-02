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
constexpr int N = 2e5 + 10, INF = 0x3f3f3f3f;
int n, a[N];
ll res;
bitset<N> b[35], all, use, now;

struct SEG {
    struct node {
        int Max, pos;
        node() {
            Max = -INF, pos = 0;
        }
        node operator+(const node &other) const {
            if (Max > other.Max) {
                return *this;
            } else {
                return other;
            }
        }
    } t[N << 2];
    void build(int id, int l, int r) {
        t[id] = node();
        if (l == r) {
            t[id].Max = a[l];
            t[id].pos = l;
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
    void update(int id, int l, int r, int pos) {
        if (l == r) {
            t[id].Max = -INF;
            t[id].pos = -1;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(id << 1, l, mid, pos);
        else
            update(id << 1 | 1, mid + 1, r, pos);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }
} seg;

void gao(int x) {
    seg.update(1, 1, n, x);
    use[x] = 1;
    int w = a[x];
    now.reset();
    for (int i = 0; i < 20; ++i) {
        if ((x >> i) & 1) {
            now |= b[i];
        }
        //	if (now == all) break;
    }
    now.flip();
    if (all[x] == 0 && (now & use).count() > 0)
        res += w;
    all[x] = 0;
    now &= all;
    for (int i = now._Find_first(); i != SZ(now); i = now._Find_next(i)) {
        res += w;
        all[i] = 0;
    }
    all ^= now;
}

void run() {
    for (int i = 1; i <= n; ++i) rd(a[i]);
    all.reset();
    use.reset();
    for (int i = 1; i <= n; ++i) all[i] = 1, use[i] = 0;
    for (int i = 0; i < 20; ++i) b[i].reset();
    seg.build(1, 1, n);
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 20; ++j) {
            if ((i >> j) & 1) {
                b[j][i] = 1;
            }
        }
    }
    res = 0;
    while (1) {
        int pos = seg.t[1].pos;
        if (pos == -1)
            break;
        gao(pos);
    }
    pt(res);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cout << fixed << setprecision(20);
    while (cin >> n) run();
    //    for (int kase = 1; kase <= _T; ++kase) {
    //        cout << "Case #" << kase << ":\n";
    //        run();
    //    }
    return 0;
}
