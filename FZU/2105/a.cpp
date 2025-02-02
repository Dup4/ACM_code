#include <algorithm>
#include <bitset>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
const int N = 1e6 + 10;
struct SEG {
    struct node {
        int sum[2];
        int And;
        int Or;
        int Xor;

        node() {
            sum[0] = sum[1] = And = Or = Xor = 0;
        }
        void upAnd() {
            sum[0] += sum[1];
            sum[1] = 0;
            And = 1;
            Or = Xor = 0;
        }

        void upOr() {
            sum[1] += sum[0];
            sum[0] = 0;
            Or = 1;
            And = Xor = 0;
        }

        void upXor() {
            swap(sum[0], sum[1]);
            if (And || Or) {
                Xor = 0;
                swap(And, Or);
            } else
                Xor = 1;
        }

        node operator+(const node &other) const {
            node res = node();
            res.sum[0] = sum[0] + other.sum[0];
            res.sum[1] = sum[1] + other.sum[1];
            return res;
        }
    } t[N << 2];

    void pushdown(int id) {
        if (t[id].And)
            t[id << 1].upAnd(), t[id << 1 | 1].upAnd(), t[id].And = 0;
        if (t[id].Or)
            t[id << 1].upOr(), t[id << 1 | 1].upOr(), t[id].Or = 0;
        if (t[id].Xor)
            t[id << 1].upXor(), t[id << 1 | 1].upXor(), t[id].Xor = 0;
    }

    void build(int id, int l, int r) {
        if (l == r) {
            t[id] = node();
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
    }

    void update(int id, int l, int r, int p, int v) {
        if (l == r) {
            t[id].sum[v]++;
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid)
            update(id << 1, l, mid, p, v);
        else
            update(id << 1 | 1, mid + 1, r, p, v);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }

    void updateAnd(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            t[id].upAnd();
            return;
        }
        pushdown(id);
        int mid = (l + r) >> 1;
        if (ql <= mid)
            updateAnd(id << 1, l, mid, ql, qr);
        if (qr > mid)
            updateAnd(id << 1 | 1, mid + 1, r, ql, qr);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }

    void updateOr(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            t[id].upOr();
            return;
        }
        pushdown(id);
        int mid = (l + r) >> 1;
        if (ql <= mid)
            updateOr(id << 1, l, mid, ql, qr);
        if (qr > mid)
            updateOr(id << 1 | 1, mid + 1, r, ql, qr);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }

    void updateXor(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            t[id].upXor();
            return;
        }
        pushdown(id);
        int mid = (l + r) >> 1;
        if (ql <= mid)
            updateXor(id << 1, l, mid, ql, qr);
        if (qr > mid)
            updateXor(id << 1 | 1, mid + 1, r, ql, qr);
        t[id] = t[id << 1] + t[id << 1 | 1];
    }

    int query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            return t[id].sum[1];
        }
        int mid = (l + r) >> 1;
        pushdown(id);
        int res = 0;
        if (ql <= mid)
            res += query(id << 1, l, mid, ql, qr);
        if (qr > mid)
            res += query(id << 1 | 1, mid + 1, r, ql, qr);
        return res;
    }
} seg[4];
int n, q, a[N];

void RUN() {
    int _T;
    scanf("%d", &_T);
    while (_T--) {
        scanf("%d%d", &n, &q);
        for (int i = 0; i < 4; ++i) {
            seg[i].build(1, 1, n);
        }
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            for (int j = 0; j < 4; ++j) {
                if (a[i] & (1 << j)) {
                    seg[j].update(1, 1, n, i, 1);
                } else {
                    seg[j].update(1, 1, n, i, 0);
                }
            }
        }
        char op[10];
        for (int _q = 1, l, r, x; _q <= q; ++_q) {
            scanf("%s", op);
            if (op[0] == 'S') {
                scanf("%d%d", &l, &r);
                ++l, ++r;
                ll res = 0;
                for (int i = 0; i < 4; ++i) {
                    res += (1ll << i) * seg[i].query(1, 1, n, l, r);
                }
                printf("%lld\n", res);
            } else if (op[0] == 'X') {
                scanf("%d%d%d", &x, &l, &r);
                ++l, ++r;
                for (int i = 0; i < 4; ++i) {
                    if (x & (1 << i)) {
                        seg[i].updateXor(1, 1, n, l, r);
                    }
                }
            } else if (op[0] == 'O') {
                scanf("%d%d%d", &x, &l, &r);
                ++l, ++r;
                for (int i = 0; i < 4; ++i) {
                    if (x & (1 << i)) {
                        seg[i].updateOr(1, 1, n, l, r);
                    }
                }
            } else if (op[0] == 'A') {
                scanf("%d%d%d", &x, &l, &r);
                ++l, ++r;
                for (int i = 0; i < 4; ++i) {
                    if (!(x & (1 << i))) {
                        seg[i].updateAnd(1, 1, n, l, r);
                    }
                }
            }
        }
    }
}

int main() {
    RUN();
    return 0;
}
