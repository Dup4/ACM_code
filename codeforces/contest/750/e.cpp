#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 10;
const int INF = 0x3f3f3f3f;
int n, q;
char s[N];
int base[10][5][5];
inline void chmin(int &x, int y) {
    if (x > y)
        x = y;
}
struct SEG {
    struct Matrix {
        int a[5][5];
        Matrix() {
            memset(a, 0x3f, sizeof a);
        }
        Matrix(int _a[5][5]) {
            for (int i = 0; i < 5; ++i)
                for (int j = 0; j < 5; ++j) a[i][j] = _a[i][j];
        }
        bool isbase() {
            for (int i = 0; i < 5; ++i)
                for (int j = 0; j < 5; ++j) {
                    if (i == j)
                        if (a[i][j] != 1)
                            return 0;
                    if (i != j)
                        if (a[i][j] != 0)
                            return 0;
                }
            return 1;
        }
        void setbase() {
            memset(a, 0, sizeof a);
            for (int i = 0; i < 5; ++i) a[i][i] = 1;
        }
        Matrix operator*(const Matrix &other) const {
            Matrix res = Matrix();
            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 5; ++j) {
                    for (int k = 0; k < 5; ++k) {
                        chmin(res.a[i][j], a[i][k] + other.a[k][j]);
                    }
                }
            }
            return res;
        }
    } t[N << 2], res;
    void build(int id, int l, int r) {
        if (l == r) {
            t[id] = Matrix(base[s[l] - '0']);
            return;
        }
        int mid = (l + r) >> 1;
        build(id << 1, l, mid);
        build(id << 1 | 1, mid + 1, r);
        t[id] = t[id << 1] * t[id << 1 | 1];
    }
    void query(int id, int l, int r, int ql, int qr) {
        if (l >= ql && r <= qr) {
            res = res * t[id];
            return;
        }
        int mid = (l + r) >> 1;
        if (ql <= mid)
            query(id << 1, l, mid, ql, qr);
        if (qr > mid)
            query(id << 1 | 1, mid + 1, r, ql, qr);
    }
} seg;

int main() {
    memset(base, 0x3f, sizeof base);
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 5; ++j) base[i][j][j] = 0;
    // 2
    base[2][0][0] = 1;
    base[2][0][1] = 0;
    // 0
    base[0][1][1] = 1;
    base[0][1][2] = 0;
    // 1
    base[1][2][3] = 0;
    base[1][2][2] = 1;
    // 7
    base[7][3][4] = 0;
    base[7][3][3] = 1;
    // 6
    base[6][3][3] = 1;
    base[6][4][4] = 1;
    while (scanf("%d%d", &n, &q) != EOF) {
        scanf("%s", s + 1);
        seg.build(1, 1, n);
        for (int i = 1, l, r; i <= q; ++i) {
            scanf("%d%d", &l, &r);
            seg.res = SEG::Matrix();
            for (int i = 0; i < 5; ++i) seg.res.a[i][i] = 0;
            seg.query(1, 1, n, l, r);
            if (seg.res.a[0][4] >= INF)
                puts("-1");
            else
                printf("%d\n", seg.res.a[0][4]);
        }
    }
    return 0;
}
