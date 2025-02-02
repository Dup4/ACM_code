#include <bits/stdc++.h>
using namespace std;
typedef double db;
const db eps = 1e-10;
int sgn(db x) {
    if (fabs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}

struct LP {
    int m, n;
    vector<int> B, N;
    vector<vector<db> > D;
    LP() {}
    LP(vector<vector<db> > &A, const vector<db> &b, const vector<db> &c) {
        m = (int)b.size();
        n = (int)c.size();
        N = vector<int>(n + 1);
        B = vector<int>(m + 1);
        swap(D, A);
        //		D = vector <vector<db> >(m + 2, vector<db>(n + 2));
        //      for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) D[i][j] = A[i][j];
        for (int i = 0; i < m; i++) {
            B[i] = n + i;
            D[i][n] = -1;
            D[i][n + 1] = b[i];
        }
        for (int j = 0; j < n; j++) {
            N[j] = j;
            D[m][j] = -c[j];
        }
        N[n] = -1;
        D[m + 1][n] = 1;
    }
    void Pivot(int r, int s) {
        for (int i = 0; i < m + 2; i++)
            if (i != r)
                for (int j = 0; j < n + 2; j++)
                    if (j != s)
                        D[i][j] -= D[r][j] * D[i][s] / D[r][s];
        for (int j = 0; j < n + 2; j++)
            if (j != s)
                D[r][j] /= D[r][s];
        for (int i = 0; i < m + 2; i++)
            if (i != r)
                D[i][s] /= -D[r][s];
        D[r][s] = 1.0 / D[r][s];
        swap(B[r], N[s]);
    }
    bool Simplex(int phase) {
        int x = phase == 1 ? m + 1 : m;
        while (true) {
            int s = -1;
            for (int j = 0; j <= n; j++) {
                if (phase == 2 && N[j] == -1)
                    continue;
                if (s == -1 || D[x][j] < D[x][s] || (D[x][j] == D[x][s] && N[j] < N[s]))
                    s = j;
            }
            if (D[x][s] > -eps)
                return true;
            int r = -1;
            for (int i = 0; i < m; i++) {
                if (D[i][s] < eps)
                    continue;
                if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] ||
                        ((D[i][n + 1] / D[i][s]) == (D[r][n + 1] / D[r][s]) && B[i] < B[r]))
                    r = i;
            }
            if (r == -1)
                return false;
            Pivot(r, s);
        }
    }
    db Solve(vector<db> &x) {
        int r = 0;
        for (int i = 1; i < m; i++)
            if (D[i][n + 1] < D[r][n + 1])
                r = i;
        if (D[r][n + 1] < -eps) {
            Pivot(r, n);
            if (!Simplex(1) || D[m + 1][n + 1] < -eps)
                return -numeric_limits<db>::infinity();
            for (int i = 0; i < m; i++)
                if (B[i] == -1) {
                    int s = -1;
                    for (int j = 0; j <= n; j++)
                        if (s == -1 || D[i][j] < D[i][s] || (D[i][j] == D[i][s] && N[j] < N[s]))
                            s = j;
                    Pivot(i, s);
                }
        }
        if (!Simplex(2))
            return numeric_limits<db>::infinity();
        x = vector<db>(n);
        for (int i = 0; i < m; i++)
            if (B[i] < n)
                x[B[i]] = D[i][n + 1];
        return D[m][n + 1];
    }
};

const int N = 1e3 + 10;
int n, m, a[N];

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        vector<vector<db> > A(n + 2, vector<db>(m + 2, 0));
        vector<db> B(n);
        vector<db> C(m);
        vector<db> X;
        for (int i = 0; i < n; ++i) scanf("%d", a + i);
        for (int i = 0, l, r, c; i < m; ++i) {
            scanf("%d%d%d", &l, &r, &c);
            for (int j = l - 1; j < r; ++j) {
                A[j][i] = -1;
            }
            C[i] = -c;
        }
        for (int i = 0; i < n; ++i) B[i] = -a[i];
        LP lp(A, B, C);
        printf("%.0f\n", -lp.Solve(X));
    }
    return 0;
}
